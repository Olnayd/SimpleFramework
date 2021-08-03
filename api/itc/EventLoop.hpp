#ifndef SRC_ITC_EVENTLOOP_HPP_
#define SRC_ITC_EVENTLOOP_HPP_

#include <api/itc/Dispatcher.hpp>

namespace sf
{

class EventLoop
{
public:
  explicit EventLoop ();

  void run ();
  void stop ();
  bool isRunning ();

public:
  bool mRunning;
  std::mutex mLoop;
  std::condition_variable mTrigger;
  ThreadId mCurrentThreadId;
  std::shared_ptr<Dispatcher> mDispatcher;
};

} /* namespace sf */

#endif /* SRC_ITC_EVENTLOOP_HPP_ */
