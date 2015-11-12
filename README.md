# observer_ptr<> for C++98 up&ensp;[![Build Status](https://travis-ci.org/martinmoene/observer-ptr.svg?branch=master)](https://travis-ci.org/martinmoene/observer-ptr) [![Build status](https://ci.appveyor.com/api/projects/status/6icjotc617wmhljt/branch/master?svg=true)](https://ci.appveyor.com/project/martinmoene/observer-ptr/branch/master)

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
#include "nonstd/observer_ptr.h"

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
**observer-ptr** is an implementation of the *world’s dumbest smart pointer* for C++98 and higher. It takes no ownership responsibility for the object it *observes* or *watches* and is intended as a near drop-in replacement for raw pointer types. As a vocabulary type it indicates intended use, easing code reading. [1]

Class template `observer_ptr<>` has been proposed for and accepted into C++17 [2][3].

The *observer-ptr* of this project can be used with probably any clang, g++ or MSVC compiler. It has been tested with clang 3.4, g++ 5.2 and with VC6 (VS6, no comparison of observers), VC8 (VS2005), VC10 (VS2010), VC12 (VS2012), VC13 (VS2013), VC14 (VS2015).

License
-------
*observer-ptr* uses the [MIT](LICENSE) license.
 

Dependencies
------------
*observer-ptr* has no other dependencies than the [C++ standard library](http://en.cppreference.com/w/cpp/header).


Installation
------------
*observer-ptr* is a single-file header-only library. Put `observer-ptr.h` in the [include](include) folder directly into the project source tree or somewhere reachable from your project.


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

### Configuration macros

\-D<b>nop\_CONFIG\_CONFIRMS\_COMPILATION\_ERRORS</b>=0  
Define this macro to 1 to experience the by-design compile-time errors of the *observer-ptr* components in the test suite. Default is 0.


Other open source implementations
---------------------------------
None known.


Notes and references
--------------------
### Notes
[1] This conclusion may be challenged if the coding style ensures that *any raw pointer* is a *non-owning pointer.*

### References
[2] Walter E. Brown. [N3840: A Proposal for the World’s Dumbest Smart Pointer, v3](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n3840.pdf) (PDF).1 January 2014.  
[3] N4481: Tentative Working Draft, C++ Extensions for Library Fundamentals, Version 2 [Section 4.2 Non-owning pointers](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4481.html#memory.observer.ptr). 12 April 2015.  


Appendix
--------
### A.1 Observer Ptr test specification

```
Disallows to delete the observer_ptr (define nop_CONFIG_CONFIRMS_COMPILATION_ERRORS)
Disallows construction from an observer_ptr of incompatible type (define nop_CONFIG_CONFIRMS_COMPILATION_ERRORS)
Allows default construction
Allows construction from nullptr
Allows construction from a non-null pointer
Allows construction from an observer_ptr of compatible type
Allows to retrieve the pointer
Allows to retrieve the value pointed to
Allows to retrieve the member pointed to
Allows to test for a non-null pointer via conversion to bool (explicitly if available)
Allows to convert to the observed pointer (explicitly if available)
Allows to reset to stop observing
Allows to reset to observe another pointer
Allows to swap two observers
Specialized: Allows to swap two observers
Specialized: Allows to make an observer
Specialized: Allows to compare if an observer is equal to another observer
Specialized: Allows to compare if an observer is not equal to another observer
Specialized: Allows to compare if an observer is equal to nullptr
Specialized: Allows to compare if an observer is not equal to nullptr
Specialized: Allows to compare if an observer is less than another observer
Specialized: Allows to compare if an observer is less than or equal to another observer
Specialized: Allows to compare if an observer is greater than another observer
Specialized: Allows to compare if an observer is greater than or equal to another observer
Specialized: Allows to compute hash
```
