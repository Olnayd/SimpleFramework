#ifndef API_ILOGSTRATEGY_HPP_
#define API_ILOGSTRATEGY_HPP_

#include <cstddef>

namespace sf
{

enum ELogSeverity
{
  Msg,
  Warn,
  Error
};

class ILogStrategy
{
public:
  ILogStrategy () = default;
  ILogStrategy (const ILogStrategy &) = default;
  ILogStrategy (ILogStrategy &&) = default;
  ILogStrategy &operator= (const ILogStrategy &) = default;
  ILogStrategy &operator= (ILogStrategy &&) = default;
  virtual ~ILogStrategy () = default;

public:
  virtual void setUp ();
  virtual void tearDown ();
  virtual void logMsg (ELogSeverity, const char *const str, const std::size_t num);
};

}

#endif /* API_ILOGSTRATEGY_HPP_ */
