# Introduction
A fast command-line interface to find words at [Wiktionary](http://en.wiktionary.org/).
## Note
This project, as of now, is fully unfinished.

# Build
I depend on CMake. Instructions assume your CWD is this project directory.
You are also required to have the following packages installed:
- `include-what-you-use` (v0.20)
- `clang`, `clang++` (v16)

Do it using GNU Make, or Ninja. No need to do both.

## GNU Make
```console
mkdir build
cd build
cmake ..
make package
```

## Ninja
Ninja uses parallelism by default, resulting in faster compilation.
```console
mkdir build
cd build
cmake .. -G Ninja
ninja package
```

## Note
You must install GNU Make or Ninja yourself. Use internet search engines
to figure that out.

# Install
Follow the build instructions. You should then be able to find `wiktionary-cli[.exe]` 
binary in the `build` directory.

If you would like, you can move it to somewhere like `$USER[/.local]/bin` 
or `%HOME%/bin` then add the folder to your PATH environment variable.
