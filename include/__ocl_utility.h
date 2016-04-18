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

#include <__ocl_config.h>
#include <__ocl_type_traits_cv_ref_ptr.h>

namespace cl
{

/// \brief Converts any type to rvalue reference type which allows to use it in decltype expressions even if constructors are unavailable
///
template<class T>
add_rvalue_reference_t<T> declval( );

template <class T>
__ALWAYS_INLINE constexpr T&& forward(typename remove_reference<T>::type& t) __NOEXCEPT
{
  return static_cast<T&&>(t);
}
template <class T>
__ALWAYS_INLINE constexpr T&& forward(typename remove_reference<T>::type&& t) __NOEXCEPT
{
  return static_cast<T&&>(t);
}
template <class T>
__ALWAYS_INLINE constexpr typename remove_reference<T>::type&& move(T&& t) __NOEXCEPT
{
  return static_cast<typename remove_reference<T>::type&&>(t);
}

template<class T>
void swap(T& a, T& b) __NOEXCEPT
{
  remove_as_t<T> t(cl::move(a));
  b = cl::move(a);
  a = cl::move(t);
}

//TODO: template <class T, size_t N>
//      void swap(T (&a)[N], T (&b)[N]) __NOEXCEPT;
}
