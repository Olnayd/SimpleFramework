
#include <algorithm>
#include <common/api/Operation.hpp>
#include <vector>

namespace
{
enum ECommandStep
{
  Finished,
  Pending,
  Aborted // Unrecoverable state
};
}

struct Operation::SharedState
{
  ECommandStep step{ ECommandStep::Finished };
  std::shared_ptr<void> payload;
  bool bPending{ false };
  std::vector<Operation> waitForList;
  std::vector<std::function<void ()> > onFinishCallbackList;

  void finish ();
  void abort ();
  void notify ();
};

void
Operation::SharedState::finish ()
{
  if (ECommandStep::Aborted != step)
  {
    const auto bJoinedOperationFinished = std::all_of (waitForList.begin (), waitForList.end (),
                                                       [] (const auto &command) { return command.isFinished (); });
    if (!bPending && bJoinedOperationFinished)
    {
      std::vector<Operation> tmpWaitForList;
      tmpWaitForList.swap (waitForList);
      step = ECommandStep::Finished;
      notify ();
    }
  }
}

void
Operation::SharedState::abort ()
{
  if (ECommandStep::Aborted != step)
  {
    std::vector<Operation> tmpWaitForList;
    tmpWaitForList.swap (waitForList);
    step = ECommandStep::Aborted;
    notify ();
  }
}

void
Operation::SharedState::notify ()
{
  std::vector<std::function<void ()> > tmpOnFinishCallbackList;
  tmpOnFinishCallbackList.swap (onFinishCallbackList);
  for (const auto &callback : tmpOnFinishCallbackList)
  {
    callback ();
  }
}

Operation::Operation () = default;
Operation::~Operation () = default;
Operation::Operation (const Operation &command) : mpSharedState (command.mpSharedState) {}

bool
Operation::isSharedStateExists () const
{
  return mpSharedState.operator bool ();
}

std::shared_ptr<Operation::SharedState>
Operation::getSharedState () const
{
  return mpSharedState;
}

std::shared_ptr<Operation::SharedState>
Operation::getOrCreateSharedState ()
{
  if (!mpSharedState)
  {
    mpSharedState = std::make_shared<SharedState> ();
  }
  return mpSharedState;
}

void
Operation::setPayload (const std::shared_ptr<void> &payload_)
{
  getOrCreateSharedState ()->payload = payload_;
}

std::shared_ptr<void>
Operation::getPayload () const
{
  if (isSharedStateExists ())
  {
    return getSharedState ()->payload;
  }
  return nullptr;
}

void
Operation::onFinish (std::function<void (Operation)> &&cb)
{
  onFinish ([cb = std::move (cb), command = *this] () { cb (command); });
}

void
Operation::onFinish (std::function<void ()> &&cb)
{
  if (isPending ())
  {
    getOrCreateSharedState ()->onFinishCallbackList.emplace_back (std::move (cb));
  }
  else
  {
    cb ();
  }
}

void
Operation::abort ()
{
  const auto sharedstate = getOrCreateSharedState ();
  sharedstate->abort ();
}

void
Operation::finish ()
{
  const auto sharedstate = getOrCreateSharedState ();
  if (ECommandStep::Pending == sharedstate->step || ECommandStep::Finished == sharedstate->step)
  {
    sharedstate->bPending = false;
    sharedstate->finish ();
  }
}

void
Operation::setPending ()
{
  const auto sharedstate = getOrCreateSharedState ();
  if (ECommandStep::Pending == sharedstate->step || ECommandStep::Finished == sharedstate->step)
  {
    sharedstate->step = ECommandStep::Pending;
    sharedstate->bPending = true;
  }
}

bool
Operation::isPending () const
{
  if (isSharedStateExists ())
  {
    return ECommandStep::Pending == getSharedState ()->step;
  }
  return false;
}

bool
Operation::isAborted () const
{
  if (isSharedStateExists ())
  {
    return ECommandStep::Aborted == getSharedState ()->step;
  }
  return false;
}

bool
Operation::isFinished () const
{
  if (isSharedStateExists ())
  {
    return getSharedState ()->step == ECommandStep::Aborted || getSharedState ()->step == ECommandStep::Finished;
  }
  return true;
}

Operation
Operation::join (Operation &&cm)
{
  join (cm);
  return cm;
}

Operation
Operation::join (Operation &cm)
{
  const auto sharedstate = getOrCreateSharedState ();
  if (ECommandStep::Finished == sharedstate->step)
  {
    sharedstate->step = ECommandStep::Pending;
  }

  if (ECommandStep::Pending == sharedstate->step)
  {
    sharedstate->waitForList.push_back (cm);
    cm.onFinish ([sharedstate] (Operation cm) { sharedstate->finish (); });
  }
  return cm;
}
