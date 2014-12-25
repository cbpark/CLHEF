CLHEF
=====

Tools for the LHEF analyses using C++

## Usage

You'll need [cmake](http://www.cmake.org) in order to build and install.

```shell
git@github.com:cbpark/CLHEF.git
cd CLHEF && mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/some/where ..
make
make install
```

Note that it would be installed in `/usr/local` unless you specify the installation path via `-DCMAKE_INSTALL_PREFIX`.
