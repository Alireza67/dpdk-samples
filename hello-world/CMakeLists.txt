cmake_minimum_required(VERSION 3.10)
project(helloworld CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME}  main.cpp)
include_directories(/usr/local/include/)
link_directories(/usr/local/lib64)
link_directories(/usr/local/lib/x86_64-linux-gnu/)
target_link_libraries(${PROJECT_NAME}  rte_eal)
