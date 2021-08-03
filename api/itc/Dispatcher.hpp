#ifndef SRC_ITC_DISPATCHER_HPP_
#define SRC_ITC_DISPATCHER_HPP_

#include <api/itc/IEvent.hpp>
#include <condition_variable>
#include <mutex>
#include <stack>

namespace sf
{

class Dispatcher
{
public:
  Dispatcher (std::condition_variable &);

  void addInternalEvent (const IEvent &);
  void addExternalEvent (const IEvent &);

  void dispatch ();
  void run ();

private:
  std::mutex mAccess;
  std::condition_variable &mTrigger;

  std::stack<IEvent> mInternalQueue;
  std::stack<IEvent> mExternalPopQueue;
  std::stack<IEvent> mExternalPushQueue;
};

}
#endif /* SRC_ITC_DISPATCHER_HPP_ */
