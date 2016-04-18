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
    
template <bool b, class T, class F> struct conditional;

template <bool b, class T, class F>
using conditional_t = typename conditional<b,T,F>::type;

/// \brief Type trait checking if two types are the same
///
template <class _A, class _B>
struct is_same : false_type { };

/// \brief Type trait checking if two types are the same
///
template <class _A>
struct is_same<_A, _A> : true_type { };

/// \brief Type trait checking if T is base class of U or if T is the same class as U
///
template <class T, class U>
struct is_base_of : integral_constant<bool, __is_base_of(T, U)> { };

/// \brief Type trait checking if T is implicitly convertible to U or if T is the same class as U
///
template <class T, class U>
struct is_convertible : integral_constant<bool, __is_convertible(T, U)> { };

/// \brief Type trait that selects types based on a flag, for true it selects first for false second
///
template <bool Select, class T, class U>
struct conditional { typedef T type; };

/// \brief Type trait that selects types based on a flag, for true it selects first for false second
///
template <class T, class U>
struct conditional<false, T, U> { typedef U type; };


}