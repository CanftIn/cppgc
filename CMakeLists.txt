cmake_minimum_required(VERSION 3.20)
project(
  cppgc
  VERSION 0.0.1
  LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE "Debug")
set(project_version "${${PROJECT_NAME}_VERSION}")

message(STATUS "Project '${PROJECT_NAME}', version: '${project_version}'")

option(CPPGC_OPT_BUILD_UNITTESTS "Build all unittests" ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # for debug of stl structure while using clang compile
  add_compile_options(-fstandalone-debug)
endif()

# CMake helpers:
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

include(CTest)

include_directories(include)

# Create the cppgc C++ library
set(cppgc_SRCS)

set(STATIC_LIB_NAME ${PROJECT_NAME})

file(GLOB_RECURSE LIB_PATH
    ./lib/*.cc
  )
list(APPEND cocktail_SRCS ${LIB_PATH})

add_library(${STATIC_LIB_NAME} STATIC ${cocktail_SRCS})
target_link_libraries(${STATIC_LIB_NAME})

#if (CPPGC_OPT_BUILD_UNITTESTS)
#  add_subdirectory(unittests #[[EXCLUDE_FROM_ALL]])
#endif()