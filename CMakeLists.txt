# Copyright 2015 by Martin Moene
#
# This code is licensed under the MIT License (MIT).

cmake_minimum_required( VERSION 2.8 )

# observer-ptr version, updated by script/update-version.py:

set( observer_ptr_version "0.2.0" )

project( observer_ptr )

enable_testing()

add_subdirectory( test )
#add_subdirectory( example )

# end of file
