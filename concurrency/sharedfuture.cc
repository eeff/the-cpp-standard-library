// The following code example is taken from the book w/o modification
// The C++ Standard Library - A Tutorial and Reference
// by Nicolai M. Josuttis, Addison-Wesley, 1999
// © Copyright Nicolai M. Josuttis 1999

#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>

int query_number()
{
  std::cout << "read number: ";
  int num;
  std::cin >> num;

  if (!std::cin) {
    throw std::runtime_error("no number read");
  }

  return num;
}

void do_something(char c, std::shared_future<int> f)
{
  try {
    // wait for number of characters to print
    int num = f.get();

    for (int i = 0; i < num; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      std::cout.put(c).flush();
    }
  } catch (const std::exception& e) {
    std::cerr << "EXCEPTION in thread " << std::this_thread::get_id()
              << ": " << e.what() << std::endl;
  }
}

int main()
{
  try {
    // start one task to query a number
    auto f = std::async(query_number).share();

    // start three tasks each processing this number in a loop
    auto f1 = std::async(std::launch::async, do_something, '.', f);
    auto f2 = std::async(std::launch::async, do_something, '+', f);
    auto f3 = std::async(std::launch::async, do_something, '*', f);

    f1.get();
    f2.get();
    f3.get();
  } catch (const std::exception& e) {
    std::cerr << "\nEXCEPTION: " << e.what() << std::endl;
  }
  std::cout << "\ndone" << std::endl;
}
