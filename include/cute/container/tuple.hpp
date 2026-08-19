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

#include <cstddef>
#include <type_traits>

namespace cute {

    namespace detail {
        template <
            std::size_t N,
            class T,
            bool IsEmpty = std::is_empty_v<T>
        >
        struct EBO;

        template <std::size_t N, class T>
        struct EBO<N, T, true>
        {
            CUTE_HOST_DEVICE constexpr
            EBO()
            {
            }

            CUTE_HOST_DEVICE constexpr
            EBO(T const&)
            {
            }
        };

        template <std::size_t N, class T>
        struct EBO<N, T, false>
        {
            CUTE_HOST_DEVICE constexpr
            EBO() : t_{}
            {
            }

            template <class U>
            CUTE_HOST_DEVICE constexpr
            EBO(U const& u) : t_{u}
            {
            }

            T t_;
        };


        // non-const tuple → get<I>() returns T&
        // const tuple     → get<I>() returns T const&


        // const object/reference → ordinary members are read-only
        //                → return const reference
        // non-const object/reference → members are modifiable
        //                → may return mutable reference

        template <std::size_t N, class T>
        CUTE_HOST_DEVICE constexpr T
        getv(EBO<N, T, true> const&)
        {
            return T{};
        }

        template <std::size_t N, class T>
        CUTE_HOST_DEVICE constexpr T const&
        getv(EBO<N, T, false> const& x)
        {
            return x.t_;
        }

        // it returns a non-const reference to a member of 
        // the parameter, not to the complete parameter itself.
        template <std::size_t N, class T>
        CUTE_HOST_DEVICE constexpr T&
        getv(EBO<N, T, false>& x)
        {
            return x.t_;
        }

    } // namespace detail

    template <class T0, class T1>
    struct tuple :
        detail::EBO<0, T0>,
        detail::EBO<1, T1>
    {
        CUTE_HOST_DEVICE constexpr
        tuple()
        {
        }

        template <class U0, class U1>
        CUTE_HOST_DEVICE constexpr
        tuple(U0 const& u0, U1 const& u1) :
            detail::EBO<0, T0>(u0),
            detail::EBO<1, T1>(u1)
        {
        }
    };

    template <std::size_t I, class T0, class T1>
    // For T = int:
    // decltype(auto) // preserves int&
    // auto           // would produce int
    CUTE_HOST_DEVICE constexpr decltype(auto)
    get(tuple<T0, T1> const& t) noexcept
    {
        static_assert(I < 2, "Index out of range");
        return detail::getv<I>(t);
    }

    template <std::size_t I, class T0, class T1>
    CUTE_HOST_DEVICE constexpr decltype(auto)
    get(tuple<T0, T1>& t) noexcept
    {
        static_assert(I < 2, "Index out of range");
        return detail::getv<I>(t);
    }

} // namespace cute


// Encode information in types when it is known during compilation; 
// store information in object members when it is only known at runtime.
//

// The important qualification is “when it is useful and known at compile 
// time.” Encoding every possible value in types would create excessive 
// template instantiations and compilation cost. Matrix problem sizes often 
// remain dynamic, while tile shapes, layouts, copy operations, and MMA 
// sinstruction shapes are strong candidates for compile-time representation.


// The complete selection is:
// non-const dimensions
//         ↓
// select get(tuple& t)
//         ↓
// t is non-const
//         ↓
// select getv(EBO& x)
//         ↓
// x.t_ is non-const
//         ↓
// return T&
// For a const tuple, the path is instead:
// const dimensions
//         ↓
// select get(tuple const& t)
//         ↓
// t is const
//         ↓
// select getv(EBO const& x)
//         ↓
// x.t_ is const
//         ↓
// return T const&
