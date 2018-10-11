# Copyright 2013-2018 by Martin Moene
#
# Distributed under the Boost Software License, Version 1.0. 
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required( VERSION 3.5 )

# observer-ptr version, updated by script/update-version.py:

set( observer_ptr_version "0.2.0" )

project( observer_ptr LANGUAGES CXX )

enable_testing()

add_subdirectory( test )
#add_subdirectory( example )

# end of file
