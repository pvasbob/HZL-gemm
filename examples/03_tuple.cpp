#include <cute/container/tuple.hpp>
#include <cute/numeric/integral_constant.hpp>

#include <iostream>

struct EmptyPair : 
    cute::detail::EBO<0, cute::_8>, 
    cute::detail::EBO<1, cute::_16>
{
};

int main() 
{
    using Dimensions = 
        cute::tuple<cute::_8, cute::_16>;


    Dimensions dimensions{};

    std::cout 
        << "Tuple value: ("
        << cute::get<0>(dimensions)
        << ", "
        << cute::get<1>(dimensions)
        << ")\n";

    std::cout 
        << "sizeof(_8): "
        << sizeof(cute::_8)
        << " byte\n";

    std::cout 
        << "sizeof(_16): "
        << sizeof(cute::_16)
        << " byte\n";


    std::cout 
        << "Tuple size: "
        << sizeof(Dimensions)
        << " byte\n";

    std::cout 
        << "EBO pair size: "
        << sizeof(EmptyPair)
        << " byte\n";

    EmptyPair empty_pair{};

    std::cout
        << "EBO values: ("
        << cute::detail::getv<0>(empty_pair)
        << ", "
        << cute::detail::getv<1>(empty_pair)
        << ")\n";

    using RuntimeDimensions =
        cute::tuple<int, int>;

    RuntimeDimensions runtime_dimensions{128, 256};

    std::cout
        << "Runtime tuple values: ("
        << cute::get<0>(runtime_dimensions)
        << ", "
        << cute::get<1>(runtime_dimensions)
        << ")\n";

    cute::get<0>(runtime_dimensions) = 512;
    cute::get<1>(runtime_dimensions) = 1024;

    std::cout
        << "Updated runtime tuple values: ("
        << cute::get<0>(runtime_dimensions)
        << ", "
        << cute::get<1>(runtime_dimensions)
        << ")\n";

    std::cout
        << "Runtime tuple size: "
        << sizeof(RuntimeDimensions)
        << " bytes\n";

    return 0;
}
