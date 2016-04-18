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

#include <__ocl_type_traits.h>



namespace cl
{

namespace __details
{
    /// \brief Helper trait checking if T is a valid non-depth image pixel type
    template <typename T>
    struct __is_image_pixel_type : public integral_constant<bool, __is_one_of<T, int4, float4, uint4
#ifdef cl_khr_fp16
        , half4
#endif
    >::value> { };

    /// \brief Helper trait checking if T is a valid depth image pixel type
    template <typename T>
    struct __is_image_depth_type : public integral_constant<bool, __is_one_of<T, float
#ifdef cl_khr_fp16
        , half
#endif
    >::value> { };

    template<typename T>
    struct __is_ms_image_pixel_type : public integral_constant <bool, __is_one_of<T, float4, int4, uint4>::value> { };

    template<typename T>
    struct __is_ms_image_depth_type : public integral_constant <bool, __is_one_of<T, float>::value> { };

    /// \brief Helper trait checking if proper type is used for sampler reads
    template <typename T>
    struct __is_image_sampler_coord_type : public integral_constant<bool, __is_one_of<T, float, float2, float3>::value> { };

    /// \brief Helper trait checking if proper type is used for samplerless reads
    template <typename T>
    struct __is_image_read_coord_type : public integral_constant<bool, __is_one_of<T, int, int2, int3>::value> { };

    /// \brief Helper trait checking if proper type is used for writes (this is the same as for samplerless reads)
    template <typename T>
    struct __is_image_write_coord_type : public integral_constant<bool, __is_image_read_coord_type<T>::value> { };

    /// \brief Helper structure defining sample and read coordinate types given dimension of image (+1 for buffer types)
    template <size_t _Size>
    struct __image_sample_coordinates { static_assert( __always_false<__image_sample_coordinates>::value, "Coordinates size must be 1, 2 or 3" ); };

    /// \brief Helper structure defining sample and read coordinate types given dimension of image (+1 for buffer types)
    template <>
    struct __image_sample_coordinates<1>
    {
        typedef float floating_point;
        typedef int integral;
    };

    /// \brief Helper structure defining sample and read coordinate types given dimension of image (+1 for buffer types)
    template <>
    struct __image_sample_coordinates<2>
    {
        typedef float2 floating_point;
        typedef int2 integral;
    };

    /// \brief Helper structure defining sample and read coordinate types given dimension of image (+1 for buffer types)
    template <>
    struct __image_sample_coordinates<3>
    {
        typedef float3 floating_point;
        typedef int3 integral;
    };

}

}