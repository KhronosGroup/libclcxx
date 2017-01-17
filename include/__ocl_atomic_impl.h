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

#include <__ocl_atomic_traits.h>
#include <__ocl_atomic_enum.h>
#include <__ocl_spirv_atomic_opcodes.h>
#include <__ocl_type_traits_type_properties.h>

namespace cl
{

namespace __details
{

/// \brief Recurring pattern in nearly all atomic operation signatures
///
#define _MEM_ORD memory_order order = memory_order_seq_cst, memory_scope scope = memory_scope_device

/// \brief Recurring pattern in many atomic operation signatures
///
#define _MEM_ORD2 memory_order success, memory_order failure, memory_scope scope = memory_scope_device

/// \brief Class containing base atomic operations
///
/// These consist of all operations that are independent of whether the atomic type is a pointer or not
template <typename T, typename _SPIRV_T = T>
struct __atomic_base
{
    static_assert(sizeof(T) == sizeof(_SPIRV_T), "SPIRV atomic type should have same size as T");

    T _value;

    /// \brief Compare exchange strong overloads
    ///
    __ALWAYS_INLINE bool compare_exchange_strong(T & expected, T value, _MEM_ORD) __NOEXCEPT { _SPIRV_T org = __spirv::OpAtomicCompareExchange((_SPIRV_T*)&_value, scope, order, order, asSPIRV(value), asSPIRV(expected)); bool r = org == asSPIRV(expected); if(!r) expected = (T)org; return r; }
    __ALWAYS_INLINE bool compare_exchange_strong(T & expected, T value, _MEM_ORD) volatile __NOEXCEPT { _SPIRV_T org = __spirv::OpAtomicCompareExchange((_SPIRV_T*)&_value, scope, order, order, asSPIRV(value), asSPIRV(expected)); bool r = org == asSPIRV(expected); if(!r) expected = (T)org; return r; }
    __ALWAYS_INLINE bool compare_exchange_strong(T & expected, T value, _MEM_ORD2) __NOEXCEPT { _SPIRV_T org = __spirv::OpAtomicCompareExchange((_SPIRV_T*)&_value, scope, success, failure, asSPIRV(value), asSPIRV(expected)); bool r = org == asSPIRV(expected); if(!r) expected = (T)org; return r; }
    __ALWAYS_INLINE bool compare_exchange_strong(T & expected, T value, _MEM_ORD2) volatile __NOEXCEPT { _SPIRV_T org = __spirv::OpAtomicCompareExchange((_SPIRV_T*)&_value, scope, success, failure, asSPIRV(value), asSPIRV(expected)); bool r = org == asSPIRV(expected); if(!r) expected = (T)org; return r; }

    /// \brief Compare exchange weak overloads
    ///
    __ALWAYS_INLINE bool compare_exchange_weak(T & expected, T value, _MEM_ORD) __NOEXCEPT { _SPIRV_T org = __spirv::OpAtomicCompareExchangeWeak((_SPIRV_T*)&_value, scope, order, order, asSPIRV(value), asSPIRV(expected)); bool r = org == asSPIRV(expected); if(!r) expected = (T)org; return r; }
    __ALWAYS_INLINE bool compare_exchange_weak(T & expected, T value, _MEM_ORD) volatile __NOEXCEPT { _SPIRV_T org = __spirv::OpAtomicCompareExchangeWeak((_SPIRV_T*)&_value, scope, order, order, asSPIRV(value), asSPIRV(expected)); bool r = org == asSPIRV(expected); if(!r) expected = (T)org; return r; }
    __ALWAYS_INLINE bool compare_exchange_weak(T & expected, T value, _MEM_ORD2) __NOEXCEPT { _SPIRV_T org = __spirv::OpAtomicCompareExchangeWeak((_SPIRV_T*)&_value, scope, success, failure, asSPIRV(value), asSPIRV(expected)); bool r = org == asSPIRV(expected); if(!r) expected = (T)org; return r; }
    __ALWAYS_INLINE bool compare_exchange_weak(T & expected, T value, _MEM_ORD2) volatile __NOEXCEPT { _SPIRV_T org = __spirv::OpAtomicCompareExchangeWeak((_SPIRV_T*)&_value, scope, success, failure, asSPIRV(value), asSPIRV(expected)); bool r = org == asSPIRV(expected); if(!r) expected = (T)org; return r; }

