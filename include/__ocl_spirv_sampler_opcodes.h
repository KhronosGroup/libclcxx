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

namespace cl
{
namespace __spirv
{
/// \brief SPIRV Sampler Addressing Mode
///
/// Addressing mode for creating constant samplers. Used by OpConstantSampler.
enum class SamplerAddressingMode: int
{
    None           = 0,
    ClampToEdge    = 1,
    Clamp          = 2,
    Repeat         = 3,
    RepeatMirrored = 4
};

/// \brief SPIRV Sampler Filter Mode
///
/// Filter mode for creating constant samplers. Used by OpConstantSampler.
enum class SamplerFilterMode: int
{
    Nearest = 0,
    Linear  = 1
};

/// \brief SPIRV Normalized Mode
///
/// Normalized mode for creating constant samplers. Used by OpConstantSampler.
enum class SamplerCoordinates: int
{
    NonNormalized = 0,
    Normalized    = 1
};

/// \brief SPIRV sampler representation
///
struct OpTypeSampler;

/// \brief SPIRV constant sampler initializer representation
///
struct OpConstantSampler
{
    constexpr OpConstantSampler(SamplerAddressingMode AddressingMode, SamplerCoordinates Coordinates, SamplerFilterMode FilterMode): _AddressingMode(AddressingMode), _Coordinates(Coordinates), _FilterMode(FilterMode) { }

    SamplerAddressingMode _AddressingMode;
    SamplerCoordinates _Coordinates;
    SamplerFilterMode _FilterMode;
};

}

}