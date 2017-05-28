# CLHEF

Tools for the [Les Houches Event File](http://home.thep.lu.se/~leif/LHEF/) (LHEF) analyses using C++. If you want to use Haskell, see [lhef-tools](https://github.com/cbpark/lhef-tools).

## Installation

```
git clone git@github.com:cbpark/CLHEF.git
./configure
make
make install-strip
```

If ROOT is not located in the system path, it can be set by `./configure --with-rootsys=path/of/root`.

### Prerequisite

- C++ compiler supporting C++14 features,
- (optional) [ROOT](https://root.cern.ch/).

## Usage

See `src/test_parse.cc` and `src/test_render.cc` for the example usage.

## References

- [A standard format for Les Houches Event Files](http://arxiv.org/abs/hep-ph/0609017).
- [Les Houches Event File](http://home.thep.lu.se/~leif/LHEF/).
