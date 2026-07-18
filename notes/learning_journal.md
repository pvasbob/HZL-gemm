defining two ordinary empty structs:
struct A {};
struct B {};
Their bodies are identical, but A and B are still different types.

====================

template <int N>
struct C {
};

C<8> and C<9>
│      │
└──────┴── different template arguments
             ↓
        different types

====================

But identical representation does not mean identical type.
The distinction is:
Type identity:         different
Memory representation: possibly identical
Behavior:              possibly identical

====================

static_assert is evaluated at compile time because the C++ language 
specifically defines it as a compile-time assertion.
Be careful: the word static does not always mean “compile time.” For example:
static int counter = 0;
counter still exists and can change at runtime. static there describes storage 
duration, not compile-time

constexpr means an operation is eligible for compile-time evaluation. Not has to be 
compile-time evaluation. The surrounding context determines whether compile-time 
evaluation is required.

The compiler consumes the useful type-level information during compilation, 
so the runtime does not need to inspect the object to discover the number 8.


C++ therefore defines special syntax for conversion functions:
operator target_type()
The target type also acts as the function’s result type.
=================================================================



In VS Code, run:
Ctrl+Shift+P
C/C++: Reset IntelliSense Database
Then:
Ctrl+Shift+P
Developer: Reload Window

When CMake configuration changes, run:
cmake -S . -B build -G Ninja

=================================================================
