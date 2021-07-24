// The following code example is taken from the book w/o modification
// The C++ Standard Library - A Tutorial and Reference
// by Nicolai M. Josuttis, Addison-Wesley, 1999
// © Copyright Nicolai M. Josuttis 1999

#include <future>
#include <iostream>
#include <mutex>

std::mutex print_mutex;

void print(const std::string& s)
{
  std::lock_guard<std::mutex> guard(print_mutex);
  for (char c : s) {
    std::cout.put(c);
  }
  std::cout << std::endl;
}

int main()
{
  auto f1 = std::async(std::launch::async, print, "Hello from first thread");
  auto f2 = std::async(std::launch::async, print, "Hello from second thread");
  print("Hello from main thread");
}
