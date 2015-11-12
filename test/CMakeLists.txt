# Copyright 2015 by Martin Moene
#
# This code is licensed under the MIT License (MIT).

cmake_minimum_required( VERSION 2.8 )

project( test )

include_directories  ( "${PROJECT_SOURCE_DIR}/../include" )

set( SOURCES observer_ptr.t.cpp )

add_executable ( observer_ptr.t ${SOURCES} )

set( SINGLE_TEST_PROGRAM TRUE )

# GNU: have -std=c++14 and lower?
if( ${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" )
    execute_process(
        COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)

    # command line option -std=c++14 since gcc 4.9.2:
    if( GCC_VERSION VERSION_GREATER 4.9.2 OR GCC_VERSION VERSION_EQUAL 4.9.2 )
        set( SINGLE_TEST_PROGRAM FALSE )
    endif()
endif()

if( ${CMAKE_CXX_COMPILER_ID} MATCHES "MSVC" )
    add_compile_options( -W3 -EHsc )

elseif( ${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR
        ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang" )
    add_executable( observer_ptr-cpp98.t ${SOURCES} )
    add_executable( observer_ptr-cpp03.t ${SOURCES} )
    add_executable( observer_ptr-cpp11.t ${SOURCES} )
    add_executable( observer_ptr-cpp14.t ${SOURCES} )

    add_compile_options( -Wall -Wno-missing-braces )

    target_compile_options( observer_ptr-cpp98.t  PUBLIC -std=c++98 )
    target_compile_options( observer_ptr-cpp03.t  PUBLIC -std=c++03 )
    target_compile_options( observer_ptr-cpp11.t  PUBLIC -std=c++11 )
    target_compile_options( observer_ptr-cpp14.t  PUBLIC -std=c++14 )

elseif( ${CMAKE_CXX_COMPILER_ID} MATCHES "Intel" )
# as is
else()
# as is
endif()

# configure unit tests via CTest:

enable_testing()

 if( ${SINGLE_TEST_PROGRAM} )
add_test( NAME test          COMMAND observer_ptr.t --pass )
 else()
add_test( NAME test-cpp98    COMMAND observer_ptr-cpp98.t )
add_test( NAME test-cpp03    COMMAND observer_ptr-cpp03.t )
add_test( NAME test-cpp11    COMMAND observer_ptr-cpp11.t )
add_test( NAME test-cpp14    COMMAND observer_ptr-cpp14.t --pass )
 endif()
add_test( NAME list_version  COMMAND observer_ptr.t --version )
add_test( NAME list_tags     COMMAND observer_ptr.t --list-tags )
add_test( NAME list_tests    COMMAND observer_ptr.t --list-tests )

# end of file
