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

    /// \brief Compare exchange strong overloads
    ///
    bool __ALWAYS_INLINE compare_exchange_strong(T & expected, T value, _MEM_ORD) __NOEXCEPT { return __spirv::OpAtomicCompareExchange((_SPIRV_T*)&_value, scope, order, asSPIRV(value), asSPIRV(expected)) == asSPIRV(expected); }
    bool __ALWAYS_INLINE compare_exchange_strong(T & expected, T value, _MEM_ORD) volatile __NOEXCEPT { return __spirv::OpAtomicCompareExchange((_SPIRV_T*)&_value, scope, order, asSPIRV(value), asSPIRV(expected)) == asSPIRV(expected); }
    bool __ALWAYS_INLINE compare_exchange_strong(T & expected, T value, _MEM_ORD2) __NOEXCEPT { return __spirv::OpAtomicCompareExchange((_SPIRV_T*)&_value, scope, failure, asSPIRV(value), asSPIRV(expected)) == asSPIRV(expected); } //SPIRV doesn't support CompareExchange with two Semantics (success/failuer), bug?
    bool __ALWAYS_INLINE compare_exchange_strong(T & expected, T value, _MEM_ORD2) volatile __NOEXCEPT { return __spirv::OpAtomicCompareExchange((_SPIRV_T*)&_value, scope, failure, asSPIRV(value), asSPIRV(expected)) == asSPIRV(expected); } //as above

    /// \brief Compare exchange strong overloads
    ///
    bool __ALWAYS_INLINE compare_exchange_weak(T & expected, T value, _MEM_ORD) __NOEXCEPT { return __spirv::OpAtomicCompareExchangeWeak((_SPIRV_T*)&_value, scope, order, asSPIRV(value), asSPIRV(expected)) == asSPIRV(expected); }
    bool __ALWAYS_INLINE compare_exchange_weak(T & expected, T value, _MEM_ORD) volatile __NOEXCEPT { return __spirv::OpAtomicCompareExchangeWeak((_SPIRV_T*)&_value, scope, order, asSPIRV(value), asSPIRV(expected)) == asSPIRV(expected); }
    bool __ALWAYS_INLINE compare_exchange_weak(T & expected, T value, _MEM_ORD2) __NOEXCEPT { return __spirv::OpAtomicCompareExchangeWeak((_SPIRV_T*)&_value, scope, failure, asSPIRV(value), asSPIRV(expected)) == asSPIRV(expected); } //as above
    bool __ALWAYS_INLINE compare_exchange_weak(T & expected, T value, _MEM_ORD2) volatile __NOEXCEPT { return __spirv::OpAtomicCompareExchangeWeak((_SPIRV_T*)&_value, scope, failure, asSPIRV(value), asSPIRV(expected)) == asSPIRV(expected); } //as above

    /// \brief Exchange overloads
    ///
    T __ALWAYS_INLINE exchange(T value, _MEM_ORD) __NOEXCEPT { return asT(__spirv::OpAtomicExchange((_SPIRV_T*)&_value, scope, order, asSPIRV(value))); }
    T __ALWAYS_INLINE exchange(T value, _MEM_ORD) volatile __NOEXCEPT { return asT(__spirv::OpAtomicExchange((_SPIRV_T*)&_value, scope, order, asSPIRV(value))); }

    /// \brief Load overloads
    ///
    T __ALWAYS_INLINE load(_MEM_ORD) const __NOEXCEPT { return asT(__spirv::OpAtomicLoad((_SPIRV_T*)&_value, scope, order)); }
    T __ALWAYS_INLINE load(_MEM_ORD) const volatile __NOEXCEPT { return asT(__spirv::OpAtomicLoad((_SPIRV_T*)&_value, scope, order)); }

    /// \brief Store overloads
    ///
    void __ALWAYS_INLINE store(T value, _MEM_ORD) __NOEXCEPT { __spirv::OpAtomicStore((_SPIRV_T*)&_value, scope, order, asSPIRV(value)); }
    void __ALWAYS_INLINE store(T value, _MEM_ORD) volatile __NOEXCEPT { __spirv::OpAtomicStore((_SPIRV_T*)&_value, scope, order, asSPIRV(value)); }

    __ALWAYS_INLINE operator T( ) const __NOEXCEPT { return load( ); }
    __ALWAYS_INLINE operator T( ) const volatile __NOEXCEPT { return load( ); }

    T __ALWAYS_INLINE operator=(T value) __NOEXCEPT { store(value); return value; }
    T __ALWAYS_INLINE operator=(T value) volatile __NOEXCEPT { store(value); return value; }

