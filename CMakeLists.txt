cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME csvtoker)
project(${PROJECT_NAME})

set(CMAKE_SUPPRESS_REGENERATION "1")

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "-lstdc++")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG=1 -O2")
add_executable(${PROJECT_NAME}-demo demo.cpp)

if (GTESTDIR)
  add_executable(${PROJECT_NAME}-tests tests.cpp)
  include_directories("${GTESTDIR}/include")
  #link_directories("${GTESTDIR}/lib")
  target_link_libraries (${PROJECT_NAME}-tests "${GTESTDIR}/lib/libgtest.a" )
endif()
