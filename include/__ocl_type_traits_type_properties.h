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

#include <__ocl_type_traits_type_relations.h>
#include <__ocl_type_traits_type_categories.h>
#include <__ocl_type_traits_supported_operations.h>

namespace cl
{

template <class T> struct is_scalar;

/// \brief Type trait checking if type is void
///
template <class T>
struct is_void : is_same<void, remove_attrs_t<T>> { };

/// \brief Type trait checking if type is nullptr_t
///
template <class T>
struct is_null_pointer : is_same<decltype(nullptr), remove_attrs_t<T>> { };

/// \brief Type trait checking if type is either integral or floating point type
///
template <class T>
struct is_arithmetic : integral_constant<bool, is_integral<T>::value || is_floating_point<T>::value> { };

/// \brief Type trait checking if type is fundamental type
///
template <class T>
struct is_fundamental : integral_constant<bool, is_arithmetic<T>::value ||
                                                is_void<T>::value ||
                                                is_null_pointer<T>::value> { };

/// \brief Type trait checking if type is object
///
template <class T>
struct is_object : integral_constant<bool, is_class<T>::value || is_array<T>::value || is_scalar<T>::value || is_union<T>::value> { };

/// \brief Type trait checking if type is scalar
///
template <class T>
struct is_scalar : integral_constant<bool, is_null_pointer<T>::value ||
                                           is_arithmetic<T>::value ||
                                           is_pointer<T>::value ||
                                           is_member_pointer<T>::value ||
                                           is_enum<T>::value> { };

/// \brief Type trait checking if type is compound, ie. not fundamental
///
template <class T>
struct is_compound : integral_constant<bool, !is_fundamental<T>::value> { };

/// \brief Type trait checking if type is trivially copyable
///
template <class T>
struct is_trivially_copyable : integral_constant<bool, __is_trivially_copyable(T)> { };

/// \brief Type trait checking if type is trivially copyable and trivially default constructible type
///
template <class T>
struct is_trivial : integral_constant<bool, is_trivially_copyable<T>::value && is_trivially_default_constructible<T>::value> { };

/// \brief Type trait checking if type has standard layout
///
template <class T>
struct is_standard_layout : integral_constant<bool, __is_standard_layout(T)> { };

/// \brief Type trait checking if type is plain old datatype ie. is trivial and has standard layout
///
template <class T>
struct is_pod : integral_constant<bool, is_trivial<T>::value && is_standard_layout<T>::value> { };

/// \brief Type trait checking if type is literal type
///
template <class T>
struct is_literal_type : integral_constant<bool, __is_literal_type(T)> { };

/// \brief Type trait checking if type is empty
///
template <class T>
struct is_empty : integral_constant<bool, __is_empty(T)> { };

/// \brief Type trait checking if type is polymorphic
///
template <class T>
struct is_polymorphic : integral_constant<bool, __is_polymorphic(T)> { };

/// \brief Type trait checking if type is abstract
///
template <class T>
struct is_abstract : integral_constant<bool, __is_abstract(T)> { };

/// \brief Type trait checking if type is final
///
template <class T>
struct is_final : integral_constant<bool, __is_final(T)> { };

namespace __details
{

/// \brief Helper class for is is signed trait
///
template <class T, bool = is_arithmetic<T>::value>
struct __is_signed_helper : integral_constant<bool, T(-1) < T(0)> { };

/// \brief Helper class for is is signed trait
///
template <class T>
struct __is_signed_helper<T, false> : false_type { };

/// \brief Helper class for is is unsigned trait
///
template <class T, bool = is_arithmetic<T>::value>
struct __is_unsigned_helper : integral_constant<bool, T(0) < T(-1)> { };

/// \brief Helper class for is is unsigned trait
///
template <class T>
struct __is_unsigned_helper<T, false> : false_type { };

}

/// \brief Type trait checking if type is arithmetic and signed
///
template <class T>
struct is_signed : __details::__is_signed_helper<vector_element_t<T>> { };

/// \brief Type trait checking if type is arithmetic and unsigned
///
template <class T>
struct is_unsigned : __details::__is_unsigned_helper<vector_element_t<T>> { };

}