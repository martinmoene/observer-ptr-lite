# Copyright 2013-2018 by Martin Moene
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required( VERSION 3.5 )

# observer-ptr version, updated by script/update-version.py:

set( observer_ptr_version "0.2.0" )

# At default, disable building and performing of tests and building of examples:

option( NSOP_OPT_BUILD_TESTS    "Build and perform observer_ptr tests" OFF )
option( NSOP_OPT_BUILD_EXAMPLES "Build observer_ptr examples" OFF )

project( observer_ptr LANGUAGES CXX )

enable_testing()

if ( NSOP_OPT_BUILD_TESTS )
    add_subdirectory( test )
endif()

if ( NSOP_OPT_BUILD_EXAMPLES )
    add_subdirectory( example )
endif()

# end of file
