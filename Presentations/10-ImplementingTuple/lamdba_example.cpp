#include <iostream>

template<typename T1, typename T2>
auto make_tuple(T1&& t1, T2&& t2)
{
  return [t1 = std::forward<T1>(t1), t2 = std::forward<T2>(t2)](
           auto&& f) mutable -> decltype(auto) { return f(t1, t2); };
}

template<typename T>
decltype(auto) get1(T& t)
{
  return t([](auto& t, auto&) -> auto& { return t; });
}

template<typename T>
decltype(auto) get2(T& t)
{
  return t([](auto&, auto& t) -> auto& { return t; });
}

int main()
{
  auto t = make_tuple(1, 2);
  std::cout << get1(t) << std::endl;
  get1(t) = 3;
  std::cout << get1(t) << std::endl;
}
