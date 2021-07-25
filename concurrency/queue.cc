// The following code example is taken from the book w/o modification
// The C++ Standard Library - A Tutorial and Reference
// by Nicolai M. Josuttis, Addison-Wesley, 1999
// © Copyright Nicolai M. Josuttis 1999

#include <chrono>
#include <condition_variable>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

std::mutex g_queue_mutex;
std::queue<int> g_queue;
std::condition_variable g_queue_condvar;

void provider(int val)
{
  // push different values into the queue
  for (int i = 0; i < 6; ++i) {
    {
      std::lock_guard<std::mutex> lg(g_queue_mutex);
      g_queue.push(val + i);
    }
    g_queue_condvar.notify_one();
    std::this_thread::sleep_for(std::chrono::milliseconds(val));
  }
}

void consumer(int num)
{
  // pop values if available
  while (true) {
    int val;
    {
      std::unique_lock<std::mutex> ul(g_queue_mutex);
      g_queue_condvar.wait(ul, [] { return !g_queue.empty(); });
      val = g_queue.front();
      g_queue.pop();
    }
    std::cout << "consumer " << num << ": " << val << std::endl;
  }
}

int main()
{
  // start three providers
  auto p1 = std::async(std::launch::async, provider, 100);
  auto p2 = std::async(std::launch::async, provider, 300);
  auto p3 = std::async(std::launch::async, provider, 500);

  // start two consumers
  auto c1 = std::async(std::launch::async, consumer, 1);
  auto c2 = std::async(std::launch::async, consumer, 2);
}
