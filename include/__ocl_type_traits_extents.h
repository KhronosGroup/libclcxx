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

namespace cl
{

template <class T> struct remove_extent;
template <class T> struct remove_all_extents;

template <class T>
using remove_extent_t = typename remove_extent<T>::type;
template <class T>
using remove_all_extents_t = typename remove_all_extents<T>::type;

namespace __details
{

/// \brief Helper trait removing all extents from a type
///
template <class T, bool = is_same<T, remove_extent_t<T>>::value>
struct __remove_all_extents_helper { typedef T type; };

/// \brief Helper trait removing all extents from a type
///
template <class T>
struct __remove_all_extents_helper<T, false> { typedef typename __remove_all_extents_helper<remove_extent_t<T>>::type type; };

/// \brief Helper trait for extent
///
template <class T, unsigned Count>
struct __trim_extent { typedef typename __trim_extent<remove_extent_t<T>, Count - 1>::type type; };

/// \brief Helper trait for extent
///
template <class T>
struct __trim_extent<T, 0> { typedef T type; };

/// \brief Helper trait for extent
///
template <class T>
struct __extent_helper : integral_constant<size_t, 0> { };

/// \brief Helper trait for extent
///
template <class T>
struct __extent_helper<T[]> : integral_constant<size_t, 0> { };

/// \brief Helper trait for extent
///
template <class T, size_t Size>
struct __extent_helper<T[Size]> : integral_constant<size_t, Size> { };

}

/// \brief Type trait removing last extent from a type
///
template <class T>
struct remove_extent { typedef T type; };

/// \brief Type trait removing last extent from a type
///
template <class T>
struct remove_extent<T[]> { typedef T type; };

/// \brief Type trait removing last extent from a type
///
template <class T, size_t Size>
struct remove_extent<T[Size]> { typedef T type; };

/// \brief Type trait removing all extents from a type
///
template <class T>
struct remove_all_extents { typedef typename __details::__remove_all_extents_helper<T>::type type; };

/// \brief Type trait obtaining extent of I-th dimension of an array
///
template <class T, unsigned I = 0>
struct extent : __details::__extent_helper<typename __details::__trim_extent<T, I>::type> { };

}