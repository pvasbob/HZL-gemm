cmake_minimum_required(VERSION 3.20)

project(HZL_GEMM LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)

set(CMAKE_CUDA_ARCHITECTURES 86)

add_executable(
    step01_device_info
    examples/01_device_info.cu
)