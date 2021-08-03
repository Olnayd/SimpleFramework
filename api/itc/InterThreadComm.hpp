#ifndef API_ITC_INTERTHREADCOMM_HPP_
#define API_ITC_INTERTHREADCOMM_HPP_

#include <api/itc/Definitions.hpp>
#include <api/itc/Dispatcher.hpp>

namespace sf
{

class InterThreadComm
{
public:
  static InterThreadComm &getInstance ();

public:
  void setUp ();
  void tearDown ();
  bool registerDispatcher (ThreadId forThreadId, const std::shared_ptr<Dispatcher> &);
  bool sendEvent (ThreadId toThreadId, const IEvent &);

private:
  std::mutex mAccess;
  std::map<ThreadId, std::shared_ptr<Dispatcher> > mThreadId2Dispatcher;
};

}

#endif /* API_ITC_INTERTHREADCOMM_HPP_ */
