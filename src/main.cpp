#include <api/itc/EventLoop.hpp>
#include <api/itc/EventThread.hpp>
#include <api/itc/InterThreadComm.hpp>
#include <api/logging/ConsoleLogStrategy.hpp>
#include <api/logging/Log.hpp>
#include <api/logging/Logger.hpp>
#include <iostream>
#include <thread>

int
main (int argc, char **argv)
{

  sf::Logger &logger = sf::Logger::getInstance ();
  logger.registerStrategy (std::make_unique<sf::ConsoleLogStrategy> ());
  logger.setUp ();

  std::vector<int> valueList;
  std::multimap<std::string, int> name2Id;

  name2Id.emplace ("Julia", 4);
  name2Id.emplace ("Lol", 5);

  auto lBound = name2Id.lower_bound ("Oleh");
  auto uBound = name2Id.upper_bound ("Oleh");

  for (auto it = lBound; it != uBound; ++it)
    std::cout << (*it).first << " => " << (*it).second << '\n';

  //
  //  sf::InterThreadComm &itcComm = sf::InterThreadComm::getInstance ();
  //  itcComm.setUp ();
  //
  //  sf::EventThread thread1;
  //  sf::EventThread thread2;
  //  sf::EventThread thread3;
  //
  //  thread1.run ();
  //  thread2.run ();
  //  thread3.run ();
  //
  //  std::this_thread::sleep_for (std::chrono::milliseconds (5000));
  //  auto &itcManager = sf::InterThreadComm::getInstance ();
  //  itcManager.sendEvent (thread2.getThreadInfo ()->id, sf::IEvent ());
  //
  //  std::this_thread::sleep_for (std::chrono::milliseconds (5000));
  //
  //  thread1.stop ();
  //  thread2.stop ();
  //  thread3.stop ();
  //  /* sf::InterThreadComm */ itcComm.tearDown ();
  /* sf::Logger */ logger.tearDown ();
}
