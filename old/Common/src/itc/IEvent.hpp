#ifndef SRC_ITC_IEVENT_HPP_
#define SRC_ITC_IEVENT_HPP_

namespace sf
{

class IEvent
{
public:
  friend class Dispatcher;

  IEvent (const IEvent &) = default;
  IEvent (IEvent &&) = default;
  IEvent &operator= (const IEvent &) = default;
  IEvent &operator= (IEvent &&) = default;
  virtual ~IEvent () = default;

private:
  virtual void dispatchSelf (){};
};

} /* namespace sf */

#endif /* SRC_ITC_IEVENT_HPP_ */
