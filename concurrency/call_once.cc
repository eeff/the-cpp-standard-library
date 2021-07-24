#include <future>
#include <iostream>
#include <mutex>
#include <thread>

std::once_flag g_once_flag;
std::string g_data;

void initialize_data()
{
  std::cout << "initializing static data" << std::endl;
  g_data = "this is the data";
}

std::mutex g_mutex;

void do_something()
{
  std::call_once(g_once_flag, initialize_data);
  std::lock_guard<std::mutex> guard(g_mutex);
  std::cout << "THREAD " << std::this_thread::get_id()
            << ": " << g_data << std::endl;
}

int main()
{
  auto f1 = std::async(std::launch::async, do_something);
  auto f2 = std::async(std::launch::async, do_something);
}
