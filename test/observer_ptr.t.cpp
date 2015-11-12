// Copyright 2015 by Martin Moene
//
// nonstd::observer_ptr<> is a C++98 onward implementation for std::observer_ptr as of C++17.
//
// This code is licensed under the MIT License (MIT).
//

#include "observer_ptr.t.h"
#include <iostream>

lest::tests & specification()
{
    static lest::tests tests;
    return tests;
}

namespace {

CASE( "__cplusplus" )
{
    EXPECT( __cplusplus > 0L );
}

CASE( "Disallows to delete the observer_ptr (define nop_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if nop_CONFIG_CONFIRMS_COMPILATION_ERRORS
    int a = 7;
    observer_ptr<int> ap( &a );

    delete ap;
#endif
}

CASE( "Disallows construction from an observer_ptr of incompatible type (define nop_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
#if nop_CONFIG_CONFIRMS_COMPILATION_ERRORS
    int a = 7;

    observer_ptr<int>  ap( &a );
    observer_ptr<long> bp( ap );
#endif
}

CASE( "Allows default construction" )
{
    observer_ptr<int> p;

#if nop_HAVE_NULLPTR
    EXPECT( p.get() == nullptr );
#else
    EXPECT( p.get() == (void*)NULL );
#endif
}

CASE( "Allows construction from nullptr" )
{
#if nop_HAVE_NULLPTR
    observer_ptr<int> p( nullptr );

    EXPECT( p.get() == nullptr );
#else
    EXPECT( !!"nullptr is not available (no C++11)" );
#endif
}

CASE( "Allows construction from a non-null pointer" )
{
    int a = 7;

    observer_ptr<int> ap( &a );

    EXPECT( *ap == a );
}

CASE( "Allows construction from an observer_ptr of compatible type" )
{
    int  a = 7;

    observer_ptr<int>       ap( &a );
    observer_ptr<const int> bp( ap );

    EXPECT( *bp == a );
}

CASE( "Allows to retrieve the pointer" )
{
    int a = 7;

    observer_ptr<int> ap( &a );

    EXPECT( ap.get() == &a );
}

CASE( "Allows to retrieve the value pointed to" )
{
    int a = 7;

    observer_ptr<int> ap( &a );

    EXPECT( *ap == a );
}

struct S { S():a(7){} int a; };

CASE( "Allows to retrieve the member pointed to" )
{
    S s;

    observer_ptr<S> sp( &s );

    EXPECT( sp->a == s.a );
}

CASE( "Allows to test for a non-null pointer via conversion to bool (explicitly if available)" )
{
    int a = 7;

    observer_ptr<int> ap( &a );

    EXPECT( !!ap );
}

CASE( "Allows to convert to the observed pointer (explicitly if available)" )
{
    int a = 7;
    observer_ptr<int> ap( &a );
    int * q( ap );

    EXPECT( q == &a );
}

CASE( "Allows to reset to stop observing" )
{
    int a = 7;
    observer_ptr<int> ap( &a );

    ap.reset();

    EXPECT( ap.get() == (void*)NULL );
}

CASE( "Allows to reset to observe another pointer" )
{
    int a = 7;
    observer_ptr<int> ap;

    ap.reset( &a );

    EXPECT( ap.get() == &a );
}

CASE( "Allows to swap two observers" )
{
    int a = 7, b = 9;
    observer_ptr<int> ap( &a );
    observer_ptr<int> bp( &b );

    ap.swap( bp );

    EXPECT(  ap.get() == &b );
    EXPECT(  bp.get() == &a );
    EXPECT( *ap == b );
    EXPECT( *bp == a );
}

// specialized algorithms:

CASE( "Specialized: Allows to swap two observers" )
{
    int a = 7, b = 9;
    observer_ptr<int> ap( &a );
    observer_ptr<int> bp( &b );

    swap( ap, bp );

    EXPECT(  ap.get() == &b );
    EXPECT(  bp.get() == &a );
    EXPECT( *ap == b );
    EXPECT( *bp == a );
}

CASE( "Specialized: Allows to make an observer" )
{
    int a = 7;
    EXPECT( *make_observer( &a ) == a );
}

CASE( "Specialized: Allows to compare if an observer is equal to another observer" )
{
#if nop_COMPILER_MSVC_VERSION != 6
    int a = 7, b = 9;
    observer_ptr<int> ap( &a );
    observer_ptr<int> bp( &b );

    EXPECT(     ap == ap );
    EXPECT_NOT( ap == bp );
#else
    EXPECT( !!"op== yields 'operator ==' is ambiguous for VC6 " );
#endif
}

CASE( "Specialized: Allows to compare if an observer is not equal to another observer" )
{
#if nop_COMPILER_MSVC_VERSION != 6
    int a = 7, b= 9;
    observer_ptr<int> ap( &a );
    observer_ptr<int> bp( &b );

    EXPECT(     ap != bp );
    EXPECT_NOT( ap != ap );
#else
    EXPECT( !!"op== yields 'operator !=' is ambiguous for VC6 " );
#endif
}

CASE( "Specialized: Allows to compare if an observer is equal to nullptr" )
{
#if nop_HAVE_NULLPTR
    observer_ptr<int> p;

    EXPECT(       p == nullptr );
    EXPECT( nullptr == p       );
#else
    EXPECT( !!"nullptr is not available (no C++11)" );
#endif
}

CASE( "Specialized: Allows to compare if an observer is not equal to nullptr" )
{
#if nop_HAVE_NULLPTR
    int a = 7;
    observer_ptr<int> p( &a );

    EXPECT(       p != nullptr );
    EXPECT( nullptr != p       );
#else
    EXPECT( !!"nullptr is not available (no C++11)" );
#endif
}

CASE( "Specialized: Allows to compare if an observer is less than another observer" )
{
    int arr[] = { 7, 9, };
    observer_ptr<int> p1( &arr[0] );
    observer_ptr<int> p2( &arr[1] );

    EXPECT(     p1 < p2 );
    EXPECT_NOT( p2 < p1 );
}

CASE( "Specialized: Allows to compare if an observer is less than or equal to another observer" )
{
    int arr[] = { 7, 9, };
    observer_ptr<int> p1( &arr[0] );
    observer_ptr<int> p2( &arr[1] );

    EXPECT(     p1 <= p1 );
    EXPECT(     p1 <= p2 );
    EXPECT_NOT( p2 <= p1 );
}

CASE( "Specialized: Allows to compare if an observer is greater than another observer" )
{
    int arr[] = { 7, 9, };
    observer_ptr<int> p1( &arr[0] );
    observer_ptr<int> p2( &arr[1] );

    EXPECT(     p2 > p1 );
    EXPECT_NOT( p1 > p2 );
}

CASE( "Specialized: Allows to compare if an observer is greater than or equal to another observer" )
{
    int arr[] = { 7, 9, };
    observer_ptr<int> p1( &arr[0] );
    observer_ptr<int> p2( &arr[1] );

    EXPECT(     p1 >= p1 );
    EXPECT(     p2 >= p1 );
    EXPECT_NOT( p1 >= p2 );
}

CASE( "Specialized: Allows to compute hash" )
{
#if nop_CPP11_OR_GREATER
    int a = 7;
    auto h = std::hash< observer_ptr<int> >()( make_observer( &a ) );
    EXPECT( std::hash< observer_ptr<int> >()( make_observer( &a ) ) );
#else
    EXPECT( !!"hash is not available (no C++11)" );
#endif // nop_CPP11_OR_GREATER
}

} // namespace

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include -o observer_ptr.t.exe observer_ptr.t.cpp && observer_ptr.t.exe --pass
g++ -std=c++98 -I../include -o observer_ptr.t.exe observer_ptr.t.cpp && observer_ptr.t.exe --pass
g++ -std=c++03 -I../include -o observer_ptr.t.exe observer_ptr.t.cpp && observer_ptr.t.exe --pass
g++ -std=c++11 -I../include -o observer_ptr.t.exe observer_ptr.t.cpp && observer_ptr.t.exe --pass
g++ -std=c++14 -I../include -o observer_ptr.t.exe observer_ptr.t.cpp && observer_ptr.t.exe --pass
cl -EHsc -I../include observer_ptr.t.cpp && observer_ptr.t.exe --pass
cl -EHsc -I../include -Dnop_CONFIG_CONFIRMS_COMPILATION_ERRORS=1 observer_ptr.t.cpp && observer_ptr.t.exe --pass
#endif

// end of file
