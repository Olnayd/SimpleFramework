#ifndef API_ITC_EVENTTHREAD_HPP_
#define API_ITC_EVENTTHREAD_HPP_

#include <api/itc/EventLoop.hpp>
#include <thread>

namespace sf
{

struct ThreadInfo
{
  ThreadId id;
  std::string name;
};

class EventThread
{
public:
  explicit EventThread ();
  // TODO
  void run ();
  void stop ();

  std::shared_ptr<ThreadInfo> getThreadInfo ();

private:
  std::unique_ptr<std::thread> mThread;
  std::shared_ptr<ThreadInfo> mThreadInfo;
  std::shared_ptr<EventLoop> mEventLoop;
};

}

#endif /* API_ITC_EVENTTHREAD_HPP_ */
