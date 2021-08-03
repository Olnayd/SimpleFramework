#ifndef SRC_COMMON_GUARD_HPP_
#define SRC_COMMON_GUARD_HPP_

#include <memory>

class guard
{
public:
  guard (const std::shared_ptr<void> &);

  inline bool
  isAlive ()
  {
    return !weak.expired ();
  };

private:
  std::weak_ptr<void> weak;
};

class guarded
{
public:
  guarded ();
  virtual ~guarded ();

  guard getGuard ();

private:
  std::shared_ptr<void> mGuard;
};

#endif /* SRC_COMMON_GUARD_HPP_ */
