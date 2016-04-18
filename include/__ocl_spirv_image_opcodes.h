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
#include <__ocl_functions_macros.h>
#include <__ocl_spirv_access_opcodes.h>
#include <__ocl_spirv_sampler_opcodes.h>

#define REGION true

namespace cl
{

namespace __spirv
{
/// \brief SPIRV image formats
///
/// Declarative image format. Used by OpTypeImage.
enum class ImageFormat: int
{
    Unknown      = 0,
    Rgba32f      = 1,
    Rgba16f      = 2,
    R32f         = 3,
    Rgba8        = 4,
    Rgba8Snorm   = 5,
    Rg32f        = 6,
    Rg16f        = 7,
    R11fG11fB10f = 8,
    R16f         = 9,
    Rgba16       = 10,
    Rgb10A2      = 11,
    Rg16         = 12,
    Rg8          = 13,
    R16          = 14,
    R8           = 15,
    Rgba16Snorm  = 16,
    Rg16Snorm    = 17,
    Rg8Snorm     = 18,
    R16Snorm     = 19,
    R8Snorm      = 20,
    Rgba32i      = 21,
    Rgba16i      = 22,
    Rgba8i       = 23,
    R32i         = 24,
    Rg32i        = 25,
    Rg16i        = 26,
    Rg8i         = 27,
    R16i         = 28,
    R8i          = 29,
    Rgba32ui     = 30,
    Rgba16ui     = 31,
    Rgba8ui      = 32,
    R32ui        = 33,
    Rgb10a2ui    = 34,
    Rg32ui       = 35,
    Rg16ui       = 36,
    Rg8ui        = 37,
    R16ui        = 38,
    R8ui         = 39
};

/// \brief SPIRV Image Channel Data Type
///
/// Image channel data type returned by OpImageQueryFormat.
enum class ImageChannelOrder: int
{
    R            = 0,
    A            = 1,
    RG           = 2,
    RA           = 3,
    RGB          = 4,
    RGBA         = 5,
    BGRA         = 6,
    ARGB         = 7,
    Intensity    = 8,
    Luminance    = 9,
    Rx           = 10,
    RGx          = 11,
    RGBx         = 12,
    Depth        = 13,
    DepthStencil = 14,
    sRGB         = 15,
    sRGBx        = 16,
    sRGBA        = 17,
    sBGRA        = 18,
    ABGR         = 19
};

/// \brief SPIRV Image Channel Data Type
///
/// Image channel data type returned by OpImageQueryFormat.
enum class ImageChannelDataType: int
{
    SnormInt8        = 0,
    SnormInt16       = 1,
    UnormInt8        = 2,
    UnormInt16       = 3,
    UnormShort565    = 4,
    UnormShort555    = 5,
    UnormInt101010   = 6,
    SignedInt8       = 7,
    SignedInt16      = 8,
    SignedInt32      = 9,
    UnsignedInt8     = 10,
    UnsignedInt16    = 11,
    UnsignedInt32    = 12,
    HalfFloat        = 13,
    Float            = 14,
    UnormInt24       = 15,
    UnormInt101010_2 = 16
};

/// \brief SPIRV Image Operands
///
enum class ImageOperands: int
{
    None         = 0x0,
    Bias         = 0x1,
    Lod          = 0x2,
    Grad         = 0x4,
    ConstOffset  = 0x8,
    Offset       = 0x10,
    ConstOffsets = 0x20,
    Sample       = 0x40,
    MinLod       = 0x80,
};

/// \brief SPIRV Dim
///
/// Dimensionality of an image. Used by OpTypeImage.
enum class Dim: int
{
    _1D         = 0,
    _2D         = 1,
    _3D         = 2,
    Cube        = 3,
    Rect        = 4,
    Buffer      = 5,
    SubpassData = 6
};

template<class SampledType, Dim D, bool Depth, bool Array, bool MS, int Sampled, ImageFormat Format, AccessQualifier Acc>
struct OpTypeImage;

template<class SampledType, Dim D, bool Depth, bool Array, bool MS, int Sampled, ImageFormat Format, AccessQualifier Acc>
struct OpTypeSampledImage;

#if REGION | Read_image_functions_forward_declarations

/// \brief SPIRV declaration of function reading a texel from an image without sampler
///
MAKE_SPIRV_CALLABLE_WITH_TEMPLATE_RETTYPE(OpImageRead)

#endif

#if REGION | Sample_image_functions_forward_declarations

/// \brief SPIRV declaration of function creating SampledImage from image and a sampler
MAKE_SPIRV_CALLABLE(OpSampledImage)

/// \brief SPIRV declaration of function reading an image sample with level of detail
///
MAKE_SPIRV_CALLABLE_WITH_TEMPLATE_RETTYPE(OpImageSampleExplicitLod);

#endif

#if REGION | Write_image_functions_forward_declarations

/// \brief SPIRV declaration of function writing a texel to an image without sampler
///
MAKE_SPIRV_CALLABLE(OpImageWrite);

#endif

#if REGION | Common_image_functions_overloads

/// \brief SPIRV declaration of function returning dimensions of an image with no level of detail
///
/// @return vector filled in with [width, height, depth, elements] where elements is the number of layers in an image array
MAKE_SPIRV_CALLABLE(OpImageQuerySize);


/// \brief SPIRV declaration of function returning dimensions of an image with level of detail
///
/// @return vector filled in with [width, height, depth, elements] where elements is the number of layers in an image array
MAKE_SPIRV_CALLABLE(OpImageQuerySizeLod);


/// \brief SPIRV declaration of function returning the image format
///
/// @return image channel data type
MAKE_SPIRV_CALLABLE(OpImageQueryFormat);


/// \brief SPIRV declaration of function returning the image channel order
///
/// @return image channel order
MAKE_SPIRV_CALLABLE(OpImageQueryOrder);

/// \brief SPIRV declaration of function returning number of samples in the 2D multisample image
///
/// @return number of samples
MAKE_SPIRV_CALLABLE(OpImageQuerySamples);

/// \brief SPIRV declaration of function returning number of mipmaps
///
/// @return number of mipmaps
MAKE_SPIRV_CALLABLE(OpImageQueryLevels);

#endif

}

}

#undef REGION