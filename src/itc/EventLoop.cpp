#include <api/itc/EventLoop.hpp>
#include <api/itc/InterThreadComm.hpp>
#include <api/logging/Log.hpp>
#include <iostream>

namespace sf
{

EventLoop::EventLoop () : mDispatcher (std::make_shared<Dispatcher> (mTrigger)) {}

void
EventLoop::run ()
{
  mRunning = true;

  InterThreadComm::getInstance ().registerDispatcher (std::this_thread::get_id (), mDispatcher);

  uint32_t tick = 0;
  do
  {
    tick++;

    std::unique_lock<std::mutex> lock (mLoop);
    mTrigger.wait (lock);

    sf::logM ("Tick: %d", tick);
    mDispatcher->dispatch ();

  } while (mRunning);
}

void
EventLoop::stop ()
{
  mRunning = false;
  mTrigger.notify_one ();
}

bool
EventLoop::isRunning ()
{
  return mRunning;
}

} /* namespace sf */
