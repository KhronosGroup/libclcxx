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
#include <__ocl_images_forward.h>
#include <__ocl_spirv_image_opcodes.h>
#include <__ocl_image_traits_helpers.h>
#include <__ocl_vector_utility.h>
#include <__ocl_sampler.h>

namespace cl
{

namespace __details
{

/// \brief Helper structure making __image_base from OpTypeImage
///
template <typename T>
struct __make_image_base_helper;

template<class T, image_access Access, image_dim Dim, bool Depth, bool Array, bool MS>
struct __make_image_base_helper<__details::__image_helper<T, Access, Dim, Depth, Array, MS>>
{
    using base = __details::__image_base<T, Access, Dim, Depth, Array, MS>;
};

/// \brief Helper typedef for getting image base from image type
///
template <typename T>
using __make_image_base_t = typename __make_image_base_helper<T>::base;

/// \brief Image trait implementing sample interface via static polymorphism
///
template <typename _ElemType, typename _ImageType>
struct __image_sample_trait
{
private:
    using _base = __make_image_base_t<_ImageType>;
    using _integer_coord = typename _base::integer_coord;
    using _float_coord = typename _base::float_coord;
    using _ret_type = make_vector_t<_ElemType, 4>;

    static_assert( __is_image_sampler_coord_type<_float_coord>::value, "Invalid coordinate type" );

public:
    /// \brief Implementation of sample method for non-depth images
    ///
    /// @param s sampler that will be used for sampling
    /// @param coord integral coordinates from where value will be sampled
    /// @return result of sampling
    template<class CoordType, class Img = _ImageType>
    __ALWAYS_INLINE auto sample( const sampler& s, CoordType coord ) const __NOEXCEPT -> enable_if_t<is_integral<CoordType>::value && !__make_image_base_t<Img>::is_depth, _ElemType>
    {
        auto SampledImage = __spirv::__make_OpSampledImage_call<__global typename _ImageType::sampled_image_type *>( static_cast<const _ImageType*>( this )->_handle, s._handle );
        return __spirv::__make_OpImageSampleExplicitLod_call<_ret_type>( SampledImage, coord, static_cast<underlying_type_t<__spirv::ImageOperands>>(__spirv::ImageOperands::Lod), 0.0f );
    }

    /// \brief Implementation of sample method for depth images
    ///
    /// @param s sampler that will be used for sampling
    /// @param coord integral coordinates from where value will be sampled
    /// @return result of sampling
    template<class CoordType, class Img = _ImageType>
    __ALWAYS_INLINE auto sample( const sampler& s, CoordType coord ) const __NOEXCEPT -> enable_if_t<is_integral<CoordType>::value && __make_image_base_t<Img>::is_depth, _ElemType>
    {
        auto SampledImage = __spirv::__make_OpSampledImage_call<__global typename _ImageType::sampled_image_type *>( static_cast<const _ImageType*>( this )->_handle, s._handle );
        return get<0>( __spirv::__make_OpImageSampleExplicitLod_call<_ret_type>( SampledImage, coord, static_cast<underlying_type_t<__spirv::ImageOperands>>(__spirv::ImageOperands::Lod), 0.0f ) );
    }

    /// \brief Implementation of sample method for non-depth images
    ///
    /// @param s sampler that will be used for sampling
    /// @param coord floating point coordinates from where value will be sampled
    /// @return result of sampling
    template<class CoordType, class Img = _ImageType>
    __ALWAYS_INLINE auto sample( const sampler& s, CoordType coord ) const __NOEXCEPT -> enable_if_t<is_floating_point<CoordType>::value && !__make_image_base_t<Img>::is_depth, _ElemType>
    {
        auto SampledImage = __spirv::__make_OpSampledImage_call<__global typename _ImageType::sampled_image_type *>( static_cast<const _ImageType*>( this )->_handle, s._handle );
        return __spirv::__make_OpImageSampleExplicitLod_call<_ret_type>( SampledImage, coord, static_cast<underlying_type_t<__spirv::ImageOperands>>(__spirv::ImageOperands::Lod), 0.0f);
    }

