//
// Copyright (c) 2015-2016 The Khronos Group Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and/or associated documentation files (the
// "Materials"), to deal in the Materials without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Materials, and to
// permit persons to whom the Materials are furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Materials.
//
// THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
//

#pragma once

#include <__ocl_swizzle_engine.h>

namespace cl
{

template <class Vec, size_t... Swizzle>
using swizzle_t = typename __details::__make_swizzle_type<Vec, Swizzle...>::type;

template <size_t... Swizzle, class Vec>
__ALWAYS_INLINE auto swizzle(Vec& v)
{
    return swizzle_t<Vec, Swizzle...>{ __details::__get_underlying_vec(v) };
}

template <channel... Swizzle, class Vec>
__ALWAYS_INLINE auto swizzle(Vec& v)
{
    return swizzle<static_cast<size_t>(Swizzle)...>(v);
}

namespace __details
{

template <class T, size_t Size>
struct __vec_impl
{
    static_assert(is_vector_type<make_vector_t<T, Size>>::value, "cl::vec T should be any scalar built-in type, except void, and Size should be 2, 3, 4, 8 or 16");

    using element_type = T;
    using vector_type = make_vector_t<T, Size>;
    static constexpr size_t size = Size;

    __vec_impl() = default;
    __vec_impl(const __vec_impl&) = default;
    __vec_impl(__vec_impl&&) = default;

    __vec_impl(const vector_type& r) __NOEXCEPT : myvec(r) {}

    __vec_impl(vector_type&& r) __NOEXCEPT : myvec(move(r)) {}

    template <class... Params>
    __vec_impl(Params... params) __NOEXCEPT : myvec(params...){}

    __ALWAYS_INLINE auto& __get()       { return myvec; }
    __ALWAYS_INLINE auto& __get() const { return myvec; }

protected:
    make_vector_t<T, Size> myvec;
};

} //end namespace details


template <class T, size_t Size>
struct vec : public __details::__impl_swizzle_t<vec<T, Size>, Size>,
             public __details::__vec_impl<T, Size>
{
    using __details::__vec_impl<T, Size>::myvec;
    using __details::__vec_impl<T, Size>::__vec_impl;

    using element_type = typename __details::__vec_impl<T, Size>::element_type;
    using vector_type = typename __details::__vec_impl<T, Size>::vector_type;
    using __details::__vec_impl<T, Size>::size;

    vec() = default;
    vec(vec const&) = default;
    vec(vec&&) = default;

    __ALWAYS_INLINE vec& operator =(const vec&) = default;
    __ALWAYS_INLINE vec& operator =(vec&&) = default;

    __ALWAYS_INLINE vec& operator =(const vector_type& r) __NOEXCEPT { myvec = r; return *this; }
    __ALWAYS_INLINE vec& operator =(vector_type&& r) __NOEXCEPT { myvec = move(r); return *this; }

    __ALWAYS_INLINE operator vector_type() const __NOEXCEPT { return myvec; }
    __ALWAYS_INLINE operator vector_type&() __NOEXCEPT { return myvec; }
    __ALWAYS_INLINE operator const vector_type&() const __NOEXCEPT { return myvec; }

    __ALWAYS_INLINE vec& operator++() __NOEXCEPT { ++myvec; return *this; }
    __ALWAYS_INLINE vec& operator++(int)__NOEXCEPT { myvec++; return *this; }
    __ALWAYS_INLINE vec& operator--() __NOEXCEPT { --myvec; return *this; }
    __ALWAYS_INLINE vec& operator--(int) __NOEXCEPT{ myvec--; return *this; }
    __ALWAYS_INLINE vec& operator+=(const vec &r) __NOEXCEPT { myvec += r; return *this; }
    __ALWAYS_INLINE vec& operator+=(const element_type &r) __NOEXCEPT { myvec += vector_type{ r }; return *this; }
    __ALWAYS_INLINE vec& operator-=(const vec &r) __NOEXCEPT { myvec -= r; return *this; }
    __ALWAYS_INLINE vec& operator-=(const element_type &r) __NOEXCEPT { myvec -= vector_type{ r }; return *this; }
    __ALWAYS_INLINE vec& operator*=(const vec &r) __NOEXCEPT { myvec *= r; return *this; }
    __ALWAYS_INLINE vec& operator*=(const element_type &r) __NOEXCEPT { myvec *= vector_type{ r }; return *this; }
    __ALWAYS_INLINE vec& operator/=(const vec &r) __NOEXCEPT { myvec /= r; return *this; }
    __ALWAYS_INLINE vec& operator/=(const element_type &r) __NOEXCEPT { myvec /= vector_type{ r }; return *this; }
    __ALWAYS_INLINE vec& operator%=(const vec &r) __NOEXCEPT { myvec %= r; return *this; }
    __ALWAYS_INLINE vec& operator%=(const element_type &r) __NOEXCEPT { myvec %= vector_type{ r }; return *this; }
};

#define _VEC_GLOBAL_OP(op) template <class T, size_t Size> __ALWAYS_INLINE make_vector_t<bool, Size> operator op(const vec<T, Size> &lhs, const vec<T, Size> &rhs) __NOEXCEPT { return lhs.myvec op rhs.myvec; }

_VEC_GLOBAL_OP(==)
_VEC_GLOBAL_OP(!=)
_VEC_GLOBAL_OP(<)
_VEC_GLOBAL_OP(>)
_VEC_GLOBAL_OP(<=)
_VEC_GLOBAL_OP(>=)

#undef _VEC_GLOBAL_OP
#define _VEC_GLOBAL_OP(op) \
    template <class T, size_t Size> vec<T, Size> operator op(const vec<T, Size> &lhs, const vec<T, Size> &rhs) __NOEXCEPT { return vec<T, Size>{ lhs.myvec op rhs.myvec }; } \
    template <class T, size_t Size> vec<T, Size> operator op(const vec<T, Size> &lhs, const T &rhs) __NOEXCEPT { return vec<T, Size>{ lhs.myvec op typename vec<T, Size>::vector_type{ rhs } }; } \
    template <class T, size_t Size> vec<T, Size> operator op(const T &lhs, const vec<T, Size> &rhs) __NOEXCEPT { return vec<T, Size>{ typename vec<T, Size>::vector_type { lhs } op rhs.myvec }; }

_VEC_GLOBAL_OP(+)
_VEC_GLOBAL_OP(-)
_VEC_GLOBAL_OP(*)
_VEC_GLOBAL_OP(/)

#undef _VEC_GLOBAL_OP


} //end namespace cl