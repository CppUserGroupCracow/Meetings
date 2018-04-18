#include <iostream>
#include <utility>

template<typename... Ts>
auto make_tuple(Ts&&... ts)
{
  return [ts...](auto&& f) mutable -> decltype(auto) { return f(ts...); };
}

struct none
{
  template<typename T>
  none(T&&)
  {}
};

template<std::size_t I>
using give_me_none = none;

template<std::size_t... Is>
auto make_getter(std::index_sequence<Is...>)
{
  return [](give_me_none<Is>..., auto& t, auto&&...) -> auto&
  {
    return t;
  };
}

template<std::size_t I, typename T>
decltype(auto) get(T& t)
{
  using indicies = std::make_index_sequence<I-1>;
  return t(make_getter(indicies{}));
}

template<typename T>
struct tier
{ 
  T val;
  
  template<typename Tuple>
  void operator=(Tuple& other) 
  {
    val([&other] (auto&... saved) {
       other([&saved...] (auto&&... source) {
          (int[]){(saved = source, void(), 1)...};
       });
    });
  }
};

template<typename... Ts>
auto tie(Ts&... ts)
{
  auto tied = [&ts...] (auto&& f) mutable -> decltype(auto) { return f(ts...); };

  return tier<decltype(tied)>{tied};
}

int main()
{
  auto&& t = make_tuple(1, 2, 3, 4);
  int i, j, k, l;
  tie(i,j,k,l) = t;
  std::cout << i << " " << j << " " << k << " " << l << std::endl;
}  