    /// \brief Exchange overloads
    ///
    __ALWAYS_INLINE T exchange(T value, _MEM_ORD) __NOEXCEPT { return asT(__spirv::OpAtomicExchange((_SPIRV_T*)&_value, scope, order, asSPIRV(value))); }
    __ALWAYS_INLINE T exchange(T value, _MEM_ORD) volatile __NOEXCEPT { return asT(__spirv::OpAtomicExchange((_SPIRV_T*)&_value, scope, order, asSPIRV(value))); }

    /// \brief Load overloads
    ///
    __ALWAYS_INLINE T load(_MEM_ORD) const __NOEXCEPT { return asT(__spirv::OpAtomicLoad((_SPIRV_T*)&_value, scope, order)); }
    __ALWAYS_INLINE T load(_MEM_ORD) const volatile __NOEXCEPT { return asT(__spirv::OpAtomicLoad((_SPIRV_T*)&_value, scope, order)); }

    /// \brief Store overloads
    ///
    __ALWAYS_INLINE void store(T value, _MEM_ORD) __NOEXCEPT { __spirv::OpAtomicStore((_SPIRV_T*)&_value, scope, order, asSPIRV(value)); }
    __ALWAYS_INLINE void store(T value, _MEM_ORD) volatile __NOEXCEPT { __spirv::OpAtomicStore((_SPIRV_T*)&_value, scope, order, asSPIRV(value)); }

    __atomic_base() __NOEXCEPT = default;
    constexpr __atomic_base(T v) __NOEXCEPT: _value(v) {}
    __atomic_base(const __atomic_base&) = delete;
    __atomic_base &operator=(const __atomic_base&) = delete;
    __atomic_base &operator=(const __atomic_base&) volatile = delete;

    __ALWAYS_INLINE operator T( ) const __NOEXCEPT { return load( ); }
    __ALWAYS_INLINE operator T( ) const volatile __NOEXCEPT { return load( ); }

    __ALWAYS_INLINE T operator=(T value) __NOEXCEPT { store(value); return value; }
    __ALWAYS_INLINE T operator=(T value) volatile __NOEXCEPT { store(value); return value; }

protected:
    __ALWAYS_INLINE T const& asT(_SPIRV_T const& S) const volatile __NOEXCEPT { return reinterpret_cast<T const&>(S); }

    __ALWAYS_INLINE _SPIRV_T const& asSPIRV(T const& t) const volatile __NOEXCEPT { return reinterpret_cast<_SPIRV_T const&>(t); }
};

#define ATOMIC_ARITHMETIC_OPERATION(symbol, name, spirv_opcode) \
    __ALWAYS_INLINE auto fetch_##name(result_type value, _MEM_ORD) __NOEXCEPT { return this->asT(spirv_opcode((_SPIRV_T*)&this->_value, scope, order, value)); } \
    __ALWAYS_INLINE auto fetch_##name(result_type value, _MEM_ORD) volatile __NOEXCEPT { return this->asT(spirv_opcode((_SPIRV_T*)&this->_value, scope, order, value)); } \
    __ALWAYS_INLINE auto operator symbol##=(result_type value) __NOEXCEPT { return fetch_##name(value) symbol value; } \
    __ALWAYS_INLINE auto operator symbol##=(result_type value) volatile __NOEXCEPT { return fetch_##name(value) symbol value; }

/// \brief Class containing atomic arithmetic operations
///
template <typename T, typename _SPIRV_T = T>
struct __atomic_arithmetic_capable : public __atomic_base<T, _SPIRV_T>
{
private:
    static_assert(__details::__is_atomic_integer_type<T>::value, "Arithmetic operations are supported only for integer-type atomics.");
    typedef typename __details::__atomic_types<T>::arithmetic_result_type result_type;

public:
    using __atomic_base<T, _SPIRV_T>::__atomic_base;
    using __atomic_base<T, _SPIRV_T>::operator=;

