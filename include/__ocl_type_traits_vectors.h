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

#include <__ocl_type_traits_helpers.h>
#include <__ocl_type_traits_cv_ref_ptr.h>

namespace cl
{

template <class T> struct is_vector_type;
template <class T> struct vector_element;
template <class T> using vector_element_t = typename vector_element<T>::type;
template <class T> struct vector_size;
template <class T, uint DIM> struct make_vector;
template <class T, uint DIM> using make_vector_t = typename make_vector<T,DIM>::type;

/// \brief matches true_type if T is (possibly cv-qualified) vector type or reference to vector type, otherwise matches false_type
///
template <typename T>
struct is_vector_type : public integral_constant<bool, (vector_size<T>::value > 1)> { };

template <typename T>
struct is_vector_channel_type : public integral_constant<bool, __is_integral(T) || __is_floating_point(T)> { };


namespace __details
{

/// \brief Returns scalar type related with given type T. This is helper structure which also gets vector's size returned by __get_vector_size<T>.
///
///  By default we assume that T is in fact vector type (which means DIM > 1) and returns type of T.x as type. In other case appropriate specialization is used.
///  Returned type shares cv qualifiers with type T.
///
template <typename T, uint Size = vector_size<T>::value> struct __vector_element { typedef typename __copy_attrs_helper<T, decltype(T{}.x)>::type type; };

/// \brief Specialization which handles case when given type T isn't vector type - returns T as type
///
template <typename T> struct __vector_element<T,1> { typedef T type; };

}

/// \brief returns V if T is possibly cv-qualified V{2|3|4|8|16} or reference to any of that types; otherwise returns T. Retuned type has same cv-qualifiers as T
///
template <typename T>
struct vector_element { typedef typename __details::__vector_element<remove_reference_t<T>>::type type; };

namespace __details
{

#ifdef cl_khr_fp64
 #define __DOUBLE_VECTOR(size) double##size,
#else
 #define __DOUBLE_VECTOR(size)
#endif

/// \brief macro for checking if type T is vector of given size
///
#define __CHECK_SIZE(size) \
    __is_one_of<remove_attrs_t<T>, \
        bool##size, \
        char##size, uchar##size, \
        short##size, ushort##size, \
        int##size, uint##size, \
        long##size, ulong##size, \
        half##size, \
        __DOUBLE_VECTOR(size) \
        float##size >::value

/// \brief Brute-force check if given type T (possibly cv-qualified) is any vector type with size 2, 3 etc., if all checks fail value 1 is used
///
template <typename T>
struct __vector_size : public integral_constant<uint,
    __CHECK_SIZE(2) ? 2 :
    __CHECK_SIZE(3) ? 3 :
    __CHECK_SIZE(4) ? 4 :
    __CHECK_SIZE(8) ? 8 :
    __CHECK_SIZE(16) ? 16 : 1>
{};

#undef __DOUBLE_VECTOR
#undef __CHECK_SIZE

}

/// \brief holds number of elements in T if T is (possibly cv-qualified) vector type or reference to vector type, otherwise 1 is used
///
template <typename T>
struct vector_size : public integral_constant<uint, __details::__vector_size<remove_attrs_t<remove_reference_t<T>>>::value> { };


namespace __details
{

/// \brief macro to create specializations of __make_vector with all possible vector dimensions and given scalar type 'vtype'
///
#define __MAKE_TYPE(vtype) \
    template <> struct __make_vector<vtype, 2> { typedef vtype##2 type; }; \
    template <> struct __make_vector<vtype, 3> { typedef vtype##3 type; }; \
    template <> struct __make_vector<vtype, 4> { typedef vtype##4 type; }; \
    template <> struct __make_vector<vtype, 8> { typedef vtype##8 type; }; \
    template <> struct __make_vector<vtype, 16> { typedef vtype##16 type; }

/// \brief calls __MAKE_TYPE for given vtype and its unsigned version
///
#define _MAKE_TYPE(vtype) __MAKE_TYPE(vtype); __MAKE_TYPE(u##vtype)

/// \brief Basic template structure for making vector type from given scalar type T and size Size. Assumes invalidity by default and exposes T as result type.
///
///    T shall not be cv-qualified.
///
template <typename T, uint Size>     struct __make_vector        { typedef T type; };

/// \brief Valid specializations of __make_vector which map to appropriate vector types. Note that macros starting with one underscore create specializations for both signed and unsigned types
///
__MAKE_TYPE(bool);
_MAKE_TYPE(char);
_MAKE_TYPE(short);
_MAKE_TYPE(int);
_MAKE_TYPE(long);
__MAKE_TYPE(half);
#ifdef cl_khr_fp64
__MAKE_TYPE(double);
#endif
__MAKE_TYPE(float);

template <> struct __make_vector<signed char, 2> { typedef char2 type; };
template <> struct __make_vector<signed char, 3> { typedef char3 type; };
template <> struct __make_vector<signed char, 4> { typedef char4 type; };
template <> struct __make_vector<signed char, 8> { typedef char8 type; };
template <> struct __make_vector<signed char, 16> { typedef char16 type; };

#undef _MAKE_TYPE
#undef __MAKE_TYPE

}

/// \brief returns vector type with Size elements of type T, fires static_assert if either T or Size are invalid (e.g. T == double without cl_khr_fp64 extension or Size == 5)
///
///   Returned type is not cv-qualified (even if T is)
///
template <typename T, uint Size> struct make_vector { typedef typename __details::__copy_attrs_helper<remove_reference_t<T>, typename __details::__make_vector<remove_attrs_t<remove_reference_t<T>>,Size>::type>::type type; };

}

