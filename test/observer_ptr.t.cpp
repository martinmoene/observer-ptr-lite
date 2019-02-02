// Copyright 2018-2019 by Martin Moene
//
// nonstd::observer_ptr<> is a C++98 onward implementation for std::observer_ptr as of C++17.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "observer_ptr-main.t.hpp"
#include <iostream>

using namespace nonstd;

namespace {

CASE( "Disallows to delete the observer_ptr unless implicit conversion allowed" )
{
#if nsop_CONFIG_CONFIRMS_COMPILATION_ERRORS
    int a = 7;
    observer_ptr<int> ap( &a );

    delete ap;
#else
    EXPECT( true );
#endif
}

CASE( "Disallows construction from an observer_ptr of incompatible type" )
{
#if nsop_CONFIG_CONFIRMS_COMPILATION_ERRORS
    int a = 7;

    observer_ptr<int>  ap( &a );
    observer_ptr<long> bp( ap );
#else
    EXPECT( true );
#endif
}

CASE( "Disallows implicit conversion to bool unless implicit conversion allowed" )
{
#if nsop_CONFIG_CONFIRMS_COMPILATION_ERRORS
# if nsop_HAVE_EXPLICIT_CONVERSION
    EXPECT( !!"no compilation failure: implicit conversion never used for C++11 (see nsop_CONFIG_ALLOW_IMPLICIT_CONVERSION_TO_UNDERLYING_TYPE)" );
# elif nsop_CONFIG_ALLOW_IMPLICIT_CONVERSION_TO_UNDERLYING_TYPE
    EXPECT( !!"no compilation failure: implicit conversion allowed for pre-C++11 (see nsop_CONFIG_ALLOW_IMPLICIT_CONVERSION_TO_UNDERLYING_TYPE)" );
# endif
    int a = 7;

    observer_ptr<int> ap( &a );

    if ( ap ) {}
#else
    EXPECT( true );
#endif
}

CASE( "Disallows implicit conversion to underlying type unless implicit conversion allowed" )
{
#if nsop_CONFIG_CONFIRMS_COMPILATION_ERRORS
# if nsop_HAVE_EXPLICIT_CONVERSION
    EXPECT( !!"no compilation failure: implicit conversion never used for C++11 (see nsop_CONFIG_ALLOW_IMPLICIT_CONVERSION_TO_UNDERLYING_TYPE)" );
# elif nsop_CONFIG_ALLOW_IMPLICIT_CONVERSION_TO_UNDERLYING_TYPE
    EXPECT( !!"no compilation failure: implicit conversion allowed for pre-C++11 (see nsop_CONFIG_ALLOW_IMPLICIT_CONVERSION_TO_UNDERLYING_TYPE)" );
# endif
    struct F { static void use( int * ) {} };
    int a = 7;
    observer_ptr<int> ap( &a );

    F::use( ap );
#else
    EXPECT( true );
#endif
}

CASE( "Disallows comparison to an observer_ptr with a different underlying type" )
{
#if nsop_CONFIG_CONFIRMS_COMPILATION_ERRORS
    int  a = 7; observer_ptr<int > ap( &a );
    long b = 9; observer_ptr<long> bp( &b );

    if ( ap == bp ) {}
    if ( ap != bp ) {}
#else
    EXPECT( true );
#endif
}

CASE( "Allows default construction" )
{
    observer_ptr<int> p;

#if nsop_HAVE_NULLPTR
    EXPECT( p.get() == nullptr );
#else
    EXPECT( p.get() == (void*)NULL );
#endif
}

CASE( "Allows construction from nullptr" )
{
#if nsop_HAVE_NULLPTR
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
#if nsop_COMPILER_MSVC_VERSION != 6
    int  a = 7;

    observer_ptr<int>       ap( &a );
    observer_ptr<const int> bp( ap );

    EXPECT( *bp == a );
#else
    EXPECT( !!"not in VC6 " );
#endif
}

CASE( "Allows implicit move-construction from a std::unique_ptr<>" " [smart-ptr]" )
{
#if nsop_CONFIG_ALLOW_IMPLICIT_CONVERSION_FROM_UNIQUE_PTR
#if nsop_HAVE_STD_SMART_PTRS
    auto up = std::unique_ptr<int>( new int(42) );

    observer_ptr<int> op( std::move(up) );

    EXPECT( *op == 42 );
#else
    EXPECT( !!"std::unique_ptr<> is not available (no C++11)" );
#endif
#else
    EXPECT( !!"observer_ptr: implicit conversion from smart pointers is not enabled (nsop_CONFIG_ALLOW_IMPLICIT_CONVERSION_FROM_UNIQUE_PTR)" );
#endif
}

CASE( "Allows implicit construction from a std::shared_ptr<>" " [smart-ptr]" )
{
#if nsop_CONFIG_ALLOW_IMPLICIT_CONVERSION_FROM_SHARED_PTR
#if nsop_HAVE_STD_SMART_PTRS
    auto sp = std::make_shared<int>( 42 );

    observer_ptr<int> op( sp );

    EXPECT( *op == 42 );
#else
    EXPECT( !!"std::shared_ptr<> is not available (no C++11)" );
#endif
#else
    EXPECT( !!"observer_ptr: implicit conversion from smart pointers is not enabled (nsop_CONFIG_ALLOW_IMPLICIT_CONVERSION_FROM_SHARED_PTR)" );
#endif
}

CASE( "Allows implicit construction from a std::weak_ptr<>" " [smart-ptr]" )
{
#if nsop_CONFIG_ALLOW_IMPLICIT_CONVERSION_FROM_WEAK_PTR
#if nsop_HAVE_STD_SMART_PTRS
    auto sp = std::make_shared<int>( 42 );

    observer_ptr<int> wp( sp );

    EXPECT( *wp == 42 );
#else
    EXPECT( !!"std::weak_ptr<> is not available (no C++11)" );
#endif
#else
    EXPECT( !!"observer_ptr: implicit conversion from smart pointers is not enabled (nsop_CONFIG_ALLOW_IMPLICIT_CONVERSION_FROM_WEAK_PTR)" );
#endif
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

CASE( "Allows to test for a non-null pointer via conversion to bool" )
{
    int a = 7;
    observer_ptr<int> ap( &a );

    if ( ap ) {}

    EXPECT( !!ap );
}

CASE( "Allows to convert to the observed pointer" )
{
#if nsop_HAVE_EXPLICIT_CONVERSION || nsop_CONFIG_ALLOW_IMPLICIT_CONVERSION_TO_UNDERLYING_TYPE
    int a = 7;
    observer_ptr<int> ap( &a );
    int * q( ap );

    EXPECT( q == &a );
#else
    EXPECT( !!"no explicit (no C++11) or implicit conversion (see nsop_CONFIG_ALLOW_IMPLICIT_CONVERSION_TO_UNDERLYING_TYPE)" );
#endif
}

CASE( "Allows to reset to stop observing" )
{
    int a = 7;
    observer_ptr<int> ap( &a );

    ap.reset();

    EXPECT( ap.get() == reinterpret_cast<void*>( NULL ) );
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
#if nsop_COMPILER_MSVC_VERSION != 6
    int a = 7, b = 9;
    observer_ptr<int> ap( &a );
    observer_ptr<int> bp( &b );

    EXPECT(     ap == ap );
    EXPECT_NOT( ap == bp );
#else
    EXPECT( !!"op== yields 'operator ==' is ambiguous for VC6 " );
#endif
}

CASE( "Specialized: Allows to compare if an observer is equal to another observer with a related watched type" )
{
#if nsop_COMPILER_MSVC_VERSION != 6
    int a = 7, b = 9;
    observer_ptr<      int> ap( &a );
    observer_ptr<const int> bp( &b );

    EXPECT(     ap == ap );
    EXPECT_NOT( ap == bp );
#else
    EXPECT( !!"op== yields 'operator ==' is ambiguous for VC6 " );
#endif
}

CASE( "Specialized: Allows to compare if an observer is not equal to another observer" )
{
#if nsop_COMPILER_MSVC_VERSION != 6
    int a = 7, b= 9;
    observer_ptr<int> ap( &a );
    observer_ptr<int> bp( &b );

    EXPECT(     ap != bp );
    EXPECT_NOT( ap != ap );
#else
    EXPECT( !!"op== yields 'operator !=' is ambiguous for VC6 " );
#endif
}

CASE( "Specialized: Allows to compare if an observer is not equal to another observer with a related watched type" )
{
#if nsop_COMPILER_MSVC_VERSION != 6
    int a = 7, b= 9;
    observer_ptr<int> ap( &a );
    observer_ptr<const int> bp( &b );

    EXPECT(     ap != bp );
    EXPECT_NOT( ap != ap );
#else
    EXPECT( !!"op== yields 'operator !=' is ambiguous for VC6 " );
#endif
}

CASE( "Specialized: Allows to compare if an observer is equal to nullptr" )
{
#if nsop_HAVE_NULLPTR
    int a = 7;
    observer_ptr<int> p;
    observer_ptr<int> q( &a );

    EXPECT(           p == nullptr );
    EXPECT_NOT(       q == nullptr );
    EXPECT(     nullptr == p       );
    EXPECT_NOT( nullptr == q       );
#else
    EXPECT( !!"nullptr is not available (no C++11)" );
#endif
}

CASE( "Specialized: Allows to compare if an observer is not equal to nullptr" )
{
#if nsop_HAVE_NULLPTR
    int a = 7;
    observer_ptr<int> p( &a );
    observer_ptr<int> q;

    EXPECT(           p != nullptr );
    EXPECT_NOT(       q != nullptr );
    EXPECT(     nullptr != p       );
    EXPECT_NOT( nullptr != q       );
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

CASE( "Specialized: Allows to compare if an observer is less than another observer with a related watched type" )
{
#if nsop_HAVE_OWN_COMMON_TYPE_STD
    int arr[] = { 7, 9, };
    observer_ptr<      int> p1( &arr[0] );
    observer_ptr<const int> p2( &arr[1] );

    EXPECT(     p1 < p2 );
    EXPECT_NOT( p2 < p1 );
#else
    EXPECT( !!"common_type is not available (no C++11, no VC12, 13, 14)" );
#endif
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

CASE( "Specialized: Allows to compare if an observer is less than or equal to another observer with a related watched type" )
{
#if nsop_HAVE_OWN_COMMON_TYPE_STD
    int arr[] = { 7, 9, };
    observer_ptr<      int> p1( &arr[0] );
    observer_ptr<const int> p2( &arr[1] );

    EXPECT(     p1 <= p1 );
    EXPECT(     p1 <= p2 );
    EXPECT_NOT( p2 <= p1 );
#else
    EXPECT( !!"common_type is not available (no C++11, no VC12, 13, 14)" );
#endif
}

CASE( "Specialized: Allows to compare if an observer is greater than another observer" )
{
    int arr[] = { 7, 9, };
    observer_ptr<int> p1( &arr[0] );
    observer_ptr<int> p2( &arr[1] );

    EXPECT(     p2 > p1 );
    EXPECT_NOT( p1 > p2 );
}

CASE( "Specialized: Allows to compare if an observer is greater than another observer with a related watched type" )
{
#if nsop_HAVE_OWN_COMMON_TYPE_STD
    int arr[] = { 7, 9, };
    observer_ptr<      int> p1( &arr[0] );
    observer_ptr<const int> p2( &arr[1] );

    EXPECT(     p2 > p1 );
    EXPECT_NOT( p1 > p2 );
#else
    EXPECT( !!"common_type is not available (no C++11, no VC12, 13, 14)" );
#endif
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

CASE( "Specialized: Allows to compare if an observer is greater than or equal to another observer with a related watched type" )
{
#if nsop_HAVE_OWN_COMMON_TYPE_STD
    int arr[] = { 7, 9, };
    observer_ptr<      int> p1( &arr[0] );
    observer_ptr<const int> p2( &arr[1] );

    EXPECT(     p1 >= p1 );
    EXPECT(     p2 >= p1 );
    EXPECT_NOT( p1 >= p2 );
#else
    EXPECT( !!"common_type is not available (no C++11, no VC12, 13, 14)" );
#endif
}

CASE( "Specialized: Allows to compute hash" )
{
#if nsop_CPP11_OR_GREATER
    int a = 7;
    EXPECT( std::hash< observer_ptr<int> >()( make_observer( &a ) ) );
#else
    EXPECT( !!"hash is not available (no C++11)" );
#endif // nsop_CPP11_OR_GREATER
}

} // namespace

// end of file
