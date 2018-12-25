# Copyright 2013-2018 by Martin Moene
#
# https://github.com/martinmoene/observer-ptr
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required( VERSION 3.5 )

# observer-ptr project and version, updated by script/update-version.py:

project(
    observer_ptr
    VERSION 0.2.0
    DESCRIPTION "A C++17-like observer_ptr for C++98 and later in a single-file header-only library"
#   HOMEPAGE_URL "https://github.com/martinmoene/observer-ptr"
    LANGUAGES CXX )

set( ${PROJECT_NAME}_version "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}" )

# Toplevel or subproject:

if ( CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR )
    set( observer_ptr_IS_TOPLEVEL_PROJECT TRUE )
else()
    set( observer_ptr_IS_TOPLEVEL_PROJECT FALSE )
endif()

# At default, disable building and performing of tests and building of examples:

option( NSOP_OPT_BUILD_TESTS    "Build and perform observer_ptr tests" ${observer_ptr_IS_TOPLEVEL_PROJECT} )
option( NSOP_OPT_BUILD_EXAMPLES "Build observer_ptr examples" OFF )

option( NSOP_OPT_SELECT_STD      "Select std::experimental::observer_ptr" OFF )
option( NSOP_OPT_SELECT_NONSTD   "Select nonstd::observer_ptr" OFF )

enable_testing()

if ( NSOP_OPT_BUILD_TESTS )
    add_subdirectory( test )
endif()

if ( NSOP_OPT_BUILD_EXAMPLES )
    add_subdirectory( example )
endif()

# end of file
