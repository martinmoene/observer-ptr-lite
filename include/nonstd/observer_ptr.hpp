// Copyright 2018-2019 by Martin Moene
//
// nonstd::observer_ptr<> is a C++98 onward implementation for std::observer_ptr as of C++17.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#ifndef NONSTD_OBSERVER_PTR_H_INCLUDED
#define NONSTD_OBSERVER_PTR_H_INCLUDED

#define observer_ptr_MAJOR  0
#define observer_ptr_MINOR  2
#define observer_ptr_PATCH  0

#define observer_ptr_VERSION  nsop_STRINGIFY(observer_ptr_MAJOR) "." nsop_STRINGIFY(observer_ptr_MINOR) "." nsop_STRINGIFY(observer_ptr_PATCH)

#define nsop_STRINGIFY(  x )  nsop_STRINGIFY_( x )
#define nsop_STRINGIFY_( x )  #x

// observer_ptr configuration:

#ifndef  nsop_CONFIG_ALLOW_IMPLICIT_CONVERSION_TO_UNDERLYING_TYPE
# define nsop_CONFIG_ALLOW_IMPLICIT_CONVERSION_TO_UNDERLYING_TYPE  0
#endif

#ifndef  nsop_CONFIG_CONFIRMS_COMPILATION_ERRORS
# define nsop_CONFIG_CONFIRMS_COMPILATION_ERRORS  0
#endif

#define nsop_OBSERVER_PTR_DEFAULT  0
#define nsop_OBSERVER_PTR_NONSTD   1
#define nsop_OBSERVER_PTR_STD      2

#if !defined( nsop_CONFIG_SELECT_OBSERVER_PTR )
# define nsop_CONFIG_SELECT_OBSERVER_PTR  ( nsop_HAVE_STD_OBSERVER_PTR ? nsop_OBSERVER_PTR_STD : nsop_OBSERVER_PTR_NONSTD )
#endif

// C++ language version detection (C++20 is speculative):
// Note: VC14.0/1900 (VS2015) lacks too much from C++14.

#ifndef   nsop_CPLUSPLUS
# if defined(_MSVC_LANG ) && !defined(__clang__)
#  define nsop_CPLUSPLUS  (_MSC_VER == 1900 ? 201103L : _MSVC_LANG )
# else
#  define nsop_CPLUSPLUS  __cplusplus
# endif
#endif

#define nsop_CPP98_OR_GREATER  ( nsop_CPLUSPLUS >= 199711L )
#define nsop_CPP11_OR_GREATER  ( nsop_CPLUSPLUS >= 201103L )
#define nsop_CPP11_OR_GREATER_ ( nsop_CPLUSPLUS >= 201103L )
#define nsop_CPP14_OR_GREATER  ( nsop_CPLUSPLUS >= 201402L )
#define nsop_CPP17_OR_GREATER  ( nsop_CPLUSPLUS >= 201703L )
#define nsop_CPP20_OR_GREATER  ( nsop_CPLUSPLUS >= 202000L )

// Use C++17 std::any if available and requested:

#if nsop_CPP17_OR_GREATER && defined(__has_include )
# if __has_include( <experimental/memory> )
#  define nsop_HAVE_STD_OBSERVER_PTR  1
# else
#  define nsop_HAVE_STD_OBSERVER_PTR  0
# endif
#else
# define  nsop_HAVE_STD_OBSERVER_PTR  0
#endif

#define  nsop_USES_STD_OBSERVER_PTR  ( (nsop_CONFIG_SELECT_OBSERVER_PTR == nsop_OBSERVER_PTR_STD) || ((nsop_CONFIG_SELECT_OBSERVER_PTR == nsop_OBSERVER_PTR_DEFAULT) && nsop_HAVE_STD_OBSERVER_PTR) )

//
// Using std::experimental::observer_ptr:
//

#if nsop_USES_STD_OBSERVER_PTR

#include <experimental/memory>

namespace nonstd {

    using std::experimental::observer_ptr;
    using std::experimental::make_observer;
    using std::experimental::swap;

    using std::experimental::operator==;
    using std::experimental::operator!=;
    using std::experimental::operator<;
    using std::experimental::operator<=;
    using std::experimental::operator>;
    using std::experimental::operator>=;
}

#else // nsop_USES_STD_OBSERVER_PTR

#include <cassert>
#include <algorithm>
#include <functional>

// Compiler versions:
//
// MSVC++ 6.0  _MSC_VER == 1200 (Visual Studio 6.0)
// MSVC++ 7.0  _MSC_VER == 1300 (Visual Studio .NET 2002)
// MSVC++ 7.1  _MSC_VER == 1310 (Visual Studio .NET 2003)
// MSVC++ 8.0  _MSC_VER == 1400 (Visual Studio 2005)
// MSVC++ 9.0  _MSC_VER == 1500 (Visual Studio 2008)
// MSVC++ 10.0 _MSC_VER == 1600 (Visual Studio 2010)
// MSVC++ 11.0 _MSC_VER == 1700 (Visual Studio 2012)
// MSVC++ 12.0 _MSC_VER == 1800 (Visual Studio 2013)
// MSVC++ 14.0 _MSC_VER == 1900 (Visual Studio 2015)
// MSVC++ 14.1 _MSC_VER >= 1910 (Visual Studio 2017)

