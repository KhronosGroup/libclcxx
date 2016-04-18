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
#include <__ocl_image_enums.h>
#include <__ocl_spirv_image_opcodes.h>
#include <__ocl_spirv_access_opcodes.h>
#include <__ocl_marker_type.h>

namespace cl
{

    /// \brief Image trait containing image dimension
    ///
    /// This specialization is for image_1d, image_2d, image_3d. All other Dim values should be specialized.
    template<image_dim Dim>
    struct image_dim_num
    {
        static constexpr size_t value = static_cast<underlying_type_t<image_dim>>( Dim ) + 1;
       //+1 because SPIRV maps Dims as follows : 1D to 0, 2D to 1 and 3D to 2 and we want to get 1 from 1D, 2 from 2D and 3 from 3D
    };

    /// \brief Image trait containing image dimension
    ///
    /// This specialization is for image_buffer, which dimension is equal to 1
    template<>
    struct image_dim_num<image_dim::image_buffer>
    {
        static constexpr size_t value = 1;
    };

namespace __details
{
    template<class T, image_access Access, image_dim Dim, bool Depth, bool Array, bool MS>
    struct __image_helper;

    /// \brief Image access trait containing SPIR-V access qualifier
    ///
    /// This specialization is for read and sample accesses
    template<image_access Acc>
    struct image_access_qualifier
    {
        static constexpr __spirv::AccessQualifier value = __spirv::AccessQualifier::Read;
    };

    /// \brief Image access trait containing SPIR-V access qualifier
    ///
    /// This specialization is for write accesses
    template<>
    struct image_access_qualifier<image_access::write>
    {
        static constexpr __spirv::AccessQualifier value = __spirv::AccessQualifier::Write;
    };

    /// \brief Image access trait containing SPIR-V access qualifier
    ///
    /// This specialization is for read-write accesses
    template<>
    struct image_access_qualifier<image_access::read_write>
    {
        static constexpr __spirv::AccessQualifier value = __spirv::AccessQualifier::ReadWrite;
    };

    /// \brief Helper type trait for checking image_access equality
    ///
    template <image_access _A, image_access _B>
    struct __is_same_image_access
    {
        static constexpr bool value = ( _A == _B );
    };

    /// \brief Helper class containing all basic members and typedefs
    ///
    template<class T, image_access Access, image_dim D, bool Depth, bool Array, bool MS = false>
    struct __image_base : marker_type
    {
    private:
        __global __spirv::OpTypeImage<vector_element_t<T>, static_cast<__spirv::Dim>(D), Depth, Array, MS, 0, __spirv::ImageFormat::Unknown, image_access_qualifier<Access>::value>* _handle;

    public:
        static constexpr image_dim dimension = D;
        static constexpr size_t dimension_num = image_dim_num<D>::value;
        static constexpr size_t image_size = dimension_num + ( Array ? 1 : 0 );
        static constexpr image_access access = Access;
        static constexpr bool is_array = Array;
        static constexpr bool is_depth = Depth;
        static constexpr bool is_ms = MS;

        using element_type = T;
        using integer_coord = make_vector_t<int, image_size>;
        using float_coord = make_vector_t<float, image_size>;

#ifdef cl_khr_mipmap_image
        using gradient_coord = make_vector_t<float, dimension_num>;
#endif

        using sampled_image_type = __spirv::OpTypeSampledImage<vector_element_t<T>, static_cast<__spirv::Dim>(D), Depth, Array, MS, 0, __spirv::ImageFormat::Unknown, image_access_qualifier<Access>::value>;

        /// \brief Structure wrapping pixel and providing similar behaviour.
        ///
        /// Contains image reference and pixels coordinates.
        struct pixel
        {
        private:
            using image_type = __details::__image_helper<T, Access, D, Depth, Array, MS>;
            using base_type = __image_base<T, Access, D, Depth, Array, MS>;
            base_type &image_reference;
            integer_coord &coord;

        public:
            pixel( base_type& _image_reference, integer_coord& _coord ) : image_reference{ _image_reference }, coord{ _coord } { }

            template<class BaseType = base_type, class = enable_if_t<!BaseType::is_ms &&
                !__is_same_image_access<access, image_access::write>::value, void>>
            operator T( ) const __NOEXCEPT { return static_cast<image_type&>( image_reference ).read( coord ); }

            template<class BaseType = base_type, class = enable_if_t<!BaseType::is_ms &&
                ( __is_same_image_access<access, image_access::write>::value || __is_same_image_access<access, image_access::read_write>::value ), void >>
            pixel &operator=( T color ) __NOEXCEPT{ static_cast<image_type&>( image_reference ).write( coord, color ); return *this; }
        };

        pixel operator[]( integer_coord coord ) __NOEXCEPT{ return pixel( *this, coord ); }
        pixel operator[]( integer_coord coord ) const __NOEXCEPT{ return pixel( *this, coord ); }

        template <typename _ElemType, typename _ImageType>
        friend struct __image_sample_trait;
        template <typename _ElemType, typename _ImageType>
        friend struct __image_read_trait;
        template <typename _ElemType, typename _Coord, typename _ImageType>
        friend struct __image_write_trait;
        template <typename _ElemType, typename _ImageType>
        friend struct __image_width_trait;
        template <typename _ElemType, typename _ImageType>
        friend struct __image_height_trait;
        template <typename _ElemType, typename _ImageType>
        friend struct __image_depth_trait;
        template <typename _ElemType, typename _ImageType>
        friend struct __image_array_size_trait;
        template <typename _ElemType, typename _ImageType>
        friend struct __image_common_traits;
        template <typename _ElemType, typename _ImageType>
        friend struct __image_size_trait;
        template <typename _ElemType, typename _ImageType>
        friend struct __image_multisample_trait;
    };
}


template<class T, image_access Access = image_access::read>
using image1d = __details::__image_helper<T, Access, image_dim::image_1d, false, false, false>;

template<class T, image_access Access = image_access::read>
using image1d_buffer = __details::__image_helper<T, Access, image_dim::image_buffer, false, false, false>;

template<class T, image_access Access = image_access::read>
using image1d_array = __details::__image_helper<T, Access, image_dim::image_1d, false, true, false>;

template<class T, image_access Access = image_access::read>
using image2d = __details::__image_helper<T, Access, image_dim::image_2d, false, false, false>;

template<class T, image_access Access = image_access::read>
using image2d_depth = __details::__image_helper<T, Access, image_dim::image_2d, true, false, false>;

template<class T, image_access Access = image_access::read>
using image2d_array = __details::__image_helper<T, Access, image_dim::image_2d, false, true, false>;

template<class T, image_access Access = image_access::read>
using image3d = __details::__image_helper<T, Access, image_dim::image_3d, false, false, false>;

template<class T, image_access Access = image_access::read>
using image2d_array_depth = __details::__image_helper<T, Access, image_dim::image_2d, true, true, false>;

#if defined( cl_khr_gl_msaa_sharing ) && defined( cl_khr_gl_depth_images )
template <class T, image_access Access = image_access::read>
using image2d_ms = __details::__image_helper<T, Access, image_dim::image_2d, false, false, true>;

template <class T, image_access Access = image_access::read>
using image2d_array_ms = __details::__image_helper<T, Access, image_dim::image_2d, false, true, true>;

template <class T, image_access Access = image_access::read>
using image2d_depth_ms = __details::__image_helper<T, Access, image_dim::image_2d, true, false, true>;

template <class T, image_access Access = image_access::read>
using image2d_array_depth_ms = __details::__image_helper<T, Access, image_dim::image_2d, true, true, true>;
#endif


}
