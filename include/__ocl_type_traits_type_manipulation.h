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

#include <__ocl_type_traits_type_properties.h>
#include <__ocl_type_traits_type_relations.h>
#include <__ocl_type_traits_cv_ref_ptr.h>
#include <__ocl_type_traits_type_generators.h>
#include <__ocl_type_traits_vectors.h>

namespace cl
{

template <class T> struct make_signed;
template <class T> struct make_unsigned;

template <class T>
using make_signed_t = typename make_signed<T>::type;
template <class T>
using make_unsigned_t = typename make_unsigned<T>::type;

namespace __details
{

/// \brief Trait helper that for given integral type defines its signed and unsigned versions
///
template <class T, bool = is_vector_type<T>::value>
struct __change_sign_helper
{
    static_assert((is_enum<T>::value || is_integral<T>::value) && !is_same<T, bool>::value,
        "Make signed/unsigned can only be used with integral types that are not bool");
    typedef conditional_t<__is_one_of<T, signed char, unsigned char>::value, signed char,
            conditional_t<__is_one_of<T, short, unsigned short>::value, short,
            conditional_t<__is_one_of<T, int, unsigned int>::value, int,
            conditional_t<__is_one_of<T, long, unsigned long>::value, long,
            conditional_t<__is_one_of<T, long long, unsigned long long>::value, long long,
            conditional_t<sizeof(T) == sizeof(signed char), signed char,
            conditional_t<sizeof(T) == sizeof(short), short,
            conditional_t<sizeof(T) == sizeof(int), int,
            conditional_t<sizeof(T) == sizeof(long), long, long long>>>>>>>>> __signed_type;

    typedef conditional_t<__is_one_of<T, signed char, unsigned char>::value, unsigned char,
            conditional_t<__is_one_of<T, short, unsigned short>::value, unsigned short,
            conditional_t<__is_one_of<T, int, unsigned int>::value, unsigned int,
            conditional_t<__is_one_of<T, long, unsigned long>::value, unsigned long,
            conditional_t<__is_one_of<T, long long, unsigned long long>::value, unsigned long long,
            conditional_t<sizeof(T) == sizeof(signed char), unsigned char,
            conditional_t<sizeof(T) == sizeof(short), unsigned short,
            conditional_t<sizeof(T) == sizeof(int), unsigned int,
            conditional_t<sizeof(T) == sizeof(long), unsigned long, unsigned long long>>>>>>>>> __unsigned_type;
};

template <class T>
struct __change_sign_helper<T, true>
{
    typedef make_vector_t<
                typename __change_sign_helper<remove_attrs_t<vector_element_t<T>>, false>::__signed_type,
                vector_size<T>::value
            > __signed_type;

    typedef make_vector_t<
                typename __change_sign_helper<remove_attrs_t<vector_element_t<T>>, false>::__unsigned_type,
                vector_size<T>::value
            > __unsigned_type;
};

}

/// \brief Type trait providing signed version of given integral type
///
template <class T>
struct make_signed { typedef typename __details::__copy_attrs_helper<T, typename __details::__change_sign_helper<T>::__signed_type>::type type; };

/// \brief Type trait providing unsigned version of given integral type
///
template <class T>
struct make_unsigned { typedef typename __details::__copy_attrs_helper<T, typename __details::__change_sign_helper<T>::__unsigned_type>::type type; };

namespace __details
{

/// \brief trait similar to __make_(un)signed but instead of changing type's sign converts it to smallest type which met condition: sizeof(newtype) > sizeof(T). Works only for integral types.
///  By default handles non-vector case. Used by 'upsample' function
///
template <typename T, bool = is_vector_type<T>::value>
struct __make_upper
{
    static_assert(__is_one_of<T, char, uchar, short, ushort, int, uint>::value, "Invalid type");
    typedef
        conditional_t<is_same<T,char>::value, short,
        conditional_t<is_same<T,uchar>::value, ushort,
        conditional_t<is_same<T,short>::value, int,
        conditional_t<is_same<T,ushort>::value, uint,
        conditional_t<is_same<T,int>::value, long,
        conditional_t<is_same<T,uint>::value, ulong, T
        >>>>>> type;
};

template <typename T>
using __make_upper_t = typename __make_upper<T>::type;

/// \brief Handles vector case: fetches channel's type, converts it and constructs new vector type
///
template <typename T>
struct __make_upper<T,true>
{
    typedef make_vector_t<
            __make_upper_t<remove_attrs_t<vector_element_t<T>>>,
            vector_size<T>::value
        > type;
};

}

}