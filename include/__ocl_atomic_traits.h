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

#include <opencl_type_traits>

namespace cl
{
namespace __details
{

/// \brief Trait checking if type is valid atomic type
///
template <typename T>
struct __is_valid_atomic_type : integral_constant<bool, __is_one_of<T, int, uint,
#if defined(cl_khr_int64_base_atomics) && defined(cl_khr_int64_extended_atomics)
    long, ulong,
#if defined(cl_khr_fp64)
    double,
#endif
#endif
    float, intptr_t, uintptr_t, size_t, ptrdiff_t>::value> { };

/// \brief Trait checking if type is valid atomic type
///
/// Always true for pointer types
template <typename T>
struct __is_valid_atomic_type<T*> : integral_constant<bool,
#if (__INTPTR_WIDTH__ == 32) || (defined(cl_khr_int64_base_atomics) && defined(cl_khr_int64_extended_atomics))
true
#else
false
#endif
> { };

/// \brief Trait checking if type is valid atomic integral type
///
template <typename T>
struct __is_atomic_integer_type : integral_constant<bool, is_integral<T>::value && __is_valid_atomic_type<T>::value> { };

/// \brief Trait checking if type is valid atomic integral type
///
/// Always true for pointer types
template <typename T>
struct __is_atomic_integer_type<T*> : true_type { };

/// \brief Trait generating pair of types used for matching between OCL C++ and SPIRV types
///
template <typename T>
struct __atomic_types
{
    typedef T arithmetic_result_type;
    typedef T spirv_type;
};

/// \brief Trait generating pair of types used for matching between OCL C++ and SPIRV types
///
/// SPIRV doesn't accept floating point arguments for operations like OpAtomicExchange so we are going to treat float/double as integral types with appropriate size.
/// Since no arithmetic operations are allowed on floating point atomics there is no 'arithmetic_result_type' defined for them
template <>
struct __atomic_types<float>
{
    typedef int spirv_type;
};

#if defined(cl_khr_fp64) && defined(cl_khr_int64_base_atomics) && defined(cl_khr_int64_extended_atomics)
/// \brief Trait generating pair of types used for matching between OCL C++ and SPIRV types
///
/// SPIRV doesn't accept floating point arguments for operations like OpAtomicExchange so we are going to treat float/double as integral types with appropriate size.
/// Since no arithmetic operations are allowed on floating point atomics there is no 'arithmetic_result_type' defined for them
template <>
struct __atomic_types<double>
{
    typedef long spirv_type;
};
#endif

/// \brief Trait generating pair of types used for matching between OCL C++ and SPIRV types
///
template <typename T>
struct __atomic_types<T*>
{
    typedef ptrdiff_t arithmetic_result_type;
    typedef uintptr_t spirv_type;
};


}
}