#include <cute/numeric/integral_constant.hpp>
#include <type_traits>

#include <iostream>

int main()
{
    using Eight = cute::C<8>;

    using Nine = cute::C<9>;

    using EightInt = cute::Int<8>;

    static_assert(
        std::is_same_v<Eight, EightInt>
    );

    constexpr bool same_type = std::is_same_v<Eight, Nine>;

    static_assert(
        !same_type
    );

    static_assert(
        std::is_same_v<
            cute::_8,
            cute::Int<8>
        >
    );


    std::cout 
        << "Eight::value = "
        << Eight::value
        << '\n';


    std::cout 
        << std::boolalpha
        << "C<8> and C<9> are the same type: "
        << same_type
        << '\n';

    std::cout 
        << "sizeof(C<8>): "
        << sizeof(Eight)
        << " byte\n";

    Eight eight{};

    std::cout 
        << "Converted Eight object: "
        << static_cast<int>(eight)
        << '\n';

    std::cout
        << "Called Eight object: "
        << eight()
        << '\n';

    std::cout 
        << "Int<8>::value = "
        << EightInt::value
        << '\n';

    std::cout 
        << "_8::value = "
        << cute::_8::value
        << '\n';

    // A namespace/block variable declared:
    // constexpr auto sum
    // has a const-qualified type, so decltype(sum) is const int.
    // An ordinary auto variable is not const-qualified unless you explicitly add const or constexpr.
    constexpr auto sum = 
        cute::_8{} + cute::_16{};
    
    using SumType = decltype(sum);

    std::cout 
        << "_8{} + _16{} = "
        << sum
        << '\n';

    std::cout 
        << "Sum type is int: "
        << std::is_same_v<SumType, const int>
        << '\n';

    std::cout 
        << "sum type is const C<24>: "
        << std::is_same_v<SumType, const cute::C<24>>
        << '\n';

    static_assert(
        std::is_same_v<
            SumType,
            const cute::C<24>>
    );

    constexpr auto difference = 
        cute::_16{} - cute::_8{};
    
    constexpr auto product = 
        cute::_8{} * cute::_16{};

    static_assert(
        std::is_same_v<
            decltype(difference),
            const cute::C<8>
        >
    );

    static_assert(
        std::is_same_v<
            decltype(product),
            const cute::C<128>
        >
    );

    std::cout
        << "_16{} - _8{} = "
        << difference 
        << '\n';

    std::cout
        << "_8{} * _16{} = "
        << product 
        << '\n';
            

    return 0;
}



// std::is_same_v   evaluated/resolved at compile time, regardless of where it appears.
// std::is_same_v   is a variable termplate, not a funcition. 


// The expression inside static_assert must be eligible for compile-time evaluation under 
// C++ constant-expression rules, and the compiler then evaluates it during compilation.

// constexpr int n = 8;
// static_assert(n == 8); // Valid
// n here is a constant-expression variable. 


// int n = 8;
// static_assert(n == 8); // Error
// Even though a human can see that n was initialized to 8, n is an ordinary mutable variable. 
// It is not permitted in a constant expression.
// 
// int n = 8
//     mutable runtime variable
// 
// const int n = 8
//     immutable variable; may sometimes be usable as a constant expression
// 
// constexpr int n = 8
//     immutable variable explicitly guaranteed to be usable in constant expressions
// 
// The real requirement is:
// The entire condition passed to static_assert must be a constant expression.
// 
// A constexpr variable guarantees that requirement for its initialization. A const int 
// can also satisfy it when initialized with compile-time information.

// constexpr, static_assert()
// They do enforce compile-time evaluation; they are not merely reminders.
// The compiler performs two checks:
// Is this expression legally usable as a constant expression?
// If so, evaluate it during compilation.
// If the first check fails, compilation fails. The compiler does not fall back to runtime evaluation.

// The nuance is with a constexpr function:
// constexpr int square(int x)
// {
    // return x * x;
// }
// Declaring the function constexpr means it is eligible 
// for compile-time evaluation. It does not mean every call must occur during compilation:
// constexpr int a = square(4); // Must be compile-time
// static_assert(square(4) == 16); // Must be compile-time
// 
// int x;
// std::cin >> x;
// int b = square(x); // Runs at runtime
// constexpr variable → initializer must be compile-time evaluated
// static_assert      → condition must be compile-time evaluated
// constexpr function → function may run at compile time or runtime,
                    //  depending on the calling context