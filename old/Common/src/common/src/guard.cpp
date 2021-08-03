#include "common/api/guard.hpp"

guard::guard (const std::shared_ptr<void> &pShared) : weak{ pShared } {}

guarded::guarded () : mGuard{ std::make_shared<int> () } {}

guarded::~guarded () = default;

guard
guarded::getGuard ()
{
  return mGuard;
}
