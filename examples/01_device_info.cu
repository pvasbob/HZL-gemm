#include  <iostream>
#include <cuda_runtime.h>
#include <cstdio>

__global__ void hello_from_gpu()
{

    int compiled_arch = 0;

#if defined(__CUDA_ARCH__)
    compiled_arch = __CUDA_ARCH__;
#endif

    if (blockIdx.x == 0 && threadIdx.x == 0)
    {
        printf(
            "GPU kernel compiled for SM%d\n",
            compiled_arch / 10
        );
    }
}

int main() 
{
    std::cout << "HZL GEMM: SM86 project \n";

    int device_count = 0;

    cudaError_t status = cudaGetDeviceCount(&device_count);

    if (status != cudaSuccess)
    {
        std::cerr   << "cudaGetDeviceCount failed: "
                    << cudaGetErrorString(status)
                    << '\n';

        return 1;
    }

    std::cout   << "CUDA device count: "
                << device_count
                << '\n';

    if (device_count  == 0)
    {
        std::cerr   << "No CUDA device is available. \n";
        return 1;
    }

    cudaDeviceProp properties{};

    status = cudaGetDeviceProperties(
        &properties,
        0
    );

    if (status != cudaSuccess)
    {
        std::cerr
            << "cuda GetDeviceProperties failed: "
            << cudaGetErrorString(status)
            << '\n';

        return 1;
    }

    std::cout
        << "Device name: " 
        << properties.name
        << '\n';
    
    std::cout
        << "Compute capability: SM"
        << properties.major
        << properties.minor
        << '\n';
    
    std::cout 
        << "Warp size: "
        << properties.warpSize
        << "\n";

    hello_from_gpu<<<1, 1>>>();

    status = cudaGetLastError();
    
    if (status != cudaSuccess) 
    {
        std::cerr
            << "Kernel launch failed: " 
            << cudaGetErrorString(status)
            << '\n';
        
        return 1;
    }

    status = cudaDeviceSynchronize();

    if(status != cudaSuccess)
    {
        std::cerr
            << "Kernel execution failed: "
            << cudaGetErrorString(status)
            << '\n';

        return 1;
    }



    return 0;
}