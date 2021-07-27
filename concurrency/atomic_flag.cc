#include <atomic>
#include <chrono>
#include <future>
#include <iostream>
#include <thread>

std::atomic<bool> g_ready_flag(false);

void thread1()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  g_ready_flag.store(true);
}

void thread2()
{
  while (!g_ready_flag.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "waiting for ready flag" << std::endl;
  }
  std::cout << "done" << std::endl;
}

int main()
{
  auto f1 = std::async(std::launch::async, thread1);
  auto f2 = std::async(std::launch::async, thread2);
}
