CLHEF
=====

Tools for the LHEF analyses using C++. If you want to use Haskell, see [lhef-tools](https://github.com/cbpark/lhef-tools).

## Usage

You'll need [cmake](http://www.cmake.org) in order to build and install.

```shell
git clone git@github.com:cbpark/CLHEF.git
cd CLHEF && mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/some/where ..
make
make install
```

Note that it will be installed in `/usr/local` unless you specify the path for the installation via `-DCMAKE_INSTALL_PREFIX`. See `src/test_parse.cc` and `src/test_render.cc` for the example usage.

## References

- [A standard format for Les Houches Event Files](http://arxiv.org/abs/hep-ph/0609017).
- [Les Houches Event File](http://home.thep.lu.se/~leif/LHEF/).
