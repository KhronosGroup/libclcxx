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
#include <__ocl_spirv_common_opcodes.h>
#include <opencl_type_traits>

namespace cl
{

namespace __details
{

/// \brief different types => perform OpBitcast
///
template <typename To, typename From>
To __ALWAYS_INLINE __as_type(From const& arg)
{
    return __spirv::__make_OpBitcast_call<To>(arg);
}

/// \brief same types => NoOp
///
template <typename To, typename From>
To __ALWAYS_INLINE __as_type(To const& t)
{
    return t;
}

}

template <typename To, typename From>
To __ALWAYS_INLINE as_type(From const& arg)
{
    static_assert(!cl::is_void<To>::value && !cl::is_void<From>::value, "void type is not valid destination/source type for reinterpreting data with as_type operator.");
    static_assert(!cl::__details::__is_bool<To>::value && !cl::__details::__is_bool<From>::value, "bool type is not valid destination/source type for reinterpreting data with as_type operator.");
    static_assert(cl::is_fundamental<To>::value && cl::is_fundamental<From>::value, "as_type operator may be used only for reinterpreting data from/to builtin scalar or vector types (except void and bool).");
    static_assert(sizeof(To) == sizeof(From), "It is an error to use the as_type<T> operator to reinterpret data to a type of a different number of bytes.");

    return __details::__as_type<remove_attrs_t<To>, remove_attrs_t<From>>(arg);
}
}
