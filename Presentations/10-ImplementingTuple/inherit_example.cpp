#include <iostream>

template<std::size_t I>
struct A
{
  int i;
};

struct C :  A<0>, A<1>
{};

template<std::size_t I>
int& getI(A<I>& t) 
{
  return t.i;
}

int main()
{
  C c;
  c.A<0>::i = 1;
  c.A<1>::i = 2;

  std::cout << getI<1>(c) << std::endl;
}
