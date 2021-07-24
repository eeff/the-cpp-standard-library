// The following code example is taken from the book w/o modification
// The C++ Standard Library - A Tutorial and Reference
// by Nicolai M. Josuttis, Addison-Wesley, 1999
// © Copyright Nicolai M. Josuttis 1999

#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <random>
#include <thread>

void do_something(char c)
{
  std::default_random_engine dre(c);
  std::uniform_int_distribution<int> id(10, 1000);

  for (int i = 0; i < 10; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
    std::cout.put(c).flush();
  }
}

int main()
{
  std::cout << "starting 2 operations asynchronously" << std::endl;

  auto f1 = std::async([] { do_something('.'); });
  auto f2 = std::async([] { do_something('+'); });

  if (
      f1.wait_for(std::chrono::seconds(0)) != std::future_status::deferred
      || f2.wait_for(std::chrono::seconds(0)) != std::future_status::deferred) {
    // poll at least one of the tasks finished
    while (
        f1.wait_for(std::chrono::seconds(0)) != std::future_status::ready
        && f2.wait_for(std::chrono::seconds(0)) != std::future_status::ready) {
      std::this_thread::yield();
    }
  }
  std::cout.put('\n').flush();

  try {
    f1.get();
    f2.get();
  } catch (const std::exception& e) {
    std::cout << "\nEXCEPTION: " << e.what() << std::endl;
  }
  std::cout << "\ndone" << std::endl;
}
