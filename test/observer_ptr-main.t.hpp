// Copyright 2013-2018 by Martin Moene
//
// nonstd::observer_ptr<> is a C++98 onward implementation for std::observer_ptr as of C++17.
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#ifndef TEST_NONSTD_OBSERVER_PTR_H_INCLUDED
#define TEST_NONSTD_OBSERVER_PTR_H_INCLUDED

#include "observer_ptr.hpp"

// Compiler warning suppression for usage of lest:

#ifdef __clang__
# pragma clang diagnostic ignored "-Wstring-conversion"
# pragma clang diagnostic ignored "-Wunused-parameter"
# pragma clang diagnostic ignored "-Wunused-template"
# pragma clang diagnostic ignored "-Wunused-function"
# pragma clang diagnostic ignored "-Wunused-member-function"
#elif defined __GNUC__
# pragma GCC   diagnostic ignored "-Wunused-parameter"
# pragma GCC   diagnostic ignored "-Wunused-function"
#endif

#include <iostream>

#if ! nsop_BETWEEN( nsop_COMPILER_MSVC_VERSION, 60, 70 )
namespace std {
#else
namespace lest {
#endif

template< typename W >
inline std::ostream & operator<<( std::ostream & os, nonstd::observer_ptr<W> const & p )
{
    using ::lest::to_string;
    return os << "[observer_ptr:" << ( !!p.get() ? to_string(*p):"(empty)") << "]";
}

} // namespace std / namespace lest

#include "lest_cpp03.hpp"

#define CASE( name ) lest_CASE( specification(), name )

// Attribute externally visible for -fwhole-program:

#if defined(__GNUC__) && !defined(__clang__)
# define nsop_ATTRIBUTE_EXT_VIS  __attribute__((externally_visible))
#else
# define nsop_ATTRIBUTE_EXT_VIS
#endif

extern lest::tests & specification() nsop_ATTRIBUTE_EXT_VIS;

#endif // TEST_NONSTD_OBSERVER_PTR_H_INCLUDED
