# observer_ptr<> for C++98 up

[![Language](https://img.shields.io/badge/C%2B%2B-98/11/14/17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-BSL-blue.svg)](https://opensource.org/licenses/BSL-1.0) [![Build Status](https://travis-ci.org/martinmoene/observer-ptr-lite.svg?branch=master)](https://travis-ci.org/martinmoene/observer-ptr-lite) [![Build status](https://ci.appveyor.com/api/projects/status/6icjotc617wmhljt/branch/master?svg=true)](https://ci.appveyor.com/project/martinmoene/observer-ptr/branch/master) [![Version](https://badge.fury.io/gh/martinmoene%2Fobserver-ptr.svg)](https://github.com/martinmoene/observer-ptr/releases) [![download](https://img.shields.io/badge/latest-download-blue.svg)](https://raw.githubusercontent.com/martinmoene/observer-ptr/master/include/nonstd/observer_ptr.h)

*observer-ptr* is a single-file header-only library with a variant of std::experimental::observer_ptr [[1](#ref1)] for C++98 and later.

**Contents**  
- [Example usage](#example-usage)
- [In a nutshell](#in-a-nutshell)
- [License](#license)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Building the tests](#building-the-tests)
- [Synopsis](#synopsis)
- [Other open source implementations](#other-open-source-implementations)
- [Notes and references](#notes-and-references)
- [Appendix](#appendix)


Example usage
-------------
```
#include "nonstd/observer_ptr.hpp"

using namespace nonstd;

void use( observer_ptr<int> p )
{
    assert( *p == 42 );
}

int main()
{
    int a = 42;
    observer_ptr<int> p( &a );
    use( p );
}
```

### Compile and run

```
prompt>g++ -std=c++03 -Wall -I../include -o 01-basic.exe 01-basic.cpp && 01-basic.exe
```

In a nutshell
-------------
**observer-ptr** is an implementation of the *world’s dumbest smart pointer* for C++98 and higher. It takes no ownership responsibility for the object it *observes* or *watches* and is intended as a near drop-in replacement for raw pointer types. As a vocabulary type it indicates intended use, easing code reading ([Note 1](#note1)).

Class template `observer_ptr<>` has been proposed for inclusion into the C++ standard [1] and is part of Extensions for Library Fundamentals v2/v3 [[2](#ref2)][[3](#ref3)].

The *observer-ptr* of this project can be used with probably any clang, g++ or MSVC compiler. It has been tested with clang 3.4, g++ 5.2 and with VC6 (VS6, no comparison of observers), VC8 (VS2005), VC10 (VS2010), VC11 (VS2012), VC12 (VS2013), VC14 (VS2015).

License
-------
*observer-ptr* is distributed under the [Boost Software License](LICENSE.txt).
 

Dependencies
------------
*observer-ptr* has no other dependencies than the [C++ standard library](http://en.cppreference.com/w/cpp/header).


Installation
------------
*observer-ptr* is a single-file header-only library. Put [observer_ptr.h](include/nonstd/observer_ptr.h) in the [include](include) folder directly into the project source tree or somewhere reachable from your project.


Building the tests
------------------
To build the tests you need:

- [CMake](http://cmake.org), version 2.8.7 or later to be installed and in your PATH.
- A [suitable compiler](#reported-to-work-with). 

The [*lest* test framework](https://github.com/martinmoene/lest)  is included in the [test folder](test).
 
The following steps assume that the [*observer-ptr* source code](https://github.com/martinmoene/observer-ptr) has been cloned into a directory named `c:\observer-ptr`.

1. Create a directory for the build outputs for a particular architecture.  
Here we use c:\observer-ptr\build-win-x86-vc10.

        cd c:\observer-ptr
        md build-win-x86-vc10
        cd build-win-x86-vc10

2. Configure CMake to use the compiler of your choice (run `cmake --help` for a list).

        cmake -G "Visual Studio 10 2010" ..

3. Build the test suite in the Debug configuration (alternatively use Release).    

        cmake --build . --config Debug

4. Run the test suite.    

        ctest -V -C Debug

All tests should pass, indicating your platform is supported and you are ready to use *observer-ptr*.


Synopsis
--------

**Contents**  
[Documentation of `std::experimental::observer_ptr`](#documentation-of-stdobserver_ptr)  
[Configuration macros](#configuration-macros)  

### Documentation of `std::experimental::observer_ptr`

Depending on the compiler and C++-standard used, `nonstd::observer_ptr` behaves less or more like `std::experimental::observer_ptr`. To get an idea of the capabilities of `nonstd::observer_ptr` with your configuration, look at the output of the [tests](test/observer_ptr.t.cpp), issuing `observer_ptr-main.t --pass @`. For `std::experimental::observer_ptr`, see its [documentation at cppreference](https://en.cppreference.com/w/cpp/experimental/observer_ptr) [[5](#ref5)].  

### Configuration macros

#### Standard selection macro
\-D<b>nsop\_CPLUSPLUS</b>=199711L  
Define this macro to override the auto-detection of the supported C++ standard, or if your compiler does not set the `__cplusplus` macro correctly.

#### Select `std::experimental::observer_ptr` or `nonstd::observer_ptr`
At default, *observer-ptr lite* uses `std::experimental::observer_ptr` if it is available and lets you use it via namespace `nonstd`. You can however override this default and explicitly request to use `std::experimental::observer_ptr` or *observer-ptr lite*'s `nonstd::observer_ptr` as `nonstd::observer_ptr` via the following macros.

-D<b>nsop\_CONFIG\_SELECT\_OBSERVER_PTR</b>=nsop_OBSERVER_PTR_DEFAULT  
Define this to `nsop_OBSERVER_PTR_STD` to select `std::experimental::observer_ptr` as `nonstd::observer_ptr`. Define this to `nsop_OBSERVER_PTR_NONSTD` to select `nonstd::observer_ptr` as `nonstd::observer_ptr`. Default is undefined, which has the same effect as defining to `nsop_OBSERVER_PTR_DEFAULT`.

#### Conversions

\-D<b>nsop\_CONFIG\_ALLOW\_IMPLICIT\_CONVERSION</b>=0  
The proposed `observer_ptr` provides [explicit conversions](http://en.cppreference.com/w/cpp/language/explicit) to `bool` and to the underlying type. Explicit conversion is not available from pre-C++11 compilers. To prevent problems due to unexpected [implicit conversions](http://en.cppreference.com/w/cpp/language/implicit_cast) to `bool` or to the underlying type, this library does not provide these implicit conversions at default. If you still want them, define this macro to 1. Without these implicit conversions enabled, a conversion to bool via the [safe bool idiom](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Safe_bool) is provided. Default is 0.

#### Compile-time tests

\-D<b>nsop\_CONFIG\_CONFIRMS\_COMPILATION\_ERRORS</b>=0  
Define this macro to 1 to experience the by-design compile-time errors of the *observer-ptr* components in the test suite. Default is 0.


Other open source implementations
---------------------------------
- Mário Feroldi. [observer_ptr implementation in C++17 (Library Fundamentals TS v2)](https://github.com/feroldi/observer_ptr) (MIT License).


Notes and references
--------------------
### Notes
<a id="note1"></a>Note 1. This conclusion may be challenged if the coding style ensures that *any raw pointer* is a *non-owning pointer* [[4](#ref4)].  

### References
<a id="ref1"></a>[1] Walter E. Brown. [N3840: A Proposal for the World’s Dumbest Smart Pointer, v3](http://wg21.link/n3840) (PDF).1 January 2014.  
<a id="ref2"></a>[2] N4481: Tentative Working Draft, C++ Extensions for Library Fundamentals, Version 2, [Section 4.2 Non-owning pointers](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4481.html#memory.observer.ptr). 12 April 2015.  
<a id="ref3"></a>[3] N4758: Working Draft, C++ Extensions for Library Fundamentals, Version 3, [Section 5.2 Non-owning pointers](https://rawgit.com/cplusplus/fundamentals-ts/v3/fundamentals-ts.html#memory.observer.ptr). 13 November 2018.  
<a id="ref4"></a>[4] Bjarne Stroustrup. [P1408: Abandon observer_ptr](http://wg21.link/p1408). 4 January 2018.  
<a id="ref5"></a>[5] cppreference.com. [std&#58;&#58;experimental&#58;&#58;observer_ptr](http://en.cppreference.com/w/cpp/experimental/observer_ptr).  


Appendix
--------
### A.1 Observer Ptr test specification

```
Disallows to delete the observer_ptr unless implicit conversion allowed
Disallows construction from an observer_ptr of incompatible type
Disallows implicit conversion to bool unless implicit conversion allowed
Disallows implicit conversion to underlying type unless implicit conversion allowed
Disallows comparison to an observer_ptr with a different underlying type
Allows default construction
Allows construction from nullptr
Allows construction from a non-null pointer
Allows construction from an observer_ptr of compatible type
Allows to retrieve the pointer
Allows to retrieve the value pointed to
Allows to retrieve the member pointed to
Allows to test for a non-null pointer via conversion to bool
Allows to convert to the observed pointer
Allows to reset to stop observing
Allows to reset to observe another pointer
Allows to swap two observers
Specialized: Allows to swap two observers
Specialized: Allows to make an observer
Specialized: Allows to compare if an observer is equal to another observer
Specialized: Allows to compare if an observer is equal to another observer with a related watched type
Specialized: Allows to compare if an observer is not equal to another observer
Specialized: Allows to compare if an observer is not equal to another observer with a related watched type
Specialized: Allows to compare if an observer is equal to nullptr
Specialized: Allows to compare if an observer is not equal to nullptr
Specialized: Allows to compare if an observer is less than another observer
Specialized: Allows to compare if an observer is less than another observer with a related watched type
Specialized: Allows to compare if an observer is less than or equal to another observer
Specialized: Allows to compare if an observer is less than or equal to another observer with a related watched type
Specialized: Allows to compare if an observer is greater than another observer
Specialized: Allows to compare if an observer is greater than another observer with a related watched type
Specialized: Allows to compare if an observer is greater than or equal to another observer
Specialized: Allows to compare if an observer is greater than or equal to another observer with a related watched type
Specialized: Allows to compute hash
```
