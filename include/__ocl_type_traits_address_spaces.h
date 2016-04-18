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

#include <__ocl_type_traits_base.h>

namespace cl
{
template <class T> struct remove_constant;
template <class T> struct remove_local;
template <class T> struct remove_global;
template <class T> struct remove_private;
template <class T> struct remove_generic;
template <class T> struct remove_as;
template <class T> struct add_constant;
template <class T> struct add_local;
template <class T> struct add_global;
template <class T> struct add_private;
template <class T> struct add_generic;

template <class T>
using remove_constant_t = typename remove_constant<T>::type;
template <class T>
using remove_local_t = typename remove_local<T>::type;
template <class T>
using remove_global_t = typename remove_global<T>::type;
template <class T>
using remove_private_t = typename remove_private<T>::type;
template <class T>
using remove_generic_t = typename remove_generic<T>::type;
template <class T>
using remove_as_t = typename remove_as<T>::type;
template <class T>
using add_constant_t = typename add_constant<T>::type;
template <class T>
using add_local_t = typename add_local<T>::type;
template <class T>
using add_global_t = typename add_global<T>::type;
template <class T>
using add_private_t = typename add_private<T>::type;
template <class T>
using add_generic_t = typename add_generic<T>::type;

/// \brief Type trait removing __constant address space qualifier from a type
///
template< class T > struct remove_constant { typedef T type; };

/// \brief Type trait Type trait removing __constant address space qualifier from a type
///
template< class T > struct remove_constant<__constant T> { typedef T type; };

/// \brief Type trait removing __local address space qualifier from a type
///
template< class T > struct remove_local { typedef T type; };

/// \brief Type trait Type trait removing __local address space qualifier from a type
///
template< class T > struct remove_local<__local T> { typedef T type; };

/// \brief Type trait removing __global address space qualifier from a type
///
template< class T > struct remove_global { typedef T type; };

/// \brief Type trait Type trait removing __global address space qualifier from a type
///
template< class T > struct remove_global<__global T> { typedef T type; };

/// \brief Type trait removing __private address space qualifier from a type
///
template< class T > struct remove_private { typedef T type; };

/// \brief Type trait Type trait removing __global address space qualifier from a type
///
template< class T > struct remove_private<__private T> { typedef T type; };

/// \brief Type trait removing __generic address space qualifier from a type
///
template< class T > struct remove_generic { typedef T type; };

/// \brief Type trait Type trait removing __generic address space qualifier from a type
///
template< class T > struct remove_generic<__generic T> { typedef T type; };

/// \brief Type trait Type trait removing address space qualifier from a type
///
template< class T > struct remove_as { typedef remove_constant_t<remove_local_t<remove_global_t<remove_private_t<remove_generic_t<T>>>>> type; };

/// \brief Type trait adding __constant qualifier to a type
///
template< class T > struct add_constant { typedef __constant remove_as_t<T> type; };

/// \brief Type trait adding __constant qualifier to a type
///
template< class T > struct add_constant<__constant T> { typedef __constant remove_as_t<T> type; };

/// \brief Type trait adding __local qualifier to a type
///
template< class T > struct add_local { typedef __local remove_as_t<T> type; };

/// \brief Type trait adding __local qualifier to a type
///
template< class T > struct add_local<__local T> { typedef __local remove_as_t<T> type; };

/// \brief Type trait adding __global qualifier to a type
///
template< class T > struct add_global { typedef __global remove_as_t<T> type; };

/// \brief Type trait adding __global qualifier to a type
///
template< class T > struct add_global<__global T> { typedef __global remove_as_t<T> type; };

/// \brief Type trait adding __private qualifier to a type
///
template< class T > struct add_private { typedef __private remove_as_t<T> type; };

/// \brief Type trait adding __global qualifier to a type
///
template< class T > struct add_private<__private T> { typedef __private remove_as_t<T> type; };

/// \brief Type trait adding __generic qualifier to a type
///
template< class T > struct add_generic { typedef __generic remove_as_t<T> type; };

/// \brief Type trait adding __generic qualifier to a type
///
template< class T > struct add_generic<__generic T> { typedef __generic remove_as_t<T> type; };

/// \brief Type trait checking if type is constant type
///
template <class T>
struct is_constant : false_type { };

/// \brief Type trait checking if type is constant type
///
template <class T>
struct is_constant<__constant T> : true_type { };

/// \brief Type trait checking if type is local type
///
template <class T>
struct is_local: false_type { };

/// \brief Type trait checking if type is local type
///
template <class T>
struct is_local<__local T> : true_type { };

/// \brief Type trait checking if type is global type
///
template <class T>
struct is_global : false_type { };

/// \brief Type trait checking if type is global type
///
template <class T>
struct is_global<__global T> : true_type { };

/// \brief Type trait checking if type is private type
///
template <class T>
struct is_private : false_type { };

/// \brief Type trait checking if type is private type
///
template <class T>
struct is_private<__private T> : true_type { };

/// \brief Type trait checking if type is generic type
///
template <class T>
struct is_generic : false_type { };

/// \brief Type trait checking if type is generic type
///
template <class T>
struct is_generic<__generic T> : true_type { };

namespace __details
{
/// \brief Helper copying all address space qualifiers from one type to another
///
template <class T, class U, bool = is_constant<T>::value, bool = is_global<T>::value, bool = is_local<T>::value, bool = is_private<T>::value, bool = is_generic<T>::value>
struct __copy_as_helper { typedef U type; };

/// \brief Helper copying all address space qualifiers from one type to another
///
template <class T, class U>
struct __copy_as_helper<T, U, false, false, false, false, false> { typedef remove_as_t<U> type; };

/// \brief Helper copying all address space qualifiers from one type to another
///
template <class T, class U>
struct __copy_as_helper<T, U, true, false, false, false, false> { typedef add_constant_t<remove_as_t<U>> type; };

/// \brief Helper copying all address space qualifiers from one type to another
///
template <class T, class U>
struct __copy_as_helper<T, U, false, true, false, false, false> { typedef add_global_t<remove_as_t<U>> type; };

/// \brief Helper copying all address space qualifiers from one type to another
///
template <class T, class U>
struct __copy_as_helper<T, U, false, false, true, false, false> { typedef add_local_t<remove_as_t<U>> type; };

/// \brief Helper copying all address space qualifiers from one type to another
///
template <class T, class U>
struct __copy_as_helper<T, U, false, false, false, true, false> { typedef add_private_t<remove_as_t<U>> type; };

/// \brief Helper copying all address space qualifiers from one type to another
///
template <class T, class U>
struct __copy_as_helper<T, U, false, false, false, false, true> { typedef add_generic_t<remove_as_t<U>> type; };
}
}