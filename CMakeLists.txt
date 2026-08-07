cmake_minimum_required(VERSION 3.20)

project(Myproject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(clinical_trials src/main.cpp src/HttpClient.cpp)

target_include_directories(clinical_trials PRIVATE include)

target_link_libraries(clinical_trials PRIVATE CURL::libcurl)
target_link_libraries(clinical_trials PRIVATE nlohmann_json::nlohmann_json)