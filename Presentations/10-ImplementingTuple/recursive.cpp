#include <iostream>
#include <string>

namespace tuple_impl {

// (head, tail)
// g 0 (head, tail) -> head
// g N (head, tail) -> g N-1 tail;
struct construct_tag_t
{};

template<typename... Ts>
struct tuple_store;

template<>
struct tuple_store<>
{
  explicit tuple_store(construct_tag_t)
  {}
};

template<typename H, typename... T>
struct tuple_store<H, T...>
{
  using head_type = H;
  using tail_type = tuple_store<T...>;

  template<typename U, typename... Us>
  explicit tuple_store(construct_tag_t ct, U&& u, Us&&... us)
    : head(std::forward<U>(u)), tail(ct, std::forward<Us>(us)...)
  // forward<Us0>(us0), forward<Us1>(us1), ...
  {}

  head_type head;
  tail_type tail;
};

template<std::size_t I, typename Tuple>
struct tuple_getter;

template<typename Tuple>
struct tuple_getter<0, Tuple>
{
  using result_type = typename Tuple::head_type;

  result_type const& operator()(Tuple const& t) const
  {
    return t.head;
  }

  result_type& operator()(Tuple& t) const
  {
    return t.head;
  }

  result_type const&& operator()(Tuple const&& t) const
  {
    return std::move(t.head);
  }

  result_type&& operator()(Tuple&& t) const
  {
    return std::move(t.head);
  }
};

template<std::size_t I, typename Tuple>
struct tuple_getter
{
  using next = tuple_getter<I - 1, typename Tuple::tail_type>;
  using result_type = typename next::result_type;

  result_type const& operator()(Tuple const& t) const
  {
    return next{}(t.tail);
  }

  result_type& operator()(Tuple& t) const
  {
    return next{}(t.tail);
  }

  result_type const&& operator()(Tuple const&& t) const
  {
    return next{}(std::move(t.tail));
  }

  result_type&& operator()(Tuple&& t) const
  {
    return next{}(std::move(t.tail));
  }
};

};  // namespace tuple_impl

template<typename... Ts>
class tuple
{
  using store_type = tuple_impl::tuple_store<Ts...>;

public:
  template<typename... Us>
  tuple(Us&&... us)
    : store(tuple_impl::construct_tag_t{}, std::forward<Us>(us)...)
  {}

  template<std::size_t I>
  auto get() &
    -> typename tuple_impl::tuple_getter<I, store_type>::result_type&
  { return tuple_impl::tuple_getter<I, store_type>{}(store); }

  template<std::size_t I>
  auto get() const&
    -> typename tuple_impl::tuple_getter<I, store_type>::result_type const&
  { return tuple_impl::tuple_getter<I, store_type>{}(store); }

  template<std::size_t I>
  auto get() &&
    -> typename tuple_impl::tuple_getter<I, store_type>::result_type&&
  { return tuple_impl::tuple_getter<I, store_type>{}(std::move(store)); }

  template<std::size_t I>
  auto get() const&&
    -> typename tuple_impl::tuple_getter<I, store_type>::result_type const&&
  { return tuple_impl::tuple_getter<I, store_type>{}(std::move(store)); }


private:
  store_type store;
};

int main()
{
  tuple<int, std::string> t(1, std::string(72, 'a'));

  std::cout << t.get<1>() << std::endl;
  auto s2 = std::move(t).get<1>();
  std::cout << t.get<1>() << std::endl;

  auto s = foo().get<1>();
}