#if defined(_MSC_VER ) && !defined(__clang__)
# define nsop_COMPILER_MSVC_VER      (_MSC_VER )
# define nsop_COMPILER_MSVC_VERSION  (_MSC_VER / 10 - 10 * ( 5 + (_MSC_VER < 1900 ) ) )
#else
# define nsop_COMPILER_MSVC_VER      0
# define nsop_COMPILER_MSVC_VERSION  0
#endif

#define nsop_COMPILER_VERSION( major, minor, patch )  ( 10 * ( 10 * (major) + (minor) ) + (patch) )

#if defined(__clang__)
# define nsop_COMPILER_CLANG_VERSION  nsop_COMPILER_VERSION(__clang_major__, __clang_minor__, __clang_patchlevel__)
#else
# define nsop_COMPILER_CLANG_VERSION  0
#endif

#if defined(__GNUC__) && !defined(__clang__)
# define nsop_COMPILER_GNUC_VERSION  nsop_COMPILER_VERSION(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#else
# define nsop_COMPILER_GNUC_VERSION  0
#endif

// half-open range [lo..hi):
#define nsop_BETWEEN( v, lo, hi ) ( (lo) <= (v) && (v) < (hi) )

// Presence of language and library features:

#ifdef _HAS_CPP0X
# define nsop_HAS_CPP0X  _HAS_CPP0X
#else
# define nsop_HAS_CPP0X  0
#endif

// Unless defined otherwise below, consider VC12 as C++11 for observer_ptr:

#if nsop_COMPILER_MSVC_VER >= 1800
# undef  nsop_CPP11_OR_GREATER
# define nsop_CPP11_OR_GREATER  1
#endif

#define nsop_CPP11_100  (nsop_CPP11_OR_GREATER_ || nsop_COMPILER_MSVC_VER >= 1600)
#define nsop_CPP11_110  (nsop_CPP11_OR_GREATER_ || nsop_COMPILER_MSVC_VER >= 1700)
#define nsop_CPP11_140  (nsop_CPP11_OR_GREATER_ || nsop_COMPILER_MSVC_VER >= 1900)

#define nsop_CPP11_000  (nsop_CPP11_OR_GREATER_)
#define nsop_CPP14_000  (nsop_CPP14_OR_GREATER )
#define nsop_CPP17_000  (nsop_CPP17_OR_GREATER )

// Presence of C++ language features:

#define nsop_HAVE_CONSTEXPR_11          nsop_CPP11_000
#define nsop_HAVE_CONSTEXPR_14          nsop_CPP14_000
#define nsop_HAVE_EXPLICIT_CONVERSION   nsop_CPP11_140
#define nsop_HAVE_NOEXCEPT              nsop_CPP11_140
#define nsop_HAVE_NULLPTR               nsop_CPP11_100

#define nsop_HAVE_TYPEOF  (nsop_CPP11_000 && nsop_COMPILER_GNUC_VERSION)

// Presence of C++ library features:

#define nsop_HAVE_STD_DECAY             nsop_CPP11_110
#define nsop_HAVE_STD_DECLVAL           nsop_CPP11_110

// C++ feature usage:

#if nsop_HAVE_CONSTEXPR_11
# define nsop_constexpr constexpr
#else
# define nsop_constexpr /*nothing*/
#endif

#if nsop_HAVE_CONSTEXPR_14
# define nsop_constexpr14 constexpr
#else
# define nsop_constexpr14 /*nothing*/
#endif

#if nsop_HAVE_EXPLICIT_CONVERSION
# define nsop_explicit explicit
#else
# define nsop_explicit /*nothing*/
#endif

#if nsop_HAVE_NOEXCEPT
# define nsop_noexcept noexcept
#else
# define nsop_noexcept /*nothing*/
#endif

#if nsop_HAVE_NULLPTR
# define nsop_NULLPTR nullptr
#else
# define nsop_NULLPTR NULL
#endif

// common_type:

#if nsop_HAVE_STD_DECAY && nsop_HAVE_STD_DECLVAL
# include <type_traits>  // std::decay
# include <utility>      // std::declval
#endif

#define nsop_HAVE_OWN_COMMON_TYPE_STD    (nsop_HAVE_STD_DECAY && nsop_HAVE_STD_DECLVAL || nsop_HAVE_TYPEOF)
#define nsop_HAVE_OWN_COMMON_TYPE_TYPEOF  nsop_HAVE_TYPEOF

namespace nonstd {

template< class W >
class observer_ptr
{
public:
    typedef W   element_type;
    typedef W * pointer;
    typedef W & reference;

    nsop_constexpr14 observer_ptr() nsop_noexcept
    : ptr( nsop_NULLPTR ) {}

#if nsop_HAVE_NULLPTR
    nsop_constexpr14 observer_ptr( std::nullptr_t ) nsop_noexcept
    : ptr( nullptr ) {}
#endif

