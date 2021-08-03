#include <api/itc/EventThread.hpp>
#include <api/logging/Log.hpp>

namespace sf
{

EventThread::EventThread () : mThreadInfo (std::make_shared<ThreadInfo> ()), mEventLoop (std::make_shared<EventLoop> ())
{
}

void
EventThread::run ()
{
  mThread = std::make_unique<std::thread> ([evLoop = mEventLoop, thrInfo = mThreadInfo] () {
    thrInfo->id = std::this_thread::get_id ();
    sf::logM ("Run Thread %u", thrInfo->id);

    evLoop->run ();
  });
}

void
EventThread::stop ()
{
  if (mEventLoop->isRunning ())
  {
    mEventLoop->stop ();
  }
  mThread->join ();
  mThread.reset ();
}

std::shared_ptr<ThreadInfo>
EventThread::getThreadInfo ()
{
  return mThreadInfo;
}

}
