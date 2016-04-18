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

#include <__ocl_atomic_impl.h>

#define ATOMIC_VAR_INIT(value) {value}

namespace cl
{

/// \brief Generic atomic class
///
/// Please note that arithmetic operations are only provided for integral atomic types
template <typename T>
struct atomic : public conditional_t<
    __details::__is_atomic_integer_type<T>::value,
    __details::__atomic_arithmetic_capable<T, typename __details::__atomic_types<T>::spirv_type>,
    __details::__atomic_base<T, typename __details::__atomic_types<T>::spirv_type >>
{
    static_assert(__details::__is_valid_atomic_type<T>::value, "The generic atomic<T> class template is only available if T is "
        "int, uint, long, ulong, float, double, intptr_t, uintptr_t, size_t, ptrdiff_t or pointer to any type. Note that "
        "64-bit types may require 'cl_khr_int64_base_atomics' and 'cl_khr_int64_extended_atomics' extensions and atomic<double> in addition requires 'cl_khr_fp64'.");
};

/// \brief Typedefs for atomic types
///
using atomic_int = atomic<int>;
using atomic_uint = atomic<unsigned int>;
#if defined(cl_khr_int64_base_atomics) && defined(cl_khr_int64_extended_atomics)
using atomic_long = atomic<long>;
using atomic_ulong = atomic<unsigned long>;
#endif
using atomic_float = atomic<float>;
#if defined(cl_khr_fp64) && defined(cl_khr_int64_base_atomics) && defined(cl_khr_int64_extended_atomics)
using atomic_double = atomic<double>;
#endif
#if (defined(cl_khr_int64_base_atomics) && defined(cl_khr_int64_extended_atomics) && __INTPTR_WIDTH__ == 64) || __INTPTR_WIDTH__ == 32
using atomic_intptr_t = atomic<intptr_t>;
using atomic_uintptr_t = atomic<uintptr_t>;
#endif
#if (defined(cl_khr_int64_base_atomics) && defined(cl_khr_int64_extended_atomics) && __SIZE_WIDTH__ == 64) || __SIZE_WIDTH__ == 32
using atomic_size_t = atomic<size_t>;
#endif
#if (defined(cl_khr_int64_base_atomics) && defined(cl_khr_int64_extended_atomics) && __PTRDIFF_WIDTH__ == 64) || __PTRDIFF_WIDTH__ == 32
using atomic_ptrdiff_t = atomic<ptrdiff_t>;
#endif


template <class T> auto __ALWAYS_INLINE atomic_store(atomic<T>* object, T value) __NOEXCEPT -> decltype(object->store(value)) { return object->store(value); }
template <class T> auto __ALWAYS_INLINE atomic_store(volatile atomic<T>* object, T value) __NOEXCEPT -> decltype(object->store(value)) { return object->store(value); }
template <class T> auto __ALWAYS_INLINE atomic_store_explicit(atomic<T>* object, T value, _MEM_ORD) __NOEXCEPT -> decltype(object->store(value, order, scope)) { return object->store(value, order, scope); }
template <class T> auto __ALWAYS_INLINE atomic_store_explicit(volatile atomic<T>* object, T value, _MEM_ORD) __NOEXCEPT -> decltype(object->store(value, order, scope)) { return object->store(value, order, scope); }

template <class T> auto __ALWAYS_INLINE atomic_load(atomic<T>* object) __NOEXCEPT -> decltype(object->load()) { return object->load(); }
template <class T> auto __ALWAYS_INLINE atomic_load(volatile atomic<T>* object) __NOEXCEPT -> decltype(object->load()) { return object->load(); }
template <class T> auto __ALWAYS_INLINE atomic_load_explicit(atomic<T>* object, _MEM_ORD) __NOEXCEPT -> decltype(object->load(order, scope)) { return object->load(order, scope); }
template <class T> auto __ALWAYS_INLINE atomic_load_explicit(volatile atomic<T>* object, _MEM_ORD) __NOEXCEPT -> decltype(object->load(order, scope)) { return object->load(order, scope); }

template <class T> auto __ALWAYS_INLINE atomic_exchange(atomic<T>* object, T value) __NOEXCEPT -> decltype(object->exchange(value)) { return object->exchange(value); }
template <class T> auto __ALWAYS_INLINE atomic_exchange(volatile atomic<T>* object, T value) __NOEXCEPT -> decltype(object->exchange(value)) { return object->exchange(value); }
template <class T> auto __ALWAYS_INLINE atomic_exchange_explicit(atomic<T>* object, T value, _MEM_ORD) __NOEXCEPT -> decltype(object->exchange(value, order, scope)) { return object->exchange(value, order, scope); }
template <class T> auto __ALWAYS_INLINE atomic_exchange_explicit(volatile atomic<T>* object, T value, _MEM_ORD) __NOEXCEPT -> decltype(object->exchange(value, order, scope)) { return object->exchange(value, order, scope); }

template <class T> auto __ALWAYS_INLINE atomic_compare_exchange_strong(atomic<T>* object, T* expected, T desired) __NOEXCEPT -> decltype(object->compare_exchange_strong(expected, desired)) { return object->compare_exchange_strong(expected, desired); }
template <class T> auto __ALWAYS_INLINE atomic_compare_exchange_strong(volatile atomic<T>* object, T* expected, T desired) __NOEXCEPT -> decltype(object->compare_exchange_strong(expected, desired)) { return object->compare_exchange_strong(expected, desired); }
template <class T> auto __ALWAYS_INLINE atomic_compare_exchange_strong_explicit(atomic<T>* object, T* expected, T desired, _MEM_ORD2) __NOEXCEPT -> decltype(object->compare_exchange_strong(expected, desired, success, failure, scope)) { return object->compare_exchange_strong(expected, desired, success, failure, scope); }
template <class T> auto __ALWAYS_INLINE atomic_compare_exchange_strong_explicit(volatile atomic<T>* object, T* expected, T desired, _MEM_ORD2) __NOEXCEPT -> decltype(object->compare_exchange_strong(expected, desired, success, failure, scope)) { return object->compare_exchange_strong(expected, desired, success, failure, scope); }
template <class T> auto __ALWAYS_INLINE atomic_compare_exchange_weak(atomic<T>* object, T* expected, T desired) __NOEXCEPT -> decltype(object->compare_exchange_weak(expected, desired)) { return object->compare_exchange_weak(expected, desired); }
template <class T> auto __ALWAYS_INLINE atomic_compare_exchange_weak(volatile atomic<T>* object, T* expected, T desired) __NOEXCEPT -> decltype(object->compare_exchange_weak(expected, desired)) { return object->compare_exchange_weak(expected, desired); }
template <class T> auto __ALWAYS_INLINE atomic_compare_exchange_weak_explicit(atomic<T>* object, T* expected, T desired, _MEM_ORD2) __NOEXCEPT -> decltype(object->compare_exchange_weak(expected, desired, success, failure, scope)) { return object->compare_exchange_weak(expected, desired, success, failure, scope); }
template <class T> auto __ALWAYS_INLINE atomic_compare_exchange_weak_explicit(volatile atomic<T>* object, T* expected, T desired, _MEM_ORD2) __NOEXCEPT -> decltype(object->compare_exchange_weak(expected, desired, success, failure, scope)) { return object->compare_exchange_weak(expected, desired, success, failure, scope); }

template <class T> auto __ALWAYS_INLINE atomic_fetch_add(atomic<T>* object, T value) __NOEXCEPT -> decltype(object->fetch_add(value)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_add(value); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_add(volatile atomic<T>* object, T value) __NOEXCEPT -> decltype(object->fetch_add(value)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_add(value); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_add_explicit(atomic<T>* object, T value, _MEM_ORD) __NOEXCEPT -> decltype(object->fetch_add(value, order, scope)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_add(value, order, scope); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_add_explicit(volatile atomic<T>* object, T value, _MEM_ORD) __NOEXCEPT -> decltype(object->fetch_add(value, order, scope)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_add(value, order, scope); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_and(atomic<T>* object, T value) __NOEXCEPT -> decltype(object->fetch_and(value)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_and(value); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_and(volatile atomic<T>* object, T value) __NOEXCEPT -> decltype(object->fetch_and(value)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_and(value); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_and_explicit(atomic<T>* object, T value, _MEM_ORD) __NOEXCEPT -> decltype(object->fetch_and(value, order, scope)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_and(value, order, scope); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_and_explicit(volatile atomic<T>* object, T value, _MEM_ORD) __NOEXCEPT -> decltype(object->fetch_and(value, order, scope)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_and(value, order, scope); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_or(atomic<T>* object, T value) __NOEXCEPT -> decltype(object->fetch_or(value)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_or(value); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_or(volatile atomic<T>* object, T value) __NOEXCEPT -> decltype(object->fetch_or(value)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_or(value); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_or_explicit(atomic<T>* object, T value, _MEM_ORD) __NOEXCEPT -> decltype(object->fetch_or(value, order, scope)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_or(value, order, scope); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_or_explicit(volatile atomic<T>* object, T value, _MEM_ORD) __NOEXCEPT -> decltype(object->fetch_or(value, order, scope)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_or(value, order, scope); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_sub(atomic<T>* object, T value) __NOEXCEPT -> decltype(object->fetch_sub(value)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_sub(value); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_sub(volatile atomic<T>* object, T value) __NOEXCEPT -> decltype(object->fetch_sub(value)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_sub(value); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_sub_explicit(atomic<T>* object, T value, _MEM_ORD) __NOEXCEPT -> decltype(object->fetch_sub(value, order, scope)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_sub(value, order, scope); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_sub_explicit(volatile atomic<T>* object, T value, _MEM_ORD) __NOEXCEPT -> decltype(object->fetch_sub(value, order, scope)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_sub(value, order, scope); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_xor(atomic<T>* object, T value) __NOEXCEPT -> decltype(object->fetch_xor(value)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_xor(value); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_xor(volatile atomic<T>* object, T value) __NOEXCEPT -> decltype(object->fetch_xor(value)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_xor(value); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_xor_explicit(atomic<T>* object, T value, _MEM_ORD) __NOEXCEPT -> decltype(object->fetch_xor(value, order, scope)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_xor(value, order, scope); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_xor_explicit(volatile atomic<T>* object, T value, _MEM_ORD) __NOEXCEPT -> decltype(object->fetch_xor(value, order, scope)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_xor(value, order, scope); }

template <class T> auto __ALWAYS_INLINE atomic_fetch_add(atomic<T*>* object, ptrdiff_t value) __NOEXCEPT -> decltype(object->fetch_add(value)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_add(value); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_add(volatile atomic<T*>* object, ptrdiff_t value) __NOEXCEPT -> decltype(object->fetch_add(value)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_add(value); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_add_explicit(atomic<T*>* object, ptrdiff_t value, _MEM_ORD) __NOEXCEPT -> decltype(object->fetch_add(value, order, scope)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_add(value, order, scope); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_add_explicit(volatile atomic<T*>* object, ptrdiff_t value, _MEM_ORD) __NOEXCEPT -> decltype(object->fetch_add(value, order, scope)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_add(value, order, scope); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_and(atomic<T*>* object, ptrdiff_t value) __NOEXCEPT -> decltype(object->fetch_and(value)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_and(value); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_and(volatile atomic<T*>* object, ptrdiff_t value) __NOEXCEPT -> decltype(object->fetch_and(value)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_and(value); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_and_explicit(atomic<T*>* object, ptrdiff_t value, _MEM_ORD) __NOEXCEPT -> decltype(object->fetch_and(value, order, scope)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_and(value, order, scope); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_and_explicit(volatile atomic<T*>* object, ptrdiff_t value, _MEM_ORD) __NOEXCEPT -> decltype(object->fetch_and(value, order, scope)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_and(value, order, scope); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_or(atomic<T*>* object, ptrdiff_t value) __NOEXCEPT -> decltype(object->fetch_or(value)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_or(value); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_or(volatile atomic<T*>* object, ptrdiff_t value) __NOEXCEPT -> decltype(object->fetch_or(value)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_or(value); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_or_explicit(atomic<T*>* object, ptrdiff_t value, _MEM_ORD) __NOEXCEPT -> decltype(object->fetch_or(value, order, scope)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_or(value, order, scope); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_or_explicit(volatile atomic<T*>* object, ptrdiff_t value, _MEM_ORD) __NOEXCEPT -> decltype(object->fetch_or(value, order, scope)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_or(value, order, scope); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_sub(atomic<T*>* object, ptrdiff_t value) __NOEXCEPT -> decltype(object->fetch_sub(value)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_sub(value); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_sub(volatile atomic<T*>* object, ptrdiff_t value) __NOEXCEPT -> decltype(object->fetch_sub(value)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_sub(value); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_sub_explicit(atomic<T*>* object, ptrdiff_t value, _MEM_ORD) __NOEXCEPT -> decltype(object->fetch_sub(value, order, scope)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_sub(value, order, scope); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_sub_explicit(volatile atomic<T*>* object, ptrdiff_t value, _MEM_ORD) __NOEXCEPT -> decltype(object->fetch_sub(value, order, scope)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_sub(value, order, scope); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_xor(atomic<T*>* object, ptrdiff_t value) __NOEXCEPT -> decltype(object->fetch_xor(value)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_xor(value); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_xor(volatile atomic<T*>* object, ptrdiff_t value) __NOEXCEPT -> decltype(object->fetch_xor(value)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_xor(value); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_xor_explicit(atomic<T*>* object, ptrdiff_t value, _MEM_ORD) __NOEXCEPT -> decltype(object->fetch_xor(value, order, scope)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_xor(value, order, scope); }
template <class T> auto __ALWAYS_INLINE atomic_fetch_xor_explicit(volatile atomic<T*>* object, ptrdiff_t value, _MEM_ORD) __NOEXCEPT -> decltype(object->fetch_xor(value, order, scope)) { static_assert(__details::__is_atomic_integer_type<T>::value, "Arithemetic operations are supported only for integer type atomics"); return object->fetch_xor(value, order, scope); }

void __ALWAYS_INLINE atomic_fence(mem_fence flags, memory_order order, memory_scope scope) { __spirv::OpMemoryBarrier(scope, static_cast<memory_order>(static_cast<underlying_type_t<mem_fence>>(flags) | order)); }

#undef _MEM_ORD
#undef _MEM_ORD2

}