    /// \brief Implementation of sample method for depth images
    ///
    /// @param s sampler that will be used for sampling
    /// @param coord floating point coordinates from where value will be sampled
    /// @return result of sampling
    template<class CoordType, class Img = _ImageType>
    __ALWAYS_INLINE auto sample( const sampler& s, CoordType coord ) const __NOEXCEPT -> enable_if_t<is_floating_point<CoordType>::value && __make_image_base_t<Img>::is_depth, _ElemType>
    {
        auto SampledImage = __spirv::__make_OpSampledImage_call<__global typename _ImageType::sampled_image_type *>( static_cast<const _ImageType*>( this )->_handle, s._handle );
        return get<0>( __spirv::__make_OpImageSampleExplicitLod_call<_ret_type>( SampledImage, coord, static_cast<underlying_type_t<__spirv::ImageOperands>>(__spirv::ImageOperands::Lod), 0.0f) );
    }

#ifdef cl_khr_mipmap_image
private:
    using _gradient_coord = typename _base::gradient_coord;

public:
    /// \brief Implementation of sample method for non-depth images
    ///
    /// @param s sampler that will be used for sampling
    /// @param coord integer coordinates from where value will be sampled
    /// @param lod level of detail for images having mipmaps
    /// @return result of sampling
    template<class Img = _ImageType>
    __ALWAYS_INLINE auto sample( const sampler& s, _float_coord coord, float lod ) const __NOEXCEPT -> enable_if_t<!__make_image_base_t<Img>::is_depth, _ElemType>
    {
        auto SampledImage = __spirv::__make_OpSampledImage_call<__global typename _ImageType::sampled_image_type *>( static_cast<const _ImageType*>( this )->_handle, s._handle );
        return __spirv::__make_OpImageSampleExplicitLod_call<_ret_type>( SampledImage, coord, static_cast<underlying_type_t<__spirv::ImageOperands>>(__spirv::ImageOperands::Lod), lod );
    }

    /// \brief Implementation of sample method for depth images
    ///
    /// @param s sampler that will be used for sampling
    /// @param coord integer coordinates from where value will be sampled
    /// @param lod level of detail for images having mipmaps
    /// @return result of sampling
    template<class Img = _ImageType>
    __ALWAYS_INLINE auto sample( const sampler& s, _float_coord coord, float lod ) const __NOEXCEPT -> enable_if_t<__make_image_base_t<Img>::is_depth, _ElemType>
    {
        auto SampledImage = __spirv::__make_OpSampledImage_call<__global typename _ImageType::sampled_image_type *>( static_cast<const _ImageType*>( this )->_handle, s._handle );
        return get<0>( __spirv::__make_OpImageSampleExplicitLod_call<_ret_type>( SampledImage, coord, static_cast<underlying_type_t<__spirv::ImageOperands>>(__spirv::ImageOperands::Lod), lod ) );
    }

    /// \brief Implementation of sample method using gradients to compute the lod and coordinate to do an element lookup in the mip-level specified by computed lod for depth images
    ///
    /// @param s sampler that will be used for sampling
    /// @param coord integer coordinates from where value will be sampled
    /// @param gradient_x x gradient
    /// @param gradient_y y gradient
    /// @return result of sampling
    template<class Img = _ImageType>
    __ALWAYS_INLINE auto sample( const sampler& s, _float_coord coord, _gradient_coord gradient_x, _gradient_coord gradient_y ) const __NOEXCEPT -> enable_if_t<!__make_image_base_t<Img>::is_depth, _ElemType>
    {
        auto SampledImage = __spirv::__make_OpSampledImage_call<__global typename _ImageType::sampled_image_type *>( static_cast<const _ImageType*>( this )->_handle, s._handle );
        return __spirv::__make_OpImageSampleExplicitLod_call<_ret_type>(SampledImage, coord, static_cast<underlying_type_t<__spirv::ImageOperands>>(__spirv::ImageOperands::Grad), gradient_x, gradient_y);
    }

