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

#include <__ocl_image_traits.h>
#include <__ocl_images_forward.h>

#define REGION 1

namespace cl
{


namespace __details

{

#if REGION | Non_multisampled_images

/// \brief Image 1-dimensional type - image1d
///
/// Apart from common image interface this type implements width( ) method.
/// It has dimension of 1.
template <class T, image_access Access>
struct __details::__image_helper<T, Access, image_dim::image_1d, false, false, false> : public __details::__image_base<T, Access, image_dim::image_1d, false, false, false>,
                                                public __details::__image_access_traits     <T, 1, Access, __details::__image_helper<T, Access, image_dim::image_1d, false, false, false>>,
                                                public __details::__image_width_trait       <T, __details::__image_helper<T, Access, image_dim::image_1d, false, false, false>>,
                                                public __details::__image_size_trait        <T, __details::__image_helper<T, Access, image_dim::image_1d, false, false, false>>
{ static_assert( __details::__is_image_pixel_type<T>::value, "Invalid pixel type" ); };

/// \brief Image 1-dimensional buffer type - image1d_buffer
///
/// Apart from common image interface this type implements width( ) method
/// It has dimension of 1
template<class T, image_access Access>
struct __details::__image_helper<T, Access, image_dim::image_buffer, false, false, false> : public __details::__image_base<T, Access, image_dim::image_buffer, false, false, false>,
                                                public __details::__image_access_traits     <T, 1, Access, __details::__image_helper<T, Access, image_dim::image_buffer, false, false, false>>,
                                                public __details::__image_width_trait       <T, __details::__image_helper<T, Access, image_dim::image_buffer, false, false, false>>,
                                                public __details::__image_size_trait        <T, __details::__image_helper<T, Access, image_dim::image_buffer, false, false, false>>
{ static_assert(__details::__is_image_pixel_type<T>::value, "Invalid pixel type");  };

/// \brief Array of 1-dimensional images type - image1d_array
///
/// Apart from common image interface this type implements width( ) and array_size( ) methods.
/// It has dimension of 2.
template <class T, image_access Access>
struct __details::__image_helper<T, Access, image_dim::image_1d, false, true, false> : public __details::__image_base<T, Access, image_dim::image_1d, false, true, false>,
                                                public __details::__image_access_traits     <T, 2, Access, __details::__image_helper<T, Access, image_dim::image_1d, false, true, false>>,
                                                public __details::__image_width_trait       <T, __details::__image_helper<T, Access, image_dim::image_1d, false, true, false>>,
                                                public __details::__image_array_size_trait  <T, __details::__image_helper<T, Access, image_dim::image_1d, false, true, false>>,
                                                public __details::__image_size_trait        <T, __details::__image_helper<T, Access, image_dim::image_1d, false, true, false>>
{ static_assert(  __details::__is_image_pixel_type<T>::value, "Invalid pixel type"  ); };

/// \brief Image 2-dimensional type - image2d
///
/// Apart from common image interface this type implements width( ) and height( ) methods.
/// It has dimension of 2.
template <class T, image_access Access>
struct __details::__image_helper<T, Access, image_dim::image_2d, false, false, false> : public __details::__image_base<T, Access, image_dim::image_2d, false, false, false>,
                                                public __details::__image_access_traits     <T, 2, Access, __details::__image_helper<T, Access, image_dim::image_2d, false, false, false>>,
                                                public __details::__image_width_trait       <T, __details::__image_helper<T, Access, image_dim::image_2d, false, false, false>>,
                                                public __details::__image_height_trait      <T, __details::__image_helper<T, Access, image_dim::image_2d, false, false, false>>,
                                                public __details::__image_size_trait        <T, __details::__image_helper<T, Access, image_dim::image_2d, false, false, false>>
{ static_assert(  __details::__is_image_pixel_type<T>::value, "Invalid pixel type"  ); };

/// \brief Array of 2-dimensional images type - image2d_array
///
/// Apart from common image interface this type implements width( ), height( ) and array_size( ) methods.
/// It has dimension of 3.
template<class T, image_access Access>
struct __details::__image_helper<T, Access, image_dim::image_2d, false, true, false> : public __details::__image_base<T, Access, image_dim::image_2d, false, true, false>,
                                                public __details::__image_access_traits     <T, 3, Access, __details::__image_helper<T, Access, image_dim::image_2d, false, true, false>>,
                                                public __details::__image_width_trait       <T, __details::__image_helper<T, Access, image_dim::image_2d, false, true, false>>,
                                                public __details::__image_height_trait      <T, __details::__image_helper<T, Access, image_dim::image_2d, false, true, false>>,
                                                public __details::__image_array_size_trait  <T, __details::__image_helper<T, Access, image_dim::image_2d, false, true, false>>,
                                                public __details::__image_size_trait        <T, __details::__image_helper<T, Access, image_dim::image_2d, false, true, false>>
{ static_assert( __details::__is_image_pixel_type<T>::value, "Invalid pixel type" ); };

/// \brief Depth image 2-dimensional type - image2d_depth
///
/// Apart from common image interface this type implements width( ) and height( ) methods.
/// It has dimension of 2.
template <class T, image_access Access>
struct __details::__image_helper<T, Access, image_dim::image_2d, true, false, false> : public __details::__image_base<T, Access, image_dim::image_2d, true, false, false>,
                                                public __details::__image_access_traits     <T, 2, Access, __details::__image_helper<T, Access, image_dim::image_2d, true, false, false>>,
                                                public __details::__image_width_trait       <T, __details::__image_helper<T, Access, image_dim::image_2d, true, false, false>>,
                                                public __details::__image_height_trait      <T, __details::__image_helper<T, Access, image_dim::image_2d, true, false, false>>,
                                                public __details::__image_size_trait        <T, __details::__image_helper<T, Access, image_dim::image_2d, true, false, false>>
{ static_assert( __details::__is_image_depth_type<T>::value, "Invalid pixel type" ); };

/// \brief Array of 2-dimensional depth images type - image2d_array_depth
///
/// Apart from common image interface this type implements width( ), height( ) and array_size( ) methods.
/// It has dimension of 3.
template <class T, image_access Access>
struct __details::__image_helper<T, Access, image_dim::image_2d, true, true, false> : public __details::__image_base<T, Access, image_dim::image_2d, true, true, false>,
                                                public __details::__image_access_traits     <T, 3, Access, __details::__image_helper<T, Access, image_dim::image_2d, true, true, false>>,
                                                public __details::__image_width_trait       <T, __details::__image_helper<T, Access, image_dim::image_2d, true, true, false>>,
                                                public __details::__image_height_trait      <T, __details::__image_helper<T, Access, image_dim::image_2d, true, true, false>>,
                                                public __details::__image_array_size_trait  <T, __details::__image_helper<T, Access, image_dim::image_2d, true, true, false>>,
                                                public __details::__image_size_trait        <T, __details::__image_helper<T, Access, image_dim::image_2d, true, true, false>>
{ static_assert( __details::__is_image_depth_type<T>::value, "Invalid pixel type" ); };

/// \brief Image 3-dimensional type - image3d
///
/// Apart from common image interface this type implements width( ), height( ) and depth( ) methods.
/// It has dimension of 3.
template <class T, image_access Access>
struct __details::__image_helper<T, Access, image_dim::image_3d, false, false, false> : public __details::__image_base<T, Access, image_dim::image_3d, false, false, false>,
                                                public __details::__image_access_traits     <T, 3, Access, __details::__image_helper<T, Access, image_dim::image_3d, false, false, false>>,
                                                public __details::__image_width_trait       <T, __details::__image_helper<T, Access, image_dim::image_3d, false, false, false>>,
                                                public __details::__image_height_trait      <T, __details::__image_helper<T, Access, image_dim::image_3d, false, false, false>>,
                                                public __details::__image_depth_trait       <T, __details::__image_helper<T, Access, image_dim::image_3d, false, false, false>>,
                                                public __details::__image_size_trait        <T, __details::__image_helper<T, Access, image_dim::image_3d, false, false, false>>
{ static_assert( __details::__is_image_pixel_type<T>::value, "Invalid pixel type" ); };

#endif

#if REGION | Multisampled_images

#if defined(cl_khr_gl_msaa_sharing) && defined(cl_khr_gl_depth_images)

/// \brief Image 2-dimensional multisampled type - image2d_ms
///
/// Apart from common image interface this type implements width( ) and height( ) methods.
/// It has dimension of 2.
template <class T, image_access Access>
struct __details::__image_helper<T, Access, image_dim::image_2d, false, false, true> : public __details::__image_base<T, Access, image_dim::image_2d, false, false, true>,
                                                public __details::__image_common_traits     <T, __details::__image_helper<T, Access, image_dim::image_2d, false, false, true>>,
                                                public __details::__image_width_trait       <T, __details::__image_helper<T, Access, image_dim::image_2d, false, false, true>>,
                                                public __details::__image_height_trait      <T, __details::__image_helper<T, Access, image_dim::image_2d, false, false, true>>,
                                                public __details::__image_size_trait        <T, __details::__image_helper<T, Access, image_dim::image_2d, false, false, true>>,
                                                public __details::__image_multisample_trait <T, __details::__image_helper<T, Access, image_dim::image_2d, false, false, true>>
{
    static_assert(__details::__is_ms_image_pixel_type<T>::value, "Invalid pixel type");
    static_assert(Access != image_access::sample, "Multisampled image cannot have image_access equal to sample");
};

/// \brief Array of 2-dimensional multisampled images type - image2d_array_ms
///
/// Apart from common image interface this type implements width( ), height( ) and array_size( ) methods.
/// It has dimension of 3.
template<class T, image_access Access>
struct __details::__image_helper<T, Access, image_dim::image_2d, false, true, true> : public __details::__image_base<T, Access, image_dim::image_2d, false, true, true>,
                                                public __details::__image_common_traits     <T, __details::__image_helper<T, Access, image_dim::image_2d, false, true, true>>,
                                                public __details::__image_width_trait       <T, __details::__image_helper<T, Access, image_dim::image_2d, false, true, true>>,
                                                public __details::__image_height_trait      <T, __details::__image_helper<T, Access, image_dim::image_2d, false, true, true>>,
                                                public __details::__image_size_trait        <T, __details::__image_helper<T, Access, image_dim::image_2d, false, true, true>>,
                                                public __details::__image_multisample_trait <T, __details::__image_helper<T, Access, image_dim::image_2d, false, true, true>>,
                                                public __details::__image_array_size_trait  <T, __details::__image_helper<T, Access, image_dim::image_2d, false, true, true>>
{
    static_assert(__details::__is_ms_image_pixel_type<T>::value, "Invalid pixel type");
    static_assert(Access != image_access::sample, "Multisampled image cannot have image_access equal to sample");
};

/// \brief Multisampled 2-dimensional depth image type - image2d_depth_ms
///
/// Apart from common image interface this type implements width( ) and height( ) methods.
/// It has dimension of 2.
template <class T, image_access Access>
struct __details::__image_helper<T, Access, image_dim::image_2d, true, false, true> : public __details::__image_base<T, Access, image_dim::image_2d, true, false, true>,
                                                public __details::__image_common_traits     <T, __details::__image_helper<T, Access, image_dim::image_2d, true, false, true>>,
                                                public __details::__image_width_trait       <T, __details::__image_helper<T, Access, image_dim::image_2d, true, false, true>>,
                                                public __details::__image_height_trait      <T, __details::__image_helper<T, Access, image_dim::image_2d, true, false, true>>,
                                                public __details::__image_size_trait        <T, __details::__image_helper<T, Access, image_dim::image_2d, true, false, true>>,
                                                public __details::__image_multisample_trait <T, __details::__image_helper<T, Access, image_dim::image_2d, true, false, true>>
{
    static_assert(__details::__is_ms_image_depth_type<T>::value, "Invalid pixel type");
    static_assert(Access != image_access::sample, "Multisampled image cannot have image_access equal to sample");
};

/// \brief Array of multisampled 2-dimensional depth images type - image2d_array_depth_ms
///
/// Apart from common image interface this type implements width( ), height( ) and array_size( ) methods.
/// It has dimension of 3.
template <class T, image_access Access>
struct __details::__image_helper<T, Access, image_dim::image_2d, true, true, true> : public __details::__image_base<T, Access, image_dim::image_2d, true, true, true>,
                                                public __details::__image_common_traits     <T, __details::__image_helper<T, Access, image_dim::image_2d, true, true, true>>,
                                                public __details::__image_width_trait       <T, __details::__image_helper<T, Access, image_dim::image_2d, true, true, true>>,
                                                public __details::__image_height_trait      <T, __details::__image_helper<T, Access, image_dim::image_2d, true, true, true>>,
                                                public __details::__image_size_trait        <T, __details::__image_helper<T, Access, image_dim::image_2d, true, true, true>>,
                                                public __details::__image_multisample_trait <T, __details::__image_helper<T, Access, image_dim::image_2d, true, true, true>>,
                                                public __details::__image_array_size_trait  <T, __details::__image_helper<T, Access, image_dim::image_2d, true, true, true>>
{
    static_assert(__details::__is_ms_image_depth_type<T>::value, "Invalid pixel type");
    static_assert(Access != image_access::sample, "Multisampled image cannot have image_access equal to sample");
};

#endif

#endif

}

}

#undef REGION