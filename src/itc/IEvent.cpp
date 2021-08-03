#include <api/itc/IEvent.hpp>

namespace sf
{

IEvent::IEvent () : mCreatorThreadId (std::this_thread::get_id ()) {}

ThreadId
IEvent::getCreatorThreadId () const
{
  return mCreatorThreadId;
}

void
IEvent::dispatchSelf ()
{
  // NoOp
}

}
