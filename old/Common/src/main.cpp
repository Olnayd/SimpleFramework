#include <iostream>
#include <itc/EventLoop.hpp>
#include <thread>

sf::EventLoop loop;

void test_thread (/*sf::EventLoop &loop*/)
{
  std::cout << "Here 1;";
  loop.start ();
  std::cout << "Here 2;";
}

int
main (int argc, char **argv)
{
  std::cout << "Start;";
  std::cout << "Start;";
  std::cout << "Start;";

  std::thread test (test_thread);
  test.join ();

  //
  //  std::this_thread::sleep_for (std::chrono::milliseconds (20000));
  //  loop.stop ();
}
