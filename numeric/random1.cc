// The following code example is taken from the book w/o modification
// The C++ Standard Library - A Tutorial and Reference
// by Nicolai M. Josuttis, Addison-Wesley, 1999
// © Copyright Nicolai M. Josuttis 1999

#include <algorithm>
#include <iostream>
#include <random>

int main()
{
  // create default random engine for randomness
  std::default_random_engine dre;

  // use engine to generate integral values between 10 and 20 (both included)
  std::uniform_int_distribution<int> di(10, 20);
  for (int i = 0; i < 20; ++i) {
    std::cout << di(dre) << ' ';
  }
  std::cout << std::endl;

  // use engine to generate floating point values between 10.0 and 20.0
  // (10.0 included, 20.0 excluded)
  std::uniform_real_distribution<double> dr(10, 20);
  for (int i = 0; i < 20; ++i) {
    std::cout << dr(dre) << ' ';
  }
  std::cout << std::endl;

  // use engine to shuffle elements
  std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  std::shuffle(v.begin(), v.end(), dre);
  for (auto i : v) {
    std::cout << i << ' ';
  }
  std::cout << std::endl;
}
