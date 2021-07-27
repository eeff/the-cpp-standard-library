// The following code example is taken from the book w/o modification
// The C++ Standard Library - A Tutorial and Reference
// by Nicolai M. Josuttis, Addison-Wesley, 1999
// © Copyright Nicolai M. Josuttis 1999

#include <iostream>
#include <random>
#include <sstream>

void print_numbers(std::default_random_engine& dre)
{
  for (int i = 0; i < 6; ++i) {
    std::cout << dre() << ' ';
  }
  std::cout << std::endl;
}

int main()
{
  // create engine and generate numbers
  std::default_random_engine dre;
  print_numbers(dre);

  // create equal engine and generate numbers
  std::default_random_engine dre2;
  print_numbers(dre2);

  // create engine with intial state specified by a seed
  std::default_random_engine dre3(42);
  print_numbers(dre3);

  // save state of engine
  std::stringstream engine_state;
  engine_state << dre;

  // generate numbers according to current state
  print_numbers(dre);

  // restore saved state of engine and create numbers again
  engine_state >> dre;
  print_numbers(dre);

  // restore saved state of engine dre, skip 2 numbers and create numbers agina
  engine_state.clear();  // clear EOF bit
  engine_state.seekg(0); // move read position to beginning
  engine_state >> dre;
  dre.discard(2);
  print_numbers(dre);
}
