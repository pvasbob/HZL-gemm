#include <cute/numeric/integral_constant.hpp>
#include <cuda_runtime.h>
#include <cstdio>

__global__ void static_integer_kernel()
{
    constexpr auto product =
        cute::_8{} * cute::_16{};

    printf(
        "GPU: _8{} * _16{} = %d\n",
        static_cast<int>(product)
    );
}

int main()
{
    static_integer_kernel<<<1, 1>>>();

    cudaError_t status =
        cudaDeviceSynchronize();

    return status == cudaSuccess? 0: 1;
}