# CLHEF

Tools for the [Les Houches Event File](http://home.thep.lu.se/~leif/LHEF/) (LHEF) analyses using C++. If you want to use Haskell, see [lhef-tools](https://github.com/cbpark/lhef-tools).

## Installation

```
./configure
make
make install
```

If ROOT is not located in the system path, it can be set by `./configure --with-rootsys=path/of/root`.

### Prerequisite

- C++ compiler supporting C++11 features ([Clang](http://clang.llvm.org/cxx_status.html) >= 3.3, [GCC](https://gcc.gnu.org/projects/cxx-status.html) >= 4.8.1),
- (optional) [ROOT](https://root.cern.ch/).

## Usage

``` c++
#include <fstream>
#include <iostream>
#include "clhef/lhef.h"

int main(int, char *argv[]) {
    std::ifstream fin(argv[1]);
    auto lhe = lhef::parseEvent(&fin);
    for (int ieve = 0; !lhe.done(); lhe = lhef::parseEvent(&fin), ++ieve) {
        std::cout << "-- Event number: " << ieve + 1 << '\n';
        const auto final_states{lhef::finalStates(lhe)};
        std::cout << lhef::show(final_states) << '\n';
    }
}
```

See [`src/test_parse.cc`](src/test_parse.cc) and [`src/test_render.cc`](src/test_render.cc) for the example usage.

## References

- [A standard format for Les Houches Event Files](http://arxiv.org/abs/hep-ph/0609017).
- [Les Houches Event File](http://home.thep.lu.se/~leif/LHEF/).
