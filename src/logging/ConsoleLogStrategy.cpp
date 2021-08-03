#include <api/logging/ConsoleLogStrategy.hpp>
#include <functional>
#include <iostream>

namespace sf
{

void
ConsoleLogStrategy::logMsg (ELogSeverity severity, const char *const str, const std::size_t num)
{
  std::reference_wrapper<std::ostream> out = std::ref (std::cout);
  if (ELogSeverity::Error == severity)
  {
    out = std::ref (std::cerr);
  }

  out.get () << str << std::endl;
}

}
