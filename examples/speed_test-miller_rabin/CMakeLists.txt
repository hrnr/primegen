cmake_minimum_required (VERSION 2.6)

# set default build (current Debug), user can override
# must be before project
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
endif()

project (primegen-speed_test-miller_rabin)

# c++11 support required
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# when using bignum library same warning doesn't make sense
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-shift-count-overflow")

# include our library
include_directories("../../src")

add_executable(speed_test-miller_rabin main.cpp)


# we are using gmp library for big nums

# gmp is supposed to be is systems's default include paths and default library
# paths (ie. linkable with following line). Hope this will be the most
# convenient since pkg-config nor cmake config files are present on most
# systems (no need for this simple lib).
# Modify following line if needed
target_link_libraries(speed_test-miller_rabin "-lgmp -lgmpxx")