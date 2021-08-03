#include <iostream>
#include <itc/EventLoop.hpp>

namespace sf
{

void
EventLoop::start ()
{
  mRunning = true;
  // TODO Register dispatcher
  // mDispatcher.dispatch ();

  do
  {
    std::cout << "Event loop";
    std::unique_lock<std::mutex> lock (mLoop);
    mTrigger.wait (lock);

    mDispatcher.dispatch ();

  } while (mRunning);
}

void
EventLoop::stop ()
{
  mRunning = false;
  mTrigger.notify_one ();
}

} /* namespace sf */