protected:
    T _value;

    T const& __ALWAYS_INLINE asT(_SPIRV_T const& S) const volatile __NOEXCEPT { return reinterpret_cast<T const&>(S); }

    _SPIRV_T __ALWAYS_INLINE const& asSPIRV(T const& t) const volatile __NOEXCEPT { return reinterpret_cast<_SPIRV_T const&>(t); }
};

#define ATOMIC_ARITHMETIC_OPERATION(symbol, name, spirv_opcode) \
    T __ALWAYS_INLINE fetch_##name(result_type value, _MEM_ORD) __NOEXCEPT { return this->asT(spirv_opcode((_SPIRV_T*)&this->_value, scope, order, value)); } \
    T __ALWAYS_INLINE fetch_##name(result_type value, _MEM_ORD) volatile __NOEXCEPT { return this->asT(spirv_opcode((_SPIRV_T*)&this->_value, scope, order, value)); } \
    T __ALWAYS_INLINE operator symbol##=(result_type value) __NOEXCEPT { return fetch_##name(value) symbol value; } \
    T __ALWAYS_INLINE operator symbol##=(result_type value) volatile __NOEXCEPT { return fetch_##name(value) symbol value; }

/// \brief Class containing atomic arithmetic operations
///
template <typename T, typename _SPIRV_T = T>
struct __atomic_arithmetic_capable : public __atomic_base<T, _SPIRV_T>
{
private:
    static_assert(__details::__is_atomic_integer_type<T>::value, "Arithmetic operations are supported only for integer-type atomics.");
    typedef typename __details::__atomic_types<T>::arithmetic_result_type result_type;

public:
    ATOMIC_ARITHMETIC_OPERATION(+, add, __spirv::OpAtomicIAdd);
    ATOMIC_ARITHMETIC_OPERATION(-, sub, __spirv::OpAtomicISub);
    ATOMIC_ARITHMETIC_OPERATION(&, and, __spirv::OpAtomicAnd);
    ATOMIC_ARITHMETIC_OPERATION(| , or, __spirv::OpAtomicOr);
    ATOMIC_ARITHMETIC_OPERATION(^, xor, __spirv::OpAtomicXor);

    /// \brief operator++ overloads
    ///
    T __ALWAYS_INLINE operator++(int) __NOEXCEPT { return fetch_add(1); }
    T __ALWAYS_INLINE operator++(int) volatile __NOEXCEPT { return fetch_add(1); }

    /// \brief operator-- overloads
    ///
    T __ALWAYS_INLINE operator--(int) __NOEXCEPT { return fetch_sub(1); }
    T __ALWAYS_INLINE operator--(int) volatile __NOEXCEPT { return fetch_sub(1); }

    /// \brief operator++ overloads
    ///
    T __ALWAYS_INLINE operator++( ) __NOEXCEPT { return fetch_add(1) + 1; }
    T __ALWAYS_INLINE operator++( ) volatile __NOEXCEPT { return fetch_add(1) + 1; }

    /// \brief operator-- overloads
    ///
    T __ALWAYS_INLINE operator--( ) __NOEXCEPT { return fetch_sub(1) - 1; }
    T __ALWAYS_INLINE operator--( ) volatile __NOEXCEPT { return fetch_sub(1) - 1; }
};

#undef ATOMIC_ARITHMETIC_OPERATION

}

}