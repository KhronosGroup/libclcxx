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
#include <__ocl_type_traits_cv_ref_ptr.h>
#include <__ocl_type_traits_vectors.h>

namespace cl
{

template <class T> struct is_member_object_pointer;
template <class T> struct is_member_function_pointer;
template <class T> struct is_member_pointer;

/// \brief Type trait checking if type is integral
///
template <class T>
struct is_integral : integral_constant<bool, __is_integral(vector_element_t<T>)> { };

/// \brief Type trait checking if type is floating point
///
template <class T>
struct is_floating_point : integral_constant<bool, __is_floating_point(vector_element_t<T>)> { };

namespace __details
{

/// \brief check if given type is, possibly cv and address space qualified, boolean type (including vector types)
///
template <class T>
struct __is_bool : public integral_constant<bool, is_same<bool, remove_attrs_t<vector_element_t<T>>>::value> { };

/// \brief check if given type is, possibly cv-qualified, integral type but no bool
///
template <class T>
struct __is_integral_not_bool : public integral_constant<bool, is_integral<T>::value && !__is_bool<T>::value> { };

}

/// \brief Type trait checking if type is array
///
template <class T>
struct is_array : false_type { };

/// \brief Type trait checking if type is array
///
template <class T>
struct is_array<T[]> : true_type { };

/// \brief Type trait checking if type is array
///
template <class T, size_t Size>
struct is_array<T[Size]> : true_type { };

namespace __details
{

/// \brief Helper class for is_pointer
///
template <class T>
struct __is_pointer_helper : false_type { };

/// \brief Helper class for is_pointer
///
template <class T>
struct __is_pointer_helper<T*> : true_type { };

}

/// \brief Type trait checking if type is pointer
///
template <class T>
struct is_pointer : integral_constant<bool, __details::__is_pointer_helper<remove_attrs_t<T>>::value> { };

/// \brief Type trait checking if type is function
///
template <class T>
struct is_function : integral_constant<bool, __is_function(T)> { };

namespace __details
{

/// \brief Helper class for is member pointer trait
///
template <class T>
struct __is_member_pointer_helper : false_type { };

/// \brief Helper class for is member pointer trait
///
template <class T, class U>
struct __is_member_pointer_helper<T U::*> : true_type { };

/// \brief Helper class for is member function pointer trait
///
template<class T>
struct __is_member_function_pointer_helper : false_type { };

/// \brief Helper class for is member function pointer trait
///
template<class T, class U>
struct __is_member_function_pointer_helper<T U::*> : is_function<T> { };

}

/// \brief Type trait checking if type is member object pointer
///
template <class T>
struct is_member_object_pointer : integral_constant<bool, is_member_pointer<T>::value && !is_member_function_pointer<T>::value> { };

/// \brief Type trait checking if type is member function pointer
///
template<class T>
struct is_member_function_pointer : __details::__is_member_function_pointer_helper<remove_attrs_t<T>> { };

/// \brief Type trait checking if type is enum
///
template <class T>
struct is_enum : integral_constant<bool, __is_enum(T)> { };

/// \brief Type trait checking if type is union
///
template <class T>
struct is_union : integral_constant<bool, __is_union(T)> { };

/// \brief Type trait checking if type is class
///
template <class T>
struct is_class : integral_constant<bool, __is_class(T)> { };;

/// \brief Type trait checking if type is reference type
///
template <class T>
struct is_reference : integral_constant<bool, is_lvalue_reference<T>::value || is_rvalue_reference<T>::value> { };

/// \brief Type trait checking if type is member pointer
///
template <class T>
struct is_member_pointer : __details::__is_member_pointer_helper<remove_attrs_t<T>> { };

namespace __details
{

/// \brief Helper trait for remove pointer
///
template <class T>
struct __remove_pointer_helper { typedef T type; };

/// \brief Helper trait for remove pointer
///
template <class T>
struct __remove_pointer_helper<T*> { typedef T type; };

}

/// \brief Type trait removing pointer from type
///
template <class T>
struct remove_pointer : conditional<is_pointer<T>::value, typename __details::__remove_pointer_helper<remove_attrs_t<T>>::type, T> { };

/// \brief Type trait adding pointer to type
///
template <class T>
struct add_pointer { typedef remove_reference_t<T> * type; };

}