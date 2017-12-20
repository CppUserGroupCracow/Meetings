There was no PPT presentation in this meeting. Instead, I provide some materials.

* blog posts on the same topic:
  * https://akrzemi1.wordpress.com/2017/12/02/your-own-type-predicate/
  * https://akrzemi1.wordpress.com/2017/12/20/a-friendly-type-predicate/
* code samples on Wandbox:
  * with just `void_t`: https://wandbox.org/permlink/8acxSWTEq3u5G5sk
  * with function signature: https://wandbox.org/permlink/G0uZ5D5sOqk1hGOc
  * with detailed diagnostic messages: https://wandbox.org/permlink/U8KDLBik9xOrXevX
* Tick library: https://github.com/pfultz2/Tick
* Tick solution:

```c++
#include <tick/builder.h>

TICK_TRAIT(is_computer)
{
  template <typename T,
            typename ResultT = typename T::result_type>
  auto require (T x) -> valid<
    decltype(T::set_limit(1)),
    decltype(x.get_result()),
    is_true_c<noexcept(x.get_result())>,
    decltype(returns<ResultT const&>(x.get_result()))
  >;
};
```
