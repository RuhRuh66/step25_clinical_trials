cmake_minimum_required(VERSION 3.20)

project(Myproject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(search_trial src/main.cpp)