cmake_minimum_required(VERSION 3.0)
project(Algorithms)

set(CMAKE_CXX_COMPILER "/home/linuxbrew/.linuxbrew/bin/clang++")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BINARY_DIR bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/tools/cmake")
set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")

find_package(Catch REQUIRED)

include(tools/cmake/TestSolution.cmake)

function(add_category category)
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${category})
    add_subdirectory(${category})
  endif()
endfunction()

add_category(heap)
add_category(binary_search)
add_category(meet-in-the-middle)
