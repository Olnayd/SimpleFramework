#ifndef API_LOGGING_CONSOLELOGSTRATEGY_HPP_
#define API_LOGGING_CONSOLELOGSTRATEGY_HPP_

#include <api/logging/ILogStrategy.hpp>

namespace sf
{

class ConsoleLogStrategy : public ILogStrategy
{
public:
  virtual void logMsg (ELogSeverity, const char *const str, const std::size_t num);
};

}

#endif /* API_LOGGING_CONSOLELOGSTRATEGY_HPP_ */
