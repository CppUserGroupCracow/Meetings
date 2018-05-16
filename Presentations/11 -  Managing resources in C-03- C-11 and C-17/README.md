Blog posts with contents covered in the meeting
* "C++'s best feature" - https://akrzemi1.wordpress.com/2013/07/18/cs-best-feature/
* "Move constructor" - https://akrzemi1.wordpress.com/2011/08/11/move-constructor/
* "'Resource' or 'Session'?" - https://akrzemi1.wordpress.com/2012/03/09/resource-or-session/
* "Sessions and object lifetimes" - https://akrzemi1.wordpress.com/2016/04/07/sessions-and-object-lifetimes/
* "Rvalues redefined" - https://akrzemi1.wordpress.com/2018/05/16/rvalues-redefined/

Online source code for working with non-movable types:
* https://wandbox.org/permlink/C2gH4pe9CSDL5DgJ

The source code of the program we were writing during the session:

```c++
#include <cstdio>
#include <stdexcept>
#include <cassert>
#include <boost/optional.hpp>
#include <mutex>
#include <type_traits>
#include <utility>

class File
{
  FILE* _h;
  // invariant:  _h != 0
  explicit File(FILE* h) : _h(h) {}
  
public:
  explicit File(const char * fname) : _h(fopen(fname, "r")) 
  {
    if (!_h)
      throw std::runtime_error("no File");
  }
  
  int get_char()
  { return  fgetc(_h); }
  
  ~File()
  {
    fclose(_h);
  }
  
  static File main_config() { return true ? File("config.ini") : File("e"); }
  static File backup_config() { return true ? File("config.ini") : File("e"); }
  
  friend File destructive_move(File& old) noexcept
  {
    return File{std::move(old._h)};
  }
  
  File( File&&) = delete;
};


template <typename T>
class Opt
{
  bool _init;
  std::aligned_storage_t<sizeof(T), alignof(T)> _store;
  void* address() { return &_store; }
  T* pointer() { return static_cast<T*>(address()); }
  
public:
  Opt() : _init(false) {}
  T& get()  { return assert(_init), *pointer(); }
  template <typename A>
  void emplace(A&& a) {
    // precondition: !_init;
    new (address()) T(std::forward<A>(a));
    _init = true;
  }
  
  ~Opt() { 
    if (_init) pointer()->T::~T();
  }
  
  T eject() 
  {
    assert(_init);
    _init = false;
    return destructive_move(*pointer());
  }
};

template <typename F>
struct rvalue
{
  F f;
  using ResultT = decltype(std::declval<F>()());
  explicit rvalue(F f_) : f(std::move(f_)) {}
  explicit operator ResultT () const { return f(); }
};

void test()
{
  Opt<File> of, og;
  of.emplace(rvalue{&File::main_config});
  putc(of.get().get_char(), stdout);
  
  og.emplace(rvalue{[&]{ return of.eject(); }});
  putc(og.get().get_char(), stdout);
}

struct R
{
  File _f;
  R(bool use_backup) : _f(use_backup ? File::main_config() : File::backup_config()) {}
};

int main()
{
  test();
}
```
