// The following code example is taken from the book w/o modification
// The C++ Standard Library - A Tutorial and Reference
// by Nicolai M. Josuttis, Addison-Wesley, 1999
// © Copyright Nicolai M. Josuttis 1999

#include <chrono>
#include <future>
#include <iostream>
#include <random>
#include <thread>

int do_something(char c)
{
  std::default_random_engine dre(c);
  std::uniform_int_distribution<int> id(10, 1000);
  for (int i = 0; i < 10; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
    std::cout.put(c).flush();
  }
  return c;
}

int func1()
{
  return do_something('.');
}

int func2()
{
  return do_something('+');
}

int main()
{
  std::cout << "starting func1() in background"
            << " and func2() in foreground:" << std::endl;

  auto result1 = std::async(func1);
  auto result2 = func2();
  auto result = result1.get() + result2;

  std::cout << "\nresult of func1()+func2(): " << result << std::endl;
}
