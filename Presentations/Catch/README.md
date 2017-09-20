# Catch
_Catch.pdf_ contains presentation _( converted from Keynote )_ about C++ unit test framework.

## Bibilography

- https://github.com/philsquared/Catch
- https://martinfowler.com/bliki/UnitTest.html
- https://martinfowler.com/bliki/SelfTestingCode.html
- http://swing.fit.cvut.cz/projects/stx/doc/online/english/tools/misc/testfram.htm
- https://github.com/onqtam/doctest/blob/master/doc/markdown/tutorial.md
- https://www.amazon.com/Test-Driven-Development-Kent-Beck/dp/0321146530
- https://www.amazon.com/Extreme-Programming-Explained-Embrace-Change/dp/0321278658


## Examples
_Examples_ folder contains source code that was complementary of the speech. It uses CMake and [conan.io](https://www.conan.io).

### Build instruction
To perform the following script you need to install conan.io. [Here you can find installation instruction](http://docs.conan.io/en/latest/installation.html).
```
cd Examples
mkdir build
cd build
conan install ..
cmake ..
make -j8
```
