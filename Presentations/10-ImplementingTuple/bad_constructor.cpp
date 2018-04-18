#include <iostream>

struct Verbose
{
  Verbose() = default;
  Verbose(Verbose const&) { std::cout << "Verbose(const&)" << std::endl; }
  Verbose(Verbose&&) { std::cout << "Verbose(&&)" << std::endl; }

  template<typename U>
  Verbose(U&&) { std::cout << "Versbose(U&&)" << std::endl; }
  // U = Verbose&
  // U&& = Verbose&

};

int main()
{
  Verbose cv;
  Verbose v(cv);
}

