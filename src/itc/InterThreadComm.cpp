#include <api/itc/InterThreadComm.hpp>

namespace sf
{

void
InterThreadComm::setUp ()
{
}

void
InterThreadComm::tearDown ()
{
}

InterThreadComm &
InterThreadComm::getInstance ()
{
  static InterThreadComm instance;
  return instance;
}

bool
InterThreadComm::registerDispatcher (ThreadId threadId, const std::shared_ptr<Dispatcher> &dispatcher)
{
  bool bReturnValue{ false };

  auto &globalDispatcher = mThreadId2Dispatcher[threadId];
  if (!globalDispatcher)
  {
    bReturnValue = true;
    globalDispatcher = dispatcher;
  }

  return bReturnValue;
}

bool
InterThreadComm::sendEvent (ThreadId toThreadId, const IEvent &event)
{
  bool bReturnValue{ false };

  auto &dispatcher = mThreadId2Dispatcher[toThreadId];
  if (dispatcher)
  {
    bReturnValue = true;
    if (toThreadId == event.getCreatorThreadId ())
    {
      dispatcher->addInternalEvent (event);
    }
    else
    {
      dispatcher->addExternalEvent (event);
    }
  }

  return bReturnValue;
}

}
