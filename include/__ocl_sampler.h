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
#include <__ocl_type_traits_type_generators.h>
#include <__ocl_spirv_sampler_opcodes.h>
#include <__ocl_marker_type.h>

namespace cl
{
namespace __details
{
/// \brief Forward declaration of image sample trait
///
template <typename _ElemType, typename _ImageType>
struct __image_sample_trait;

/// \brief Helper class creating OpConstantSampler objects
///
template <__spirv::SamplerAddressingMode A, __spirv::SamplerCoordinates B, __spirv::SamplerFilterMode C>
struct OpConstantSampler_Creator
{
    static __spirv::OpConstantSampler value;
};

template <__spirv::SamplerAddressingMode A, __spirv::SamplerCoordinates B, __spirv::SamplerFilterMode C>
__spirv::OpConstantSampler OpConstantSampler_Creator<A, B, C>::value(A, B, C);

using sampler_coordinates_type = underlying_type_t<__spirv::SamplerCoordinates>;
using filtering_mode_type = underlying_type_t<__spirv::SamplerFilterMode>;
using sampler_addressing_mode_type = underlying_type_t<__spirv::SamplerAddressingMode>;

}

/// \brief Enumerable describing sampler coordinates
///
enum class normalized_coordinates
{
    normalized   = static_cast<__details::sampler_coordinates_type>(__spirv::SamplerCoordinates::Normalized),
    unnormalized = static_cast<__details::sampler_coordinates_type>(__spirv::SamplerCoordinates::NonNormalized)
};

/// \brief Enumerable describing sampler addressing mode
///
enum class addressing_mode
{
    mirrored_repeat = static_cast<__details::sampler_addressing_mode_type>(__spirv::SamplerAddressingMode::RepeatMirrored),
    repeat          = static_cast<__details::sampler_addressing_mode_type>(__spirv::SamplerAddressingMode::Repeat),
    clamp_to_edge   = static_cast<__details::sampler_addressing_mode_type>(__spirv::SamplerAddressingMode::ClampToEdge),
    clamp           = static_cast<__details::sampler_addressing_mode_type>(__spirv::SamplerAddressingMode::Clamp),
    none            = static_cast<__details::sampler_addressing_mode_type>(__spirv::SamplerAddressingMode::None)
};

/// \brief Enumerable describing sampler filtering mode
///
enum class filtering_mode
{
    nearest = static_cast<__details::filtering_mode_type>(__spirv::SamplerFilterMode::Nearest),
    linear  = static_cast<__details::filtering_mode_type>(__spirv::SamplerFilterMode::Linear)
};

/// \brief Class representing OpenCL C++ sampler
///
class sampler: marker_type
{
public:
    sampler() = delete;
    constexpr sampler(const sampler &) __global = default;
    constexpr sampler(sampler &&) __global = default;

    sampler& operator=(const sampler&) = delete;
    sampler& operator=(sampler&&) = delete;

private:
    template<addressing_mode A, normalized_coordinates C, filtering_mode F>
    friend constexpr sampler make_sampler();

    template <typename _ElemType, typename _ImageType>
    friend struct __details::__image_sample_trait;

    constexpr sampler(__global const __spirv::OpConstantSampler &handle): _handle(
        // force evaluation as constant value (if possible)
        __builtin_constant_p((__global const __spirv::OpTypeSampler*)(&handle))
            ? (__global const __spirv::OpTypeSampler*)(&handle)
            : (__global const __spirv::OpTypeSampler*)(&handle)) { };

    __global const __spirv::OpTypeSampler *_handle;
};

/// \brief Function creating sampler objects
///
template<addressing_mode A, normalized_coordinates C, filtering_mode F>
__ALWAYS_INLINE constexpr sampler make_sampler()
{
    return { __details::OpConstantSampler_Creator<static_cast<__spirv::SamplerAddressingMode>(A), static_cast<__spirv::SamplerCoordinates>(C), static_cast<__spirv::SamplerFilterMode>(F)>::value };
};

}