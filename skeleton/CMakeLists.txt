cmake_minimum_required(VERSION 3.20)
project(basicfwd)

# Find DPDK
find_package(PkgConfig REQUIRED)
pkg_check_modules(DPDK REQUIRED libdpdk)

# Check for DPDK installation
if(NOT DPDK_FOUND)
    message(FATAL_ERROR "DPDK not found")
endif()

# Add the executable
add_executable(${PROJECT_NAME} main.cpp)

# Set compile flags and link libraries
target_compile_options(${PROJECT_NAME} PRIVATE ${DPDK_CFLAGS_OTHER} -DALLOW_EXPERIMENTAL_API)
target_link_libraries(${PROJECT_NAME} PRIVATE ${DPDK_LIBRARIES})

# Conditional compilation for static and shared builds
if(BUILD_SHARED_LIBS)
    set_target_properties(${PROJECT_NAME} PROPERTIES ENABLE_EXPORTS ON)
else()
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${DPDK_LDFLAGS_STATIC}")
endif()

add_custom_target(${PROJECT_NAME}_clean
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/cmake/clean.cmake
    COMMENT "Cleaning build directory..."
)

