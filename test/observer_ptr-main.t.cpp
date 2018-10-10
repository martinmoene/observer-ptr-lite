//
// Copyright (c) 2016-2018 Martin Moene
//
// https://github.com/martinmoene/observer_ptr
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "observer_ptr-main.t.hpp"

#define nsop_PRESENT( x ) \
    std::cout << #x << ": " << x << "\n"

#define nsop_ABSENT( x ) \
    std::cout << #x << ": (undefined)\n"

// Suppress:
// - unused parameter, for cases without assertions such as [.std...]
#if defined(__clang__)
# pragma clang diagnostic ignored "-Wunused-parameter"
#elif defined __GNUC__
# pragma GCC   diagnostic ignored "-Wunused-parameter"
#endif

lest::tests & specification()
{
    static lest::tests tests;
    return tests;
}

CASE( "observer_ptr version" "[.observer_ptr][.version]" )
{
    nsop_PRESENT( observer_ptr_MAJOR );
    nsop_PRESENT( observer_ptr_MINOR );
    nsop_PRESENT( observer_ptr_PATCH );
    nsop_PRESENT( observer_ptr_VERSION );
}

CASE( "observer_ptr configuration" "[.observer_ptr][.config]" )
{
    nsop_PRESENT( nsop_FEATURE_ALLOW_IMPLICIT_CONVERSION );
    nsop_PRESENT( nsop_CONFIG_CONFIRMS_COMPILATION_ERRORS );
}

CASE( "__cplusplus" "[.stdc++]" )
{
    nsop_PRESENT( __cplusplus );
}

CASE( "Compiler version" "[.compiler]" )
{
//  nsop_PRESENT( nsop_COMPILER_CLANG_VERSION );
//  nsop_PRESENT( nsop_COMPILER_GNUC_VERSION );
    nsop_PRESENT( nsop_COMPILER_MSVC_VERSION );
}

CASE( "Presence of C++ language features" "[.stdlanguage]" )
{
//  nsop_PRESENT( nsop_HAVE_AUTO );
//  nsop_PRESENT( nsop_HAVE_NULLPTR );
//  nsop_PRESENT( nsop_HAVE_STATIC_ASSERT );
//  nsop_PRESENT( nsop_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG );
//  nsop_PRESENT( nsop_HAVE_ALIAS_TEMPLATE );
//  nsop_PRESENT( nsop_HAVE_CONSTEXPR_11 );
//  nsop_PRESENT( nsop_HAVE_CONSTEXPR_14 );
//  nsop_PRESENT( nsop_HAVE_ENUM_CLASS );
//  nsop_PRESENT( nsop_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE );
//  nsop_PRESENT( nsop_HAVE_EXPLICIT_CONVERSION );
//  nsop_PRESENT( nsop_HAVE_INITIALIZER_LIST );
//  nsop_PRESENT( nsop_HAVE_IS_DEFAULT );
//  nsop_PRESENT( nsop_HAVE_IS_DELETE );
//  nsop_PRESENT( nsop_HAVE_NOEXCEPT );
}

CASE( "Presence of C++ library features" "[.stdlibrary]" )
{
//  nsop_PRESENT( nsop_HAVE_ARRAY );
//  nsop_PRESENT( nsop_HAVE_ADD_CONST );
//  nsop_PRESENT( nsop_HAVE_TR1_ADD_CONST );
//  nsop_PRESENT( nsop_HAVE_CONDITIONAL );
//  nsop_PRESENT( nsop_HAVE_CONTAINER_DATA_METHOD );
//  nsop_PRESENT( nsop_HAVE_REMOVE_CV );
//  nsop_PRESENT( nsop_HAVE_REMOVE_REFERENCE );
//  nsop_PRESENT( nsop_HAVE_TR1_REMOVE_REFERENCE );
//  nsop_PRESENT( nsop_HAVE_SIZED_TYPES );
//  nsop_PRESENT( nsop_HAVE_TYPE_TRAITS );
//  nsop_PRESENT( nsop_HAVE_TR1_TYPE_TRAITS );

#if defined _HAS_CPP0X
    nsop_PRESENT( _HAS_CPP0X );
#else
    nsop_ABSENT(  _HAS_CPP0X );
#endif
}

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include/nonstd -o observer_ptr-main.t.exe observer_ptr-main.t.cpp observer_ptr.t.cpp && observer_ptr.t.exe --pass
g++ -std=c++98 -I../include/nonstd -o observer_ptr-main.t.exe observer_ptr-main.t.cpp observer_ptr.t.cpp && observer_ptr.t.exe --pass
g++ -std=c++03 -I../include/nonstd -o observer_ptr-main.t.exe observer_ptr-main.t.cpp observer_ptr.t.cpp && observer_ptr.t.exe --pass
g++ -std=c++0x -I../include/nonstd -o observer_ptr-main.t.exe observer_ptr-main.t.cpp observer_ptr.t.cpp && observer_ptr.t.exe --pass
g++ -std=c++11 -I../include/nonstd -o observer_ptr-main.t.exe observer_ptr-main.t.cpp observer_ptr.t.cpp && observer_ptr.t.exe --pass
g++ -std=c++14 -I../include/nonstd -o observer_ptr-main.t.exe observer_ptr-main.t.cpp observer_ptr.t.cpp && observer_ptr.t.exe --pass
g++ -std=c++17 -I../include/nonstd -o observer_ptr-main.t.exe observer_ptr-main.t.cpp observer_ptr.t.cpp && observer_ptr.t.exe --pass

cl -EHsc -I../include/nonstd observer_ptr-main.t.cpp observer_ptr.t.cpp && observer_ptr-main.t.exe --pass
cl -EHsc -Dnsop_FEATURE_ALLOW_IMPLICIT_CONVERSION=1 -I../include/nonstd observer_ptr-main.t.cpp observer_ptr.t.cpp && observer_ptr-main.t.exe --pass
cl -EHsc -Dnsop_CONFIG_CONFIRMS_COMPILATION_ERRORS=1 -I../include/nonstd observer_ptr-main.t.cpp observer_ptr.t.cpp && observer_ptr-main.t.exe --pass
#endif

// end of file