    /// \brief Implementation of sample method using gradients to compute the lod and coordinate to do an element lookup in the mip-level specified by computed lod for non-depth images
    ///
    /// @param s sampler that will be used for sampling
    /// @param coord integer coordinates from where value will be sampled
    /// @param gradient_x x gradient
    /// @param gradient_y y gradient
    /// @return result of sampling
    template<class Img = _ImageType>
    __ALWAYS_INLINE auto sample( const sampler& s, _float_coord coord, _gradient_coord gradient_x, _gradient_coord gradient_y ) const __NOEXCEPT -> enable_if_t<__make_image_base_t<Img>::is_depth, _ElemType>
    {
        auto SampledImage = __spirv::__make_OpSampledImage_call<__global typename _ImageType::sampled_image_type *>( static_cast<const _ImageType*>( this )->_handle, s._handle );
        return get<0>( __spirv::__make_OpImageSampleExplicitLod_call<_ret_type>(SampledImage, coord, static_cast<underlying_type_t<__spirv::ImageOperands>>(__spirv::ImageOperands::Grad), gradient_x, gradient_y) );
    }
#endif
};

/// \brief Image trait implementing read interface via static polymorphism
///
template <typename _ElemType, typename _ImageType>
struct __image_read_trait
{
private:
    using _base = __make_image_base_t<_ImageType>;
    using _integer_coord = typename _base::integer_coord;

    static_assert( __is_image_read_coord_type<_integer_coord>::value, "Invalid coordinate type" );

public:
    /// \brief Implementation of read method
    ///
    /// @param coord coordinates from where value will be read
    /// @return result of samplerless read
    __ALWAYS_INLINE _ElemType read( _integer_coord coord ) const __NOEXCEPT
    {
        return __spirv::__make_OpImageRead_call<_ElemType>(static_cast<const _ImageType*>( this )->_handle, coord );
    }
};

/// \brief Image trait implementing write interface via static polymorphism
///
template <typename _ElemType, typename _Coord, typename _ImageType>
struct __image_write_trait
{
    static_assert( __is_image_write_coord_type<_Coord>::value, "Invalid coordinate type" );

