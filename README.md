# Introduction
A fast command-line interface to find words at [Wiktionary](http://en.wiktionary.org/).
## Note
This project, as of now, is fully unfinished.

# How to build
I depend on CMake. Instructions assume your CWD is this project directory.

## Build
```console
mkdir build
cd build
cmake ..
make package
```

## Install
Follow the build instructions. You should then be able to find `wiktionary-cli[.exe]` 
binary in the `build` directory.

If you would like, you can move it to somewhere like `$USER[/.local]/bin` 
or `%USER%/bin` then add the folder to your PATH environment variable.
