// Copyright 2015, 2016 by Martin Moene
//
// nonstd::observer_ptr<> is a C++98 onward implementation for std::observer_ptr as of C++17.
//
// This code is licensed under the MIT License (MIT).
//

#pragma once

#ifndef TEST_NONSTD_OBSERVER_PTR_H_INCLUDED
#define TEST_NONSTD_OBSERVER_PTR_H_INCLUDED

#include "nonstd/observer_ptr.hpp"
#include "lest_cpp03.hpp"

using namespace nonstd;

#define CASE( name ) lest_CASE( specification(), name )

extern lest::tests & specification();

#if ! nop_BETWEEN( nop_COMPILER_MSVC_VERSION, 6, 7 )
namespace std {
#else
namespace lest {
#endif

template< typename W >
inline std::ostream & operator<<( std::ostream & os, observer_ptr<W> const & p )
{
    using ::lest::to_string;
    return os << "[observer_ptr:" << ( !!p.get() ? to_string(*p):"(empty)") << "]";
}

#if ! nop_BETWEEN( nop_COMPILER_MSVC_VERSION, 6, 7 )
} // namespace std
#else
} // namespace lest
#endif

#endif // TEST_NONSTD_OBSERVER_PTR_H_INCLUDED
