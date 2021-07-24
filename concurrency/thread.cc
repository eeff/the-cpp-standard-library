// The following code example is taken from the book w/o modification
// The C++ Standard Library - A Tutorial and Reference
// by Nicolai M. Josuttis, Addison-Wesley, 1999
// © Copyright Nicolai M. Josuttis 1999

#include <chrono>
#include <exception>
#include <iostream>
#include <random>
#include <thread>

void do_something(int num, char c)
{
  try {
    std::default_random_engine dre(42 * c);
    std::uniform_int_distribution<int> id(10, 1000);
    for (int i = 0; i < num; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
      std::cout.put(c).flush();
    }
  } catch (const std::exception& e) {
    std::cerr << "THREAD-EXCEPTION (thread "
              << std::this_thread::get_id() << "): " << e.what() << std::endl;
  } catch (...) {
    std::cerr << "THREAD-EXCEPTION (thread "
              << std::this_thread::get_id() << ")" << std::endl;
  }
}

int main()
{
  try {
    std::thread t1(do_something, 5, '.'); // print five dots in separate thread
    std::cout << "- started fg thread " << t1.get_id() << std::endl;

    for (int i = 0; i < 5; ++i) {
      std::thread t(do_something, 10, 'a' + i); // print ten chars in separate thread
      std::cout << "- detach started bg thread " << t.get_id() << std::endl;
      t.detach();
    }

    std::cin.get(); // wait for any input (return)

    std::cout << "- join fg thread " << t1.get_id() << std::endl;
    t1.join();
  } catch (const std::exception& e) {
    std::cerr << "EXCEPTION: " << e.what() << std::endl;
  }
}
