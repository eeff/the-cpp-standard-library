// The following code example is taken from the book w/o modification
// The C++ Standard Library - A Tutorial and Reference
// by Nicolai M. Josuttis, Addison-Wesley, 1999
// © Copyright Nicolai M. Josuttis 1999

#include <atomic>
#include <future>
#include <iostream>
#include <thread>

long g_data;
std::atomic<bool> g_ready_flag(false);

void provider()
{
  std::cout << "<return>" << std::endl;
  std::cin.get();

  // provide some data
  g_data = 42;

  // and signal readiness
  g_ready_flag.store(true, std::memory_order_release);
}

void consumer()
{
  // wait for readiness and do something else
  while (!g_ready_flag.load(std::memory_order_acquire)) {
    std::cout.put('.').flush();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  std::cout << "\nvalue: " << g_data << std::endl;
}

int main()
{
  auto p = std::async(std::launch::async, provider);
  auto c = std::async(std::launch::async, consumer);
}
