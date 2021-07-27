// The following code example is taken from the book w/o modification
// The C++ Standard Library - A Tutorial and Reference
// by Nicolai M. Josuttis, Addison-Wesley, 1999
// © Copyright Nicolai M. Josuttis 1999

#include <iomanip>
#include <iostream>
#include <map>
#include <random>

template <typename Distr, typename Eng>
void distr(Distr d, Eng e, const std::string& name)
{
  std::cout << name << ":" << std::endl;
  std::cout << "- min(): " << d.min() << std::endl;
  std::cout << "- max(): " << d.max() << std::endl;
  std::cout << "- values: "
            << d(e) << ' '
            << d(e) << ' '
            << d(e) << ' '
            << d(e) << ' '
            << std::endl;

  // count the generated values (converted to integral values)
  std::map<long long, int> value_counter;
  for (int i = 0; i < 200'000; ++i) {
    value_counter[d(e)]++;
  }

  // print the resulting distribution
  std::cout << "====" << std::endl;
  for (auto elem : value_counter) {
    std::cout << std::setw(3) << elem.first << ": "
              << elem.second << std::endl;
  }
  std::cout << "====\n"
            << std::endl;
}

int main()
{
  std::knuth_b e;

  std::uniform_real_distribution<> ud(0, 10);
  distr(ud, e, "uniform_real_distribution");

  std::normal_distribution<> nd;
  distr(nd, e, "normal_distribution");

  std::exponential_distribution<> ed;
  distr(ed, e, "exponential_distribution");

  std::gamma_distribution<> gd;
  distr(gd, e, "gamma_distribution");
}
