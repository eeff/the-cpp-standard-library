// The following code example is taken from the book w/o modification
// The C++ Standard Library - A Tutorial and Reference
// by Nicolai M. Josuttis, Addison-Wesley, 1999
// © Copyright Nicolai M. Josuttis 1999

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

bool ready_flag;
std::mutex ready_flag_mutex;

void thread1()
{
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::lock_guard<std::mutex> lg(ready_flag_mutex);
  std::cout << "thread1 do something" << std::endl;
  ready_flag = true;
}

void thread2()
{
  std::unique_lock<std::mutex> ul(ready_flag_mutex);
  std::cout << "thread2 start" << std::endl;
  while (!ready_flag) {
    ul.unlock();
    std::cout << "thread2 waiting" << std::endl;
    std::this_thread::yield();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ul.lock();
  }
  std::cout << "thread2 end" << std::endl;
}

int main()
{
  std::thread t1(thread1);
  std::thread t2(thread2);
  t1.join();
  t2.join();
}
