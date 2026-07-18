set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.20)

project(HZL_GEMM LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)

set(CMAKE_CUDA_ARCHITECTURES 86)

add_library(cute INTERFACE)

target_include_directories(
    cute
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)       

add_executable(
    step01_device_info
    examples/01_device_info.cu
)

add_executable(
    step02_static_integer
    examples/02_static_integer.cpp
)

add_executable(
    step02_static_integer_device
    examples/02_static_integer_device.cu
)

target_link_libraries(
    step02_static_integer_device
    PRIVATE
    cute
)

target_link_libraries(
    step02_static_integer
    PRIVATE
    cute
)