    nsop_constexpr14 explicit observer_ptr( pointer p ) nsop_noexcept
    : ptr(p) {}

#if nsop_CPP11_OR_GREATER
    template< class W2, class = typename std::enable_if<std::is_convertible<W2*, W*>::value>::type >
#else
    template< class W2 >
#endif
    nsop_constexpr14 observer_ptr( observer_ptr<W2> other ) nsop_noexcept
    : ptr( other.get() ) {}

    nsop_constexpr14 pointer get() const nsop_noexcept
    {
        return ptr;
    }

    nsop_constexpr14 reference operator*() const
    {
        return assert( ptr != nsop_NULLPTR ), *ptr;
    }

    nsop_constexpr14 pointer operator->() const nsop_noexcept
    {
        return ptr;
    }

#if nsop_HAVE_EXPLICIT_CONVERSION

    nsop_constexpr14 explicit operator bool() const nsop_noexcept
    {
        return ptr != nsop_NULLPTR;
    }

    nsop_constexpr14 explicit operator pointer() const nsop_noexcept
    {
        return ptr;
    }
#elif nsop_CONFIG_ALLOW_IMPLICIT_CONVERSION_TO_UNDERLYING_TYPE

    nsop_constexpr14 operator pointer() const nsop_noexcept
    {
        return ptr;
    }
#else
private:
    typedef void (observer_ptr::*safe_bool)() const;
    void this_type_does_not_support_comparisons() const {}
public:
    
    nsop_constexpr14 operator safe_bool() const nsop_noexcept
    {
        return ptr != nsop_NULLPTR ? &observer_ptr::this_type_does_not_support_comparisons : 0;
    }
#endif

    nsop_constexpr14 pointer release() nsop_noexcept
    {
        pointer p( ptr );
        reset();
        return p;
    }

    nsop_constexpr14 void reset( pointer p = nsop_NULLPTR ) nsop_noexcept
    {
        ptr = p;
    }

    nsop_constexpr14 void swap( observer_ptr & other ) nsop_noexcept
    {
        using std::swap;
        swap(ptr, other.ptr);
    }

private:
    pointer ptr;
};

// specialized algorithms:

template< class W >
void swap( observer_ptr<W> & p1, observer_ptr<W> & p2 ) nsop_noexcept
{
    p1.swap( p2 );
}

template< class W >
observer_ptr<W> make_observer( W * p ) nsop_noexcept
{
    return observer_ptr<W>( p );
}

template< class W1, class W2 >
bool operator==( observer_ptr<W1> p1, observer_ptr<W2> p2 )
{
    return p1.get() == p2.get();
}

template< class W1, class W2 >
bool operator!=( observer_ptr<W1> p1, observer_ptr<W2> p2 )
{
    return !( p1 == p2 );
}

#if nsop_HAVE_NULLPTR

template< class W >
bool operator==( observer_ptr<W> p, std::nullptr_t ) nsop_noexcept
{
    return !p;
}

template< class W >
bool operator==( std::nullptr_t, observer_ptr<W> p ) nsop_noexcept
{
    return !p;
}

template< class W >
bool operator!=( observer_ptr<W> p, std::nullptr_t ) nsop_noexcept
{
    return static_cast<bool>( p );
}

template< class W >
bool operator!=( std::nullptr_t, observer_ptr<W> p ) nsop_noexcept
{
    return static_cast<bool>( p );
}
#endif

namespace detail
{
    template< class T, class U >
#if nsop_HAVE_OWN_COMMON_TYPE_STD
    struct common_type { typedef typename std::decay< decltype(true ? std::declval<T>() : std::declval<U>()) >::type type; };
#elif nsop_HAVE_OWN_COMMON_TYPE_TYPEOF
    struct common_type { typedef __typeof__( true ? T() : U() ) type; };
#else // fall back
    struct common_type { typedef T type; };
#endif
} // namespace detail

template< class W1, class W2 >
bool operator<( observer_ptr<W1> p1, observer_ptr<W2> p2 )
{
    // return std::less<W3>()( p1.get(), p2.get() );
    // where W3 is the composite pointer type (C++14 §5) of W1* and W2*.
    return std::less< typename detail::common_type<W1*,W2*>::type >()( p1.get(), p2.get() );
}

template< class W1, class W2 >
bool operator>( observer_ptr<W1> p1, observer_ptr<W2> p2 )
{
    return p2 < p1;
}

template< class W1, class W2 >
bool operator<=( observer_ptr<W1> p1, observer_ptr<W2> p2 )
{
    return !( p2 < p1 );
}

template< class W1, class W2 >
bool operator>=( observer_ptr<W1> p1, observer_ptr<W2> p2 )
{
    return !( p1 < p2 );
}

} // namespace nonstd

#if nsop_CPP11_OR_GREATER

namespace std
{

template< class T >
struct hash< ::nonstd::observer_ptr<T> >
{
    size_t operator()(::nonstd::observer_ptr<T> p ) const nsop_noexcept
    {
        return hash<T*>()( p.get() );
    }
};

}
#endif

// #undef ...

#endif // nsop_USES_STD_OBSERVER_PTR

#endif // NONSTD_OBSERVER_PTR_H_INCLUDED

// end of file
