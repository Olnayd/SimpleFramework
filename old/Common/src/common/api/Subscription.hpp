#ifndef SRC_SUBSCRIPTION_HPP_
#define SRC_SUBSCRIPTION_HPP_

#include <common/api/guard.hpp>
#include <functional>
#include <vector>

class Subscription : public guarded
{
};

using tSubscriptionList = std::vector<Subscription>;

template <typename PAYLOAD> class Attribute
{
public:
  using tCallback = std::function<void (const PAYLOAD &)>;

public:
  Attribute ();

  Subscription
  subscribe (tCallback &&cb)
  {
    return subscribe (cb);
  };

  Subscription
  subscribe (tCallback &cb)
  {
    Subscription subscription;
    subscriptions.emplace_back (std::make_pair (subscription.getGuard (), cb));
    return subscription;
  }

private:
  std::vector<std::pair<guard, tCallback> > subscriptions;
};

#endif /* SRC_SUBSCRIPTION_HPP_ */
