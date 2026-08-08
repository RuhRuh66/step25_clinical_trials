cmake_minimum_required(VERSION 3.20)

project(clinical_trials VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_library(http_client src/HttpClient.cpp)

target_include_directories(http_client PUBLIC include)
target_link_libraries(http_client PUBLIC CURL::libcurl)


add_executable(clinical_trials src/main.cpp)



target_link_libraries(clinical_trials PRIVATE http_client nlohmann_json::nlohmann_json)