#include <iostream>
#include <string>
#include <utility>

namespace tuple_impl {

// (head, tail)
// g 0 (head, tail) -> head
// g N (head, tail) -> g N-1 tail;
struct construct_tag_t
{};

template<std::size_t I, typename T>
struct tuple_element
{
  using type = T;

  template<typename U>
  explicit tuple_element(construct_tag_t, U&& u) : val(std::forward<U>(u))
  {}

  T val;
};

template<typename Indicies, typename... Ts>
struct tuple_store;

template<std::size_t... Is, typename... T>
struct tuple_store<std::index_sequence<Is...>, T...> : tuple_element<Is, T>...
{
  template<typename... Us>
  explicit tuple_store(construct_tag_t ct, Us&&... us)
    : tuple_element<Is, T>(ct, std::forward<Us>(us))...
  // forward<Us0>(us0), forward<Us1>(us1), ...
  {}
};

template<std::size_t I>
struct tuple_getter
{
  template<typename T>
  static T get_result(tuple_element<I, T> const&);

  template<typename Tuple>
  using result_type = decltype(get_result(std::declval<Tuple const&>()));

  template<typename T>
  T& operator()(tuple_element<I, T>& t) const
  {
    return t.val;
  }

  template<typename T>
  T const& operator()(tuple_element<I, T> const& t) const
  {
    return t.val;
  }

  template<typename T>
  T&& operator()(tuple_element<I, T>&& t) const
  {
    return std::move(t.val);
  }

  template<typename T>
  T const&& operator()(tuple_element<I, T> const&& t) const
  {
    return std::move(t.val);
  }
};

};  // namespace tuple_impl

template<typename... Ts>
class tuple
{
  using indicies = std::make_index_sequence<sizeof...(Ts)>;
  using store_type = tuple_impl::tuple_store<indicies, Ts...>;

public:
  template<
    typename... Us,
    typename std::enable_if<sizeof...(Ts) == sizeof...(Us), bool>::type = true>
  tuple(Us&&... us)
    : store(tuple_impl::construct_tag_t{}, std::forward<Us>(us)...)
  {}

  template<std::size_t I>
  auto get() & ->
    typename tuple_impl::tuple_getter<I>::template result_type<store_type>&
  {
    return tuple_impl::tuple_getter<I>{}(store);
  }

  template<std::size_t I>
  auto get() const& -> typename tuple_impl::tuple_getter<
    I>::template result_type<store_type> const&
  {
    return tuple_impl::tuple_getter<I>{}(store);
  }

  template<std::size_t I>
  auto get() && ->
    typename tuple_impl::tuple_getter<I>::template result_type<store_type>&&
  {
    return tuple_impl::tuple_getter<I>{}(std::move(store));
  }

  template<std::size_t I>
  auto get() const&& -> typename tuple_impl::tuple_getter<
    I>::template result_type<store_type> const&&
  {
    return tuple_impl::tuple_getter<I>{}(std::move(store));
  }

private:
  store_type store;
};

template<typename... Ts>
tuple<typename std::decay<Ts>::type...> make_tuple(Ts&&... ts)
{
  return tuple<typename std::decay<Ts>::type...>(std::forward<Ts>(ts)...);
}

template<typename... Ts>
tuple<Ts&...> tie(Ts&... ts)
{
  return tuple<Ts&...>(ts...);
}

int main()
{
  tuple<int, std::string> t(1, std::string(72, 'a'));

  std::cout << t.get<1>() << std::endl;
  auto s2 = std::move(t).get<1>();
  std::cout << t.get<1>() << std::endl;
}
