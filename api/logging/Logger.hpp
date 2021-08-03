#ifndef API_LOGGER_HPP_
#define API_LOGGER_HPP_

#include <api/logging/ILogStrategy.hpp>
#include <memory>
#include <vector>

namespace sf
{

/***
 * The main class which handles logging of the system.
 ***
 * Example of usage:
 *
 * Create logger and fill it with strategies.
 *
 *    sf::Logger& logger = sf::Logger::getInstance();
 *    logger.registerStrategy( <strategy> );
 *    .....
 *    logger.registerStrategy( <strategy> );
 *
 * Now active/deactivate logger on your own.
 *
 *    logger.setUp();
 *    ......
 *    logger.tearDown();
 *
 */
class Logger
{
public:
  static Logger &getInstance ();

  /**
   * Activates logging and all registered strategies.
   */
  void setUp ();

  /**
   * Shutdowns logging and registered strategies.
   */
  void tearDown ();

  /**
   * Registers specific log strategy.
   * Logger support multiple strategies simultaneously
   * All strategies should be added before "setUp" call
   */
  void registerStrategy (std::unique_ptr<ILogStrategy> &&strategy);

  /**
   * Logs message.
   * Formats string and pass it to strategies.
   */
  void logMsg (ELogSeverity, const char *, va_list vlist) const;

private:
  char *mBuffer;
  const std::size_t mBufferSize = 2048;
  std::vector<std::unique_ptr<ILogStrategy> > mStrategies;
};

}

#endif /* API_LOGGER_HPP_ */
