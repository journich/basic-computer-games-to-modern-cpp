cmake_minimum_required(VERSION 3.6)
project(AceyDucey)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_executable(AceyDucey acey_ducey.cpp)
target_link_libraries(AceyDucey)
