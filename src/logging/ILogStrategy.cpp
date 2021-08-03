#include <api/logging/ILogStrategy.hpp>

namespace sf
{

void
ILogStrategy::setUp ()
{
  // NoOp
}

void
ILogStrategy::tearDown ()
{
  // NoOp
}

void
ILogStrategy::logMsg (ELogSeverity, const char *const str, const std::size_t num)
{
  // NoOp
}

}
