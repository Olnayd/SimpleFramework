#include <api/logging/Logger.hpp>

namespace sf
{

Logger &
Logger::getInstance ()
{
  static sf::Logger logger;
  return logger;
}

void
Logger::setUp ()
{
  std::setbuf (stdout, NULL); // unbuffered stdout
  mBuffer = new char[mBufferSize];
}

void
Logger::tearDown ()
{
  delete[] mBuffer;
}

void
Logger::registerStrategy (std::unique_ptr<ILogStrategy> &&strategy)
{
  mStrategies.emplace_back (std::move (strategy));
}

void
Logger::logMsg (ELogSeverity severity, const char *str, va_list vlist) const
{
  if (mBuffer)
  {
    auto num = vsnprintf (mBuffer, mBufferSize, str, vlist);
    if (0 > num)
    {
      // If an encoding error occurs, a negative number is returned.
      return;
    }

    for (const auto &strategy : mStrategies)
    {
      strategy->logMsg (severity, mBuffer, num);
    }
  }
}

}
