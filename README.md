# lharmony

A C++ library for working with musical harmony

## Features

This library provides classes for representing various harmony-related concepts, such as pitch, pitch
class, scales, intervals, and chords.

## Portability

This library is tested on Mac, Windows, and Linux (with GCC, Clang, and MSVC), as well as cross-compiled
for iOS, tvOS, watchOS, and Emscripten (WebAssembly).

## Building

This library is built with CMake. CMake presets are provided for each of the toolchains we target. This
library supports being added to other CMake projects via `find_package()`, `FetchContent`, or a plain
`add_subdirectory()`. In all cases, you should link against the target `limes::lharmony` and include
the main header this way:
```cpp
#include <lharmony/lharmony.h>
```
All of this library's headers can be individually included, but including `lharmony.h` is the easiest
way to bring in the entire library.

## Links

[CDash testing dashboard](https://my.cdash.org/index.php?project=lharmony)

[Documentation](https://benthevining.github.io/lharmony/)
