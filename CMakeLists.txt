cmake_minimum_required(VERSION 3.23)
project(Containers)

set(CMAKE_CXX_STANDARD 14)

include_directories(User)

add_executable(Containers main.cpp User/User.cpp)