    ATOMIC_ARITHMETIC_OPERATION(+, add, __spirv::OpAtomicIAdd);
    ATOMIC_ARITHMETIC_OPERATION(-, sub, __spirv::OpAtomicISub);
    ATOMIC_ARITHMETIC_OPERATION(&, and, __spirv::OpAtomicAnd);
    ATOMIC_ARITHMETIC_OPERATION(|,  or, __spirv::OpAtomicOr);
    ATOMIC_ARITHMETIC_OPERATION(^, xor, __spirv::OpAtomicXor);

    template<class U = T>
    __ALWAYS_INLINE enable_if_t<is_unsigned<U>::value, U> fetch_min(result_type value, _MEM_ORD) __NOEXCEPT { return this->asT(__spirv::OpAtomicUMin((_SPIRV_T*)&this->_value, scope, order, value)); }
    template<class U = T>
    __ALWAYS_INLINE enable_if_t<is_unsigned<U>::value, U> fetch_min(result_type value, _MEM_ORD) volatile __NOEXCEPT { return this->asT(__spirv::OpAtomicUMin((_SPIRV_T*)&this->_value, scope, order, value)); }
    template<class U = T>
    __ALWAYS_INLINE enable_if_t<!is_unsigned<U>::value, U> fetch_min(result_type value, _MEM_ORD) __NOEXCEPT { return this->asT(__spirv::OpAtomicSMin((_SPIRV_T*)&this->_value, scope, order, value)); }
    template<class U = T>
    __ALWAYS_INLINE enable_if_t<!is_unsigned<U>::value, U> fetch_min(result_type value, _MEM_ORD) volatile __NOEXCEPT { return this->asT(__spirv::OpAtomicSMin((_SPIRV_T*)&this->_value, scope, order, value)); }

    template<class U = T>
    __ALWAYS_INLINE enable_if_t<is_unsigned<U>::value, U> fetch_max(result_type value, _MEM_ORD) __NOEXCEPT { return this->asT(__spirv::OpAtomicUMax((_SPIRV_T*)&this->_value, scope, order, value)); }
    template<class U = T>
    __ALWAYS_INLINE enable_if_t<is_unsigned<U>::value, U> fetch_max(result_type value, _MEM_ORD) volatile __NOEXCEPT { return this->asT(__spirv::OpAtomicUMax((_SPIRV_T*)&this->_value, scope, order, value)); }
    template<class U = T>
    __ALWAYS_INLINE enable_if_t<!is_unsigned<U>::value, U> fetch_max(result_type value, _MEM_ORD) __NOEXCEPT { return this->asT(__spirv::OpAtomicSMax((_SPIRV_T*)&this->_value, scope, order, value)); }
    template<class U = T>
    __ALWAYS_INLINE enable_if_t<!is_unsigned<U>::value, U> fetch_max(result_type value, _MEM_ORD) volatile __NOEXCEPT { return this->asT(__spirv::OpAtomicSMax((_SPIRV_T*)&this->_value, scope, order, value)); }

    /// \brief operator++ overloads
    ///
    __ALWAYS_INLINE T operator++(int) __NOEXCEPT { return fetch_add(1); }
    __ALWAYS_INLINE T operator++(int) volatile __NOEXCEPT { return fetch_add(1); }

    /// \brief operator-- overloads
    ///
    __ALWAYS_INLINE T operator--(int) __NOEXCEPT { return fetch_sub(1); }
    __ALWAYS_INLINE T operator--(int) volatile __NOEXCEPT { return fetch_sub(1); }

    /// \brief operator++ overloads
    ///
    __ALWAYS_INLINE T operator++( ) __NOEXCEPT { return fetch_add(1) + 1; }
    __ALWAYS_INLINE T operator++( ) volatile __NOEXCEPT { return fetch_add(1) + 1; }

    /// \brief operator-- overloads
    ///
    __ALWAYS_INLINE T operator--( ) __NOEXCEPT { return fetch_sub(1) - 1; }
    __ALWAYS_INLINE T operator--( ) volatile __NOEXCEPT { return fetch_sub(1) - 1; }
};

#undef ATOMIC_ARITHMETIC_OPERATION

}

}
