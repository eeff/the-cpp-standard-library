// The following code example is taken from the book w/o modification
// The C++ Standard Library - A Tutorial and Reference
// by Nicolai M. Josuttis, Addison-Wesley, 1999
// © Copyright Nicolai M. Josuttis 1999

#include <condition_variable>
#include <future>
#include <iostream>
#include <mutex>

bool g_ready_flag;
std::mutex g_ready_mutex;
std::condition_variable g_ready_condvar;

void thread1()
{
  std::cout << "<return>" << std::endl;
  std::cin.get();

  // signal that thread1 has prepared a condition
  {
    std::lock_guard<std::mutex> lg(g_ready_mutex);
    g_ready_flag = true;
  }
  g_ready_condvar.notify_one();
}

void thread2()
{
  // wait until thread1 is ready
  {
    std::unique_lock<std::mutex> ul(g_ready_mutex);
    g_ready_condvar.wait(ul, [] { return g_ready_flag; });
  }

  std::cout << "done" << std::endl;
}

int main()
{
  auto f1 = std::async(std::launch::async, thread1);
  auto f2 = std::async(std::launch::async, thread2);
}
