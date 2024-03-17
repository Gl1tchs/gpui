cmake_minimum_required(VERSION 3.25)

project(gpui)

option(BUILD_TESTBED "Should we build testbed application." ON)
option(BUILD_SHARED "Should we build shared library." OFF)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL
                                        "RelWithDebInfo")
  set(GPUI_BUILD_TYPE "Debug")
  add_compile_definitions(GPUI_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(GPUI_BUILD_TYPE "Release")
  add_compile_definitions(GPUI_RELEASE)
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
  set(GPUI_BUILD_TYPE "Dist")
  add_compile_definitions(GPUI_DIST)
endif()

# Try to use internal SDL3 if exists
find_package(SDL3 QUIET)
if(SDL3_FOUND)
  message(STATUS "Using SDL3 from system")
endif()

# Use internal SDL if not found.
if(NOT SDL3_FOUND)
  add_subdirectory("vendor/SDL")
  message(STATUS "Using SDL3 via add_subdirectory")
  set(SDL3_FOUND TRUE)
endif()

# always use internal glad
add_subdirectory("vendor/glad")

file(GLOB_RECURSE SOURCES "include/*.h" "src/*.cpp")

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(NOT BUILD_SHARED)
  add_library(gpui STATIC ${SOURCES})
else()
  add_library(gpui SHARED ${SOURCES})
endif()

target_include_directories(
  gpui
  PUBLIC "include"
  PRIVATE "vendor/glad/include" ${SDL_INCLUDE_DIRS})

target_link_libraries(gpui PRIVATE glad SDL3::SDL3)

target_precompile_headers(gpui PUBLIC "include/gpui/pch.h")

if(BUILD_TESTBED)
  add_subdirectory(testbed)
endif()
