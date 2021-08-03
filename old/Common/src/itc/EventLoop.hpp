#ifndef SRC_ITC_EVENTLOOP_HPP_
#define SRC_ITC_EVENTLOOP_HPP_

#include <itc/Dispatcher.hpp>

namespace sf
{

class EventLoop
{
public:
  void start ();
  void stop ();

private:
  bool mRunning;
  Dispatcher mDispatcher;
  std::mutex mLoop;
  std::condition_variable mTrigger;
};

} /* namespace sf */

#endif /* SRC_ITC_EVENTLOOP_HPP_ */
