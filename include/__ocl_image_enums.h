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

#include <__ocl_spirv_image_opcodes.h>
#include <__ocl_type_traits_type_generators.h>

namespace cl
{
namespace __details
{
    using channel_data_type = underlying_type_t<__spirv::ImageChannelDataType>;
    using channel_order_type = underlying_type_t<__spirv::ImageChannelOrder>;
    using dim_type = underlying_type_t<__spirv::Dim>;
}

/// \brief Enumerable describing channel type of the image
///
enum class image_channel_type
{
    snorm_int8          = static_cast<__details::channel_data_type>(__spirv::ImageChannelDataType::SnormInt8),
    snorm_int16         = static_cast<__details::channel_data_type>(__spirv::ImageChannelDataType::SnormInt16),
    unorm_int8          = static_cast<__details::channel_data_type>(__spirv::ImageChannelDataType::UnormInt8),
    unorm_int16         = static_cast<__details::channel_data_type>(__spirv::ImageChannelDataType::UnormInt16),
    unorm_int24         = static_cast<__details::channel_data_type>(__spirv::ImageChannelDataType::UnormInt24),
    unorm_short565      = static_cast<__details::channel_data_type>(__spirv::ImageChannelDataType::UnormShort565),
    unorm_short555      = static_cast<__details::channel_data_type>(__spirv::ImageChannelDataType::UnormShort555),
    unorm_short101010   = static_cast<__details::channel_data_type>(__spirv::ImageChannelDataType::UnormInt101010),
    unorm_short101010_2 = static_cast<__details::channel_data_type>(__spirv::ImageChannelDataType::UnormInt101010_2),
    sint8               = static_cast<__details::channel_data_type>(__spirv::ImageChannelDataType::SignedInt8),
    sint16              = static_cast<__details::channel_data_type>(__spirv::ImageChannelDataType::SignedInt16),
    sint32              = static_cast<__details::channel_data_type>(__spirv::ImageChannelDataType::SignedInt32),
    uint8               = static_cast<__details::channel_data_type>(__spirv::ImageChannelDataType::UnsignedInt8),
    uint16              = static_cast<__details::channel_data_type>(__spirv::ImageChannelDataType::UnsignedInt16),
    uint32              = static_cast<__details::channel_data_type>(__spirv::ImageChannelDataType::UnsignedInt32),
    float16             = static_cast<__details::channel_data_type>(__spirv::ImageChannelDataType::HalfFloat),
    float32             = static_cast<__details::channel_data_type>(__spirv::ImageChannelDataType::Float)
};

/// \brief Enumerable describing channel order of the image
///
enum class image_channel_order
{
    r             = static_cast<__details::channel_order_type>(__spirv::ImageChannelOrder::R),
    a             = static_cast<__details::channel_order_type>(__spirv::ImageChannelOrder::A),
    rg            = static_cast<__details::channel_order_type>(__spirv::ImageChannelOrder::RG),
    ra            = static_cast<__details::channel_order_type>(__spirv::ImageChannelOrder::RA),
    rgb           = static_cast<__details::channel_order_type>(__spirv::ImageChannelOrder::RGB),
    rgba          = static_cast<__details::channel_order_type>(__spirv::ImageChannelOrder::RGBA),
    bgra          = static_cast<__details::channel_order_type>(__spirv::ImageChannelOrder::BGRA),
    argb          = static_cast<__details::channel_order_type>(__spirv::ImageChannelOrder::ARGB),
    abgr          = static_cast<__details::channel_order_type>(__spirv::ImageChannelOrder::ABGR),
    intensity     = static_cast<__details::channel_order_type>(__spirv::ImageChannelOrder::Intensity),
    luminance     = static_cast<__details::channel_order_type>(__spirv::ImageChannelOrder::Luminance),
    rx            = static_cast<__details::channel_order_type>(__spirv::ImageChannelOrder::Rx),
    rgx           = static_cast<__details::channel_order_type>(__spirv::ImageChannelOrder::RGx),
    rgbx          = static_cast<__details::channel_order_type>(__spirv::ImageChannelOrder::RGBx),
    depth         = static_cast<__details::channel_order_type>(__spirv::ImageChannelOrder::Depth),
    depth_stencil = static_cast<__details::channel_order_type>(__spirv::ImageChannelOrder::DepthStencil),
    srgb          = static_cast<__details::channel_order_type>(__spirv::ImageChannelOrder::sRGB),
    srgbx         = static_cast<__details::channel_order_type>(__spirv::ImageChannelOrder::sRGBx),
    srgba         = static_cast<__details::channel_order_type>(__spirv::ImageChannelOrder::sRGBA),
    sbgra         = static_cast<__details::channel_order_type>(__spirv::ImageChannelOrder::sBGRA)
};


/// \brief Enumerable describing image access qualifier of the image
///
/// Depending on the image access qualifier image classes present different interfaces as follows:
/// image_access::read       -> read( )
/// image_access::write      -> write( )
/// image_access::read_write -> read( ), write( )
/// image_access::sample     -> read( ), sample( )
enum class image_access
{
    sample,
    read,
    write,
    read_write
};

/// \brief Enumerable describing image dimensionality
///
enum class image_dim
{
    image_1d     = static_cast<__details::dim_type>(__spirv::Dim::_1D),
    image_2d     = static_cast<__details::dim_type>(__spirv::Dim::_2D),
    image_3d     = static_cast<__details::dim_type>(__spirv::Dim::_3D),
    image_buffer = static_cast<__details::dim_type>(__spirv::Dim::Buffer)
};

}
