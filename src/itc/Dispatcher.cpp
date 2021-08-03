#include <api/itc/Dispatcher.hpp>
#include <api/logging/Log.hpp>
#include <iostream>

namespace sf
{

Dispatcher::Dispatcher (std::condition_variable &trigger) : mTrigger (trigger){};

void
Dispatcher::addInternalEvent (const IEvent &event)
{
  sf::logM ("Dispatcher: %s", __FUNCTION__);
  mInternalQueue.push (event);
  mTrigger.notify_one ();
}

void
Dispatcher::addExternalEvent (const IEvent &event)
{
  sf::logM ("Dispatcher: %s", __FUNCTION__);
  {
    std::lock_guard<std::mutex> guard (mAccess);
    mExternalPushQueue.push (event);
  }
  mTrigger.notify_one ();
}

void
Dispatcher::dispatch ()
{
  if (mExternalPopQueue.empty ())
  {
    std::lock_guard<std::mutex> guard (mAccess);
    std::swap (mExternalPopQueue, mExternalPushQueue);
  }

  if (!mExternalPopQueue.empty ())
  {
    auto &event = mExternalPopQueue.top ();
    mExternalPopQueue.pop ();

    event.dispatchSelf ();
  }

  if (!mInternalQueue.empty ())
  {
    std::stack<IEvent> internalQueue;
    std::swap (internalQueue, mInternalQueue);
    while (!internalQueue.empty ())
    {
      auto &event = internalQueue.top ();
      internalQueue.pop ();

      event.dispatchSelf ();
    }
  }
}

}
