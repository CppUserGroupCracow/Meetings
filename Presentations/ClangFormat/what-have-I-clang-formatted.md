# What have I clang-formatted?

Wojtek Gumuła

---

### Prelude. Deliberation

- Ifs
- Whys
- Hows
---

### Act I. Preparation

```cpp
#include "matters.h"
#include "includes_order.h"

// clang-format off
deliberately()
  ^ formatted()
  ^ code();
// clang-format on
```
---

### Act II. Consummation

```bash
$ PAGER= git log --reverse --author Gumula --grep="clang-format" \
    --shortstat --format=
 18-04-06, 1 file changed, 2 insertions(+), 1 deletion(-)
 18-04-12, 1 file changed, 1 insertion(+), 1 deletion(-)
 18-04-19, 3295 files changed, 67099 insertions(+), 67552 deletions(-)
 18-04-20, 2256 files changed, 116558 insertions(+), 116030 deletions(-)
 18-05-02, 4 files changed, 45 insertions(+), 1 deletion(-)
 18-05-02, 198 files changed, 10107 insertions(+), 10507 deletions(-)
 18-05-18, 27 files changed, 92 insertions(+), 76 deletions(-)
 18-05-18, 1689 files changed, 341037 insertions(+), 307426 deletions(-)
 18-05-18, 7 files changed, 13 insertions(+), 17 deletions(-)
```

---

### Act III. Conclusion

Second thoughts and dreams

---

### Epilogue. Perpetuation

1. [Succeeding with clang-format](https://engineering.mongodb.com/post/succeeding-with-clangformat-part-1-pitfalls-and-planning)
2. [clang-format configurator](https://zed0.co.uk/clang-format-configurator/)
