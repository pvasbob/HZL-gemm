/***************************************************************************************************
 * Copyright (c) 2023 - 2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 **************************************************************************************************/

#pragma once

#include <cute/config.hpp>


namespace cute {

    template <auto v>
    struct C{
        using type = C<v>;

        static constexpr auto value = v;

        using value_type = decltype(v);


        // operator value_type()  → use object as its value type
        // operator()()           → explicitly request the encoded value
        CUTE_HOST_DEVICE constexpr
        operator value_type() const noexcept
        {
            return value;
        }

        CUTE_HOST_DEVICE constexpr
        value_type operator()() const noexcept
        {
            return value;
        }
    };
    // alias template describes a family of aliases
    template<int v>
    using Int = C<v>;

    using _1  = Int<1>;
    using _8  = Int<8>;
    using _16 = Int<16>;

    // template <auto t, auto u>
    // constexpr C<(t + u)> // this is the operator return type.
    // operator+(C<t>, C<u>)
    // {
    //     // returns an empty, initialized object of the declared return type C<(t + u)>
    //     // avoids repeating the return type
    //     return {};
    //     // below is also valid:
    //     // return C<(t + u)>{};
    // }
    #define CUTE_BINARY_OP(OP)                  \
        template<auto t, auto u>                \
        CUTE_HOST_DEVICE constexpr                               \
        C<(t OP u)> operator OP(C<t>, C<u>)     \
        {                                       \
            return {};                          \
        }


    CUTE_BINARY_OP(+);
    CUTE_BINARY_OP(-);
    CUTE_BINARY_OP(*);

    #undef CUTE_BINARY_OP


}




