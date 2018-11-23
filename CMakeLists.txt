# Copyright 2013-2018 by Martin Moene
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required( VERSION 3.5 )

# observer-ptr project and version, updated by script/update-version.py:

project( observer_ptr LANGUAGES CXX )

set( observer_ptr_version "0.2.0" )

# Toplevel or subproject:

if ( CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR )
    set( observer_ptr_IS_TOPLEVEL_PROJECT TRUE )
else()
    set( observer_ptr_IS_TOPLEVEL_PROJECT FALSE )
endif()

# At default, disable building and performing of tests and building of examples:

option( NSOP_OPT_BUILD_TESTS    "Build and perform observer_ptr tests" ${observer_ptr_IS_TOPLEVEL_PROJECT} )
option( NSOP_OPT_BUILD_EXAMPLES "Build observer_ptr examples" OFF )

enable_testing()

if ( NSOP_OPT_BUILD_TESTS )
    add_subdirectory( test )
endif()

if ( NSOP_OPT_BUILD_EXAMPLES )
    add_subdirectory( example )
endif()

# end of file
