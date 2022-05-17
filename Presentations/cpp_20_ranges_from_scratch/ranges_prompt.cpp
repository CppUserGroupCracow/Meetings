#include <tuple>
#include <ranges>
#include <iostream>
#include <iterator>
#include <string_view>
#include <algorithm>

namespace myranges
{
template <std::ranges::view Prompt>
class prompt_line_view : public std::ranges::view_interface<prompt_line_view<Prompt>>
{
public:
  struct iterator;

  explicit prompt_line_view(Prompt prompt, std::istream& stream)
    : prompt_{prompt}
    , stream_{&stream}
  {
  }

  auto begin()
  {
    yield_with_prompt();
    return iterator{this};
  }

  auto end()
  {
    return std::default_sentinel;
  }

  void yield_with_prompt()
  {
    std::ranges::copy(prompt_, std::ostream_iterator<std::ranges::range_value_t<Prompt>>{std::cout});
    std::cout << std::flush;
    std::getline(*stream_, line_);
  }

private:
  Prompt prompt_;
  std::istream* stream_{nullptr};
  std::string line_{};
};

template <typename T>
prompt_line_view(T&& prompt, auto&&...) -> prompt_line_view<std::views::all_t<T>>;

template <typename Prompt>
struct prompt_line_view<Prompt>::iterator
{
  using value_type = std::string;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::input_iterator_tag;

  prompt_line_view* parent;

  auto& operator++()
  {
    parent->yield_with_prompt();
    return *this;
  }

  void operator++(int) { ++*this; }
  const auto& operator*() const { return parent->line_; }
  bool operator==(std::default_sentinel_t) const { return !*(parent->stream_); }
};
}  // namespace myranges

namespace myviews
{
namespace detail
{
template <typename Adaptor, typename... Args>
struct partial_fn
{
  std::tuple<Args...> args;

  partial_fn(Args... args)
    : args{std::move(args)...}
  {
  }

  template <typename R>
  friend decltype(auto) operator|(R&& r, partial_fn adaptor)
  {
    return std::apply([&r](auto&&... args)
      {
        return Adaptor{}(std::forward<R>(r), static_cast<std::unwrap_ref_decay_t<Args>&&>(args)...);
      }, adaptor.args);
  }
};
}
struct prompt_line_fn
{
  template <typename R>
  auto operator()(R&& r, std::istream& stream) const
  {
    return myranges::prompt_line_view{std::forward<R>(r), stream};
  }

  auto operator()(std::istream& stream) const
  {
    return detail::partial_fn<prompt_line_fn, std::reference_wrapper<std::istream>>(stream);
  }

  template <typename R>
  friend decltype(auto) operator|(R&& r, prompt_line_fn adaptor)
  {
    return adaptor(std::forward<R>(r), std::cin);
  }
};

inline constexpr prompt_line_fn prompt_line{};
}  // namespace myviews

template <typename T>
inline constexpr bool std::ranges::enable_borrowed_range<myranges::prompt_line_view<T>> = true;

int main()
{
  using namespace std::literals;
  using V = decltype(myranges::prompt_line_view("test>"sv, std::cin));
  static_assert(std::input_or_output_iterator<std::ranges::iterator_t<V>>);
  static_assert(std::ranges::range<V>);
  static_assert(std::ranges::view<V>);
  static_assert(std::ranges::input_range<V>);
  static_assert(std::ranges::borrowed_range<V>);
  auto cli_loop = 
    // myranges::prompt_line_view("sqlite> "sv, std::cin)
    "sqlite> "
    | myviews::prompt_line(std::cin)
    | std::views::take_while([](auto command) { return command != ".exit"sv; });
  for (auto&& line : cli_loop)
  {
    std::cout << "handle_command(\"" << line << "\")\n";
  }
}
