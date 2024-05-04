cmake_minimum_required(VERSION 3.20)
project(basicfwd CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


find_package(PkgConfig REQUIRED)

if (PKG_CONFIG_FOUND)
pkg_check_modules(DPDK "libdpdk")
if (DPDK_FOUND)
message(STATUS "found dpdk via pkg-config")
endif()
endif()

pkg_check_modules(DPDK "libdpdk")
if (DPDK_FOUND)
  add_definitions(${DPDK_CFLAGS})
  set(MYDPDK_LIBRARIES -Wl,--whole-archive ${DPDK_LIBRARIES} -lpthread -lnuma -ldl -Wl,--no-whole-archive)
  include_directories(${DPDK_INCLUDE_DIR})
  link_libraries(${MYDPDK_LIBRARIES})
  add_definitions(-DHAVE_DPDK)
endif(DPDK_FOUND)

add_executable(${PROJECT_NAME} main.cpp)