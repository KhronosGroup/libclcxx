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
#include <__ocl_type_traits_type_relations.h>
#include <__ocl_type_traits_address_spaces.h>

namespace cl
{

template <class T> struct remove_const;
template <class T> struct remove_volatile;
template <class T> struct remove_cv;
template <class T> struct remove_attrs;
template <class T> struct add_const;
template <class T> struct add_volatile;
template <class T> struct add_cv;
template <class T> struct remove_reference;
template <class T> struct add_lvalue_reference;
template <class T> struct add_rvalue_reference;
template <class T> struct remove_pointer;
template <class T> struct add_pointer;

template <class T>
using remove_const_t = typename remove_const<T>::type;
template <class T>
using remove_volatile_t = typename remove_volatile<T>::type;
template <class T>
using remove_cv_t = typename remove_cv<T>::type;
template <class T>
using remove_attrs_t = typename remove_attrs<T>::type;
template <class T>
using add_const_t = typename add_const<T>::type;
template <class T>
using add_volatile_t = typename add_volatile<T>::type;
template <class T>
using add_cv_t = typename add_cv<T>::type;
template <class T>
using remove_reference_t = typename remove_reference<T>::type;
template <class T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
template <class T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
template <class T>
using remove_pointer_t = typename remove_pointer<T>::type;
template <class T>
using add_pointer_t = typename add_pointer<T>::type;

/// \brief Type trait removing const qualifier from a type
///
template<class T>
struct remove_const { typedef T type; };

/// \brief Type trait removing const qualifier from a type
///
template<class T>
struct remove_const<const T> { typedef T type; };

/// \brief Type trait removing volatile qualifier from a type
///
template<class T>
struct remove_volatile { typedef T type; };

/// \brief Type trait removing volatile qualifier from a type
///
template<class T>
struct remove_volatile<volatile T> { typedef T type; };

/// \brief Type trait removing const and volatile qualifiers from a type
///
template<class T>
struct remove_cv { typedef remove_volatile_t<remove_const_t<T>> type; };

/// \brief Type trait removing address space and cv qualifiers
///
template<class T>
struct remove_attrs { typedef remove_cv_t<remove_as_t<T>> type; };

/// \brief Type trait adding const qualifier to a type
///
template<class T>
struct add_const { typedef const T type; };

/// \brief Type trait adding const qualifier to a type
///
template<class T>
struct add_const<const T> { typedef const T type; };

/// \brief Type trait adding volatile qualifier to a type
///
template<class T>
struct add_volatile { typedef volatile T type; };

/// \brief Type trait adding volatile qualifier to a type
///
template<class T>
struct add_volatile<volatile T> { typedef volatile T type; };

/// \brief Type trait adding const and volatile qualifiers to a type
///
template<class T>
struct add_cv { typedef add_volatile_t<add_const_t<T>> type; };

/// \brief Type trait checking if type is lvalue reference
///
template <class T>
struct is_lvalue_reference : false_type { };

/// \brief Type trait checking if type is lvalue reference
///
template <class T>
struct is_lvalue_reference<T&> : true_type { };

/// \brief Type trait checking if type is rvalue reference
///
template <class T>
struct is_rvalue_reference : false_type { };

/// \brief Type trait checking if type is rvalue reference
///
template <class T>
struct is_rvalue_reference<T&&> : true_type { };

/// \brief Type trait removing reference from a type
///
template <class T>
struct remove_reference { typedef T type; };

/// \brief Type trait removing reference from a type
///
template <class T>
struct remove_reference<T&> { typedef T type; };

/// \brief Type trait removing reference from a type
///
template <class T>
struct remove_reference<T&&> { typedef T type; };

namespace __details
{

/// \brief Helper trait for add_lvalue_reference
///
template <class T, bool = !is_same<remove_attrs_t<T>, void>::value>
struct __add_lvalue_reference_helper { typedef T& type; };

/// \brief Helper trait for add_lvalue_reference
///
template <class T>
struct __add_lvalue_reference_helper<T, false> { typedef T type; };

/// \brief Helper trait for add_rvalue_reference
///
template <class T, bool = !is_same<remove_attrs_t<T>, void>::value>
struct __add_rvalue_reference_helper { typedef T&& type; };

/// \brief Helper trait for add_rvalue_reference
///
template <class T>
struct __add_rvalue_reference_helper<T, false> { typedef T type; };

}

/// \brief Type trait making a lvalue reference from a type
///
template <class T>
struct add_lvalue_reference { typedef typename __details::__add_lvalue_reference_helper<T>::type type; };

/// \brief Type trait making a rvalue reference from a type
///
template <class T>
struct add_rvalue_reference { typedef typename __details::__add_rvalue_reference_helper<T>::type type; };

/// \brief Type trait checking if type is const type
///
template <class T>
struct is_const : false_type { };

/// \brief Type trait checking if type is const type
///
template <class T>
struct is_const<const T> : true_type { };

/// \brief Type trait checking if type is volatile type
///
template <class T>
struct is_volatile : false_type { };

/// \brief Type trait checking if type is volatile type
///
template <class T>
struct is_volatile<volatile T> : true_type { };

namespace __details
{

/// \brief Helper copying all cv qualifiers from one type to another
///
template <class T, class U, bool = is_const<T>::value, bool = is_volatile<T>::value>
struct __copy_cv_helper { typedef add_cv_t<U> type; };

/// \brief Helper copying all cv qualifiers from one type to another
///
template <class T, class U>
struct __copy_cv_helper<T, U, false, false> { typedef remove_cv_t<U> type; };

/// \brief Helper copying all cv qualifiers from one type to another
///
template <class T, class U>
struct __copy_cv_helper<T, U, true, false> { typedef add_const_t<remove_volatile_t<U>> type; };

/// \brief Helper copying all cv qualifiers from one type to another
///
template <class T, class U>
struct __copy_cv_helper<T, U, false, true> { typedef remove_const_t<add_volatile_t<U>> type; };

/// \brief Helper copying all address space and cv qualifiers from one type to another
///
template <class T, class U>
struct __copy_attrs_helper { typedef typename __copy_cv_helper<T, typename __copy_as_helper<T, U>::type>::type type; };

}

}