    /// \brief Implementation of write method
    ///
    /// @param coord coordinates from where value will be read
    /// @param color value to which pixel pointed by coords will be set
    __ALWAYS_INLINE void write( _Coord coord, _ElemType color ) __NOEXCEPT
    {
        __spirv::__make_OpImageWrite_call<void>( static_cast<_ImageType*>( this )->_handle, coord, color );
    }

#if cl_khr_mipmap_image_writes
    /// \brief Implementation of write method with lod
    ///
    /// @param coord coordinates from where value will be read
    /// @param color value to which pixel pointed by coords will be set
	/// @param lod level of detail for images having mipmaps
    __ALWAYS_INLINE void write( _Coord coord, _ElemType color, int lod ) __NOEXCEPT
    {
        __spirv::__make_OpImageWrite_call<void>( static_cast<_ImageType*>( this )->_handle, coord, color, static_cast<underlying_type_t<__spirv::ImageOperands>>(__spirv::ImageOperands::Lod), lod );
    }
#endif
};

/// \brief Helper class for width trait for vector OpImageQuerySize return type
///
template <typename _ElemType, typename _ImageType>
struct __image_width_trait
{
private:
    using _base = __make_image_base_t<_ImageType>;
    using _integer_coord = typename _base::integer_coord;

public:
    /// \brief Implementation of width method
    ///
    /// @return width of image in pixels
    __ALWAYS_INLINE int width( ) const __NOEXCEPT
    {
        return get<0>( __spirv::__make_OpImageQuerySize_call<_integer_coord>( static_cast<const _ImageType*>( this )->_handle ));
    }

#if cl_khr_mipmap_image || cl_khr_mipmap_image_writes
    /// \brief Implementation of width method for mipmap level for a given level of detail
    ///
    /// @param lod level of detail for images having mipmaps
    /// @return width of image in pixels
    template<class Img = _ImageType, class = enable_if_t<!__make_image_base_t<Img>::is_ms, int>>
    __ALWAYS_INLINE int width( int lod ) const __NOEXCEPT
    {
        return get<0>( __spirv::__make_OpImageQuerySizeLod_call<_integer_coord>( static_cast<const _ImageType*>( this )->_handle, lod ));
    }
#endif
};

/// \brief Image trait implementing height interface via static polymorphism
///
template <typename _ElemType, typename _ImageType>
struct __image_height_trait
{
private:
    using _base = __make_image_base_t<_ImageType>;

public:
    /// \brief Implementation of height method
    ///
    /// @return height of image in pixels
    __ALWAYS_INLINE int height( ) const __NOEXCEPT
    {
        return get<1>( __spirv::__make_OpImageQuerySize_call<typename _ImageType::integer_coord>( static_cast<const _ImageType*>( this )->_handle ));
    }

#if cl_khr_mipmap_image || cl_khr_mipmap_image_writes
    /// \brief Implementation of height method for mipmap level for a given level of detail
    ///
    /// @param lod level of detail for images having mipmaps
    /// @return height of image in pixels
    template<class Img = _ImageType, class = enable_if_t<!__make_image_base_t<Img>::is_ms, int>>
    __ALWAYS_INLINE int height( int lod ) const __NOEXCEPT
    {
        return get<1>( __spirv::__make_OpImageQuerySizeLod_call<typename _ImageType::integer_coord>( static_cast<const _ImageType*>( this )->_handle, lod ));
    }
#endif
};

/// \brief Image trait implementing depth interface via static polymorphism
///
template <typename T, typename _ImageType>
struct __image_depth_trait
{
private:
    using _base = __make_image_base_t<_ImageType>;

public:
    /// \brief Implementation of depth method
    ///
    /// @return depth of image in pixels
    __ALWAYS_INLINE int depth( ) const __NOEXCEPT
    {
        return get<2>( __spirv::__make_OpImageQuerySize_call<typename _ImageType::integer_coord>( static_cast<const _ImageType*>( this )->_handle ));
    }

#if cl_khr_mipmap_image || cl_khr_mipmap_image_writes
    /// \brief Implementation of depth method for mipmap level for a given level of detail
    ///
    /// @param lod level of detail for images having mipmaps
    /// @return depth of image in pixels
    template<class Img = _ImageType, class = enable_if_t<!__make_image_base_t<Img>::is_ms, int>>
    __ALWAYS_INLINE int depth( int lod ) const __NOEXCEPT
    {
        return get<2>( __spirv::__make_OpImageQuerySizeLod_call<typename _ImageType::integer_coord>( static_cast<const _ImageType*>( this )->_handle, lod ));
    }
#endif
};

/// \brief Image trait implementing array_size interface via static polymorphism
///
template <typename _ElemType, typename _ImageType>
struct __image_array_size_trait
{
    /// \brief Implementation of array_size method
    ///
    /// @return size of the image array
    __ALWAYS_INLINE int array_size( ) const __NOEXCEPT
    {
        return get<_ImageType::image_size - 1>( __spirv::__make_OpImageQuerySize_call<typename _ImageType::integer_coord>( static_cast<const _ImageType*>( this )->_handle ));
    }

#ifdef cl_khr_mipmap_image
    /// \brief Implementation of array_size method taking level of detail as a parameter
    ///
    /// @param lod level of detail
    /// @return size of the image array specified by lod
    __ALWAYS_INLINE int array_size( int lod ) const __NOEXCEPT
    {
        return get<_ImageType::image_size - 1>( __spirv::__make_OpImageQuerySizeLod_call<typename _ImageType::integer_coord>( static_cast<const _ImageType*>( this )->_handle, lod ));
    }
#endif
};

/// \brief Image trait implementing common interface shared by all images via static polymorphism
///
/// That common interface consists of miplevels, channel_data_type, size and channel_order functions.
template <typename _ElemType, typename _ImageType>
struct __image_common_traits
{

#if cl_khr_mipmap_image || cl_khr_mipmap_image_writes
    /// \brief Implementation of miplevels method
    ///
    /// @return number of mipmaps in the image
    //todo : enable if ( only nonmultisampled )
    template<typename Img = _ImageType>
    __ALWAYS_INLINE auto miplevels( ) const __NOEXCEPT -> enable_if_t<!__make_image_base_t<Img>::is_ms, int>
    {
        return __spirv::__make_OpImageQueryLevels_call<int>( static_cast<const _ImageType*>( this )->_handle );
    }
#endif

    /// \brief Implementation of channel_data_type method
    ///
    /// @return enum representing channel data type of image
    __ALWAYS_INLINE image_channel_type data_type( ) const __NOEXCEPT
    {
        return __spirv::__make_OpImageQueryFormat_call<image_channel_type>( static_cast<const _ImageType*>( this )->_handle );
    }

    /// \brief Implementation of channel_order method
    ///
    /// @return enum representing channel order of image
    __ALWAYS_INLINE image_channel_order order( ) const __NOEXCEPT
    {
        return __spirv::__make_OpImageQueryOrder_call<image_channel_order>( static_cast<const _ImageType*>( this )->_handle );
    }

#if defined( cl_khr_gl_msaa_sharing ) && defined( cl_khr_gl_depth_images )

    /// \brief Implementation of num_samples method, returning the number of samples in the 2D multisampled image
    ///
    /// @return number of samples in the image
    template<class Img = _ImageType, class = enable_if_t<__make_image_base_t<Img>::is_ms, int>>
    __ALWAYS_INLINE int num_samples( ) const __NOEXCEPT
    {
        return __spirv::__make_OpImageQuerySamples_call<int>( static_cast<const _ImageType*>( this )->_handle );
    }
#endif
};

/// \brief Image trait implementing array_size interface via static polymorphism
///
template <typename _ElemType, typename _ImageType>
struct __image_size_trait
{
private:
    using _base = __make_image_base_t<_ImageType>;
    using _Ret = typename _base::integer_coord;

public:
    /// \brief Implementation of size method
    ///
    /// @return appropriately sized vector, or scalar for 1 dimensional images, containing all image dimensions followed by array size.
    __ALWAYS_INLINE _Ret size( ) const __NOEXCEPT
    {
        return __spirv::__make_OpImageQuerySize_call<_Ret>( static_cast<const _ImageType*>( this )->_handle );
    }
};

#if defined( cl_khr_gl_msaa_sharing ) && defined( cl_khr_gl_depth_images )
/// \brief Image trait implementing all methods for multisampled image
///
template <typename _ElemType, typename _ImageType>
struct __image_multisample_trait
{
    using _base = __make_image_base_t<_ImageType>;
    using _integer_coord = typename _base::integer_coord;

    /// \brief Implementation of read method for multisampled image
    ///
    /// @param coord coordinates from where element will be looked up
    /// @param sample sample used to do element lookup
    /// @return element loo
    __ALWAYS_INLINE _ElemType read( _integer_coord coord, int sample ) const __NOEXCEPT
    {
        return __spirv::__make_OpImageRead_call<_ElemType>( static_cast<const _ImageType*>( this )->_handle, coord, static_cast<underlying_type_t<__spirv::ImageOperands>>(__spirv::ImageOperands::Sample), sample );
    }
};
#endif

/// \brief Image trait containing proper access interface specified by image_access parameter.
///
/// This also contains image common traits. Access interface is defined as follows:
/// image_access::read       -> read(   )
/// image_access::write      -> write(   )
/// image_access::read_write -> read( ), write( )
/// image_access::sample     -> read( ), sample( )
template <typename _ElemType, size_t _Size, image_access _Access, typename _ImageType>
struct __image_access_traits { static_assert( __always_false<__image_access_traits>::value, "Invalid image_access value" ); };

/// \brief Image trait containing proper access interface specified by image_access parameter
///
template <typename _ElemType, size_t _Size, typename _ImageType>
struct __image_access_traits<_ElemType, _Size, image_access::read, _ImageType> :
    public __image_read_trait<_ElemType, _ImageType>,
    public __image_common_traits<_ElemType, _ImageType> { };

/// \brief Image trait containing proper access interface specified by image_access parameter.
///
template <typename _ElemType, size_t _Size, typename _ImageType>
struct __image_access_traits<_ElemType, _Size, image_access::write, _ImageType> :
    public __image_write_trait<_ElemType, typename __image_sample_coordinates<_Size>::integral, _ImageType>,
    public __image_common_traits<_ElemType, _ImageType> { };

/// \brief Image trait containing proper access interface specified by image_access parameter.
///
template <typename _ElemType, size_t _Size, typename _ImageType>
struct __image_access_traits<_ElemType, _Size, image_access::read_write, _ImageType> :
    public __image_read_trait<_ElemType, _ImageType>,
    public __image_write_trait<_ElemType, typename __image_sample_coordinates<_Size>::integral, _ImageType>,
    public __image_common_traits<_ElemType, _ImageType> { };

/// \brief Image trait containing proper access interface specified by image_access parameter.
///
template <typename _ElemType, size_t _Size, typename _ImageType>
struct __image_access_traits<_ElemType, _Size, image_access::sample, _ImageType> :
    public __image_sample_trait<_ElemType, _ImageType>,
    public __image_read_trait<_ElemType, _ImageType>,
    public __image_common_traits<_ElemType, _ImageType> { };

}

}