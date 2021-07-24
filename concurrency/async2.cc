// The following code example is taken from the book w/o modification
// The C++ Standard Library - A Tutorial and Reference
// by Nicolai M. Josuttis, Addison-Wesley, 1999
// © Copyright Nicolai M. Josuttis 1999

#include <exception>
#include <future>
#include <iostream>
#include <list>

void task1()
{
  std::list<int> ls;
  // infinit loop
  while (true) {
    for (int i = 0; i < 1000'000; ++i) {
      ls.push_back(i);
    }
    std::cout.put('.').flush();
  }
}

int main()
{
  std::cout << "starting 2 tasks\n"
            << "- task1: process endless loop of memory consumption"
            << "- task2: wait for <return> and then for task1" << std::endl;

  auto fut = std::async(task1);

  std::cin.get();
  std::cout << "\nwait for the end of task1: " << std::endl;
  try {
    fut.get();
  } catch (const std::exception& e) {
    std::cerr << "EXCEPTION: " << e.what() << std::endl;
  }
}
