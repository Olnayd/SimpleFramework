#ifndef SRC_ITC_IEVENT_HPP_
#define SRC_ITC_IEVENT_HPP_

#include <api/itc/Definitions.hpp>

namespace sf
{

class IEvent
{
public:
  friend class Dispatcher;

  IEvent ();
  IEvent (const IEvent &) = default;
  IEvent (IEvent &&) = default;
  IEvent &operator= (const IEvent &) = default;
  IEvent &operator= (IEvent &&) = default;
  virtual ~IEvent () = default;

  ThreadId getCreatorThreadId () const;

private:
  virtual void dispatchSelf ();

private:
  const ThreadId mCreatorThreadId;
};

} /* namespace sf */

#endif /* SRC_ITC_IEVENT_HPP_ */
