// The following code example is taken from the book w/o modification
// The C++ Standard Library - A Tutorial and Reference
// by Nicolai M. Josuttis, Addison-Wesley, 1999
// © Copyright Nicolai M. Josuttis 1999

#include <exception>
#include <future>
#include <iostream>

void do_something(std::promise<std::string> p)
{
  try {
    // read character and throw excepton if `x`
    std::cout << "read char ('x' for exception): ";
    char c = std::cin.get();
    if ('x' == c) {
      throw std::runtime_error(std::string("char ") + c + " read");
    }

    std::string s = std::string("char ") + c + " processed";
    p.set_value(std::move(s));
  } catch (...) {
    p.set_exception(std::current_exception());
  }
}

int main()
{
  try {
    // create promise-future pair
    std::promise<std::string> p;
    auto f = p.get_future();

    // start thread using a promise to store the outcome
    std::thread t(do_something, std::move(p));
    t.detach();

    std::cout << "result " << f.get() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "EXCEPTION: " << e.what() << std::endl;
  } catch (...) {
    std::cerr << "EXCEPTION" << std::endl;
  }
}
