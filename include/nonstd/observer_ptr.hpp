// Copyright 2013-2018 by Martin Moene
//
// nonstd::observer_ptr<> is a C++98 onward implementation for std::observer_ptr as of C++17.
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#ifndef NONSTD_OBSERVER_PTR_H_INCLUDED
#define NONSTD_OBSERVER_PTR_H_INCLUDED

#include <cassert>
#include <algorithm>
#include <functional>

#define observer_ptr_MAJOR  0
#define observer_ptr_MINOR  2
#define observer_ptr_PATCH  0

#define observer_ptr_VERSION  nsop_STRINGIFY(observer_ptr_MAJOR) "." nsop_STRINGIFY(observer_ptr_MINOR) "." nsop_STRINGIFY(observer_ptr_PATCH)

#define nsop_STRINGIFY(  x )  nsop_STRINGIFY_( x )
#define nsop_STRINGIFY_( x )  #x

// Configuration:

#ifndef  nsop_FEATURE_ALLOW_IMPLICIT_CONVERSION
# define nsop_FEATURE_ALLOW_IMPLICIT_CONVERSION  0
#endif

#ifndef  nsop_CONFIG_CONFIRMS_COMPILATION_ERRORS
# define nsop_CONFIG_CONFIRMS_COMPILATION_ERRORS  0
#endif

// Compiler detection:

#define nsop_CPP11_OR_GREATER  ( __cplusplus >= 201103L )
#define nsop_CPP14_OR_GREATER  ( __cplusplus >= 201402L )

// half-open range [lo..hi):
#define nsop_BETWEEN( v, lo, hi ) ( (lo) <= (v) && (v) < (hi) )

#if defined(_MSC_VER)
# define nsop_COMPILER_MSVC_VERSION   (_MSC_VER / 100 - 5 - (_MSC_VER < 1900))
#else
# define nsop_COMPILER_MSVC_VERSION   0
# define nsop_COMPILER_NON_MSVC       1
#endif

// Presence of C++ language features:

#if nsop_CPP11_OR_GREATER
# define nsop_HAVE_CONSTEXPR_11  1
#endif

#if nsop_CPP14_OR_GREATER
# define nsop_HAVE_CONSTEXPR_14  1
#endif

#if nsop_CPP11_OR_GREATER || nsop_COMPILER_MSVC_VERSION >= 14
# define nsop_HAVE_EXPLICIT_CONVERSION  1
#endif

#if nsop_CPP11_OR_GREATER || nsop_COMPILER_MSVC_VERSION >= 14
# define nsop_HAVE_NOEXCEPT  1
#endif

#if nsop_CPP11_OR_GREATER || nsop_COMPILER_MSVC_VERSION >= 10
# define nsop_HAVE_NULLPTR  1
#endif

#if defined( __GNUC__ )
# define nsop_HAVE_TYPEOF  1
#endif

// Presence of C++ library features:

// For the rest, consider VC12, VC14 as C++11 for observer_ptr<>:

#if nsop_COMPILER_MSVC_VERSION >= 12
# undef  nsop_CPP11_OR_GREATER
# define nsop_CPP11_OR_GREATER  1
#endif

#if nsop_CPP11_OR_GREATER || nsop_COMPILER_MSVC_VERSION >= 11
# define nsop_HAVE_STD_DECAY    1
# define nsop_HAVE_STD_DECLVAL  1
#endif

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
# define nsop_HAVE_OWN_COMMON_TYPE      1
# define nsop_HAVE_OWN_COMMON_TYPE_STD  1
#elif nsop_HAVE_TYPEOF
# define nsop_HAVE_OWN_COMMON_TYPE         1
# define nsop_HAVE_OWN_COMMON_TYPE_TYPEOF  1
#endif

namespace nonstd
{

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

    template< class W2 >
    nsop_constexpr14 observer_ptr(observer_ptr<W2> other ) nsop_noexcept
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
#elif nsop_FEATURE_ALLOW_IMPLICIT_CONVERSION

    nsop_constexpr14 operator pointer() const nsop_noexcept
    {
        return ptr;
    }
#else
    typedef void (observer_ptr::*safe_bool)() const;
    void this_type_does_not_support_comparisons() const {}

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
    return (bool)p;
}

template< class W >
bool operator!=( std::nullptr_t, observer_ptr<W> p ) nsop_noexcept
{
    return (bool)p;
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
    size_t operator()(::nonstd::observer_ptr<T> p ) { return hash<T*>()( p.get() ); }
};

}
#endif

// #undef ...

#endif // NONSTD_OBSERVER_PTR_H_INCLUDED

// end of file
