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
#include <opencl_type_traits>
#include <__ocl_type_traits_vectors.h>
#include <__ocl_iterator.h>

namespace cl
{

namespace __details
{

/// \brief Helper that allows indexing vector channels with compile time size_t indexes.
///
template <class Vec, size_t Size>
struct __vec_index_helper;

#define VEC_INDEX( OFFSET, CHANNEL ) \
    template <class Vec> \
    struct __vec_index_helper<Vec, OFFSET> \
    { \
        __ALWAYS_INLINE static constexpr auto get( const Vec& vector ) __NOEXCEPT { return vector. CHANNEL; } \
        __ALWAYS_INLINE static constexpr void set( Vec& vector, remove_attrs_t<vector_element_t<Vec>> value ) __NOEXCEPT { vector. CHANNEL = value; } \
    };

VEC_INDEX( 0, s0 )
VEC_INDEX( 1, s1 )
VEC_INDEX( 2, s2 )
VEC_INDEX( 3, s3 )
VEC_INDEX( 4, s4 )
VEC_INDEX( 5, s5 )
VEC_INDEX( 6, s6 )
VEC_INDEX( 7, s7 )
VEC_INDEX( 8, s8 )
VEC_INDEX( 9, s9 )
VEC_INDEX( 10, sa )
VEC_INDEX( 11, sb )
VEC_INDEX( 12, sc )
VEC_INDEX( 13, sd )
VEC_INDEX( 14, se )
VEC_INDEX( 15, sf )

#undef VEC_INDEX

}

/// \brief Function that returns value of vector channel numbered Channel
///
/// Specialization for vectors
template <size_t Channel, class Vec, class = enable_if_t<is_vector_type<Vec>::value, void>>
__ALWAYS_INLINE constexpr remove_attrs_t<vector_element_t<Vec>> get( const Vec& vector ) __NOEXCEPT { return __details::__vec_index_helper<Vec, Channel>::get( vector ); }

/// \brief Function that returns value of vector channel numbered Channel
///
/// Specialization for scalars
template<size_t Channel, class Vec, class = enable_if_t<!is_vector_type<Vec>::value && is_vector_channel_type<Vec>::value, void>>
__ALWAYS_INLINE constexpr remove_attrs_t<Vec> get(const Vec& vector) __NOEXCEPT{  static_assert(Channel == 0, "Channel should be equal to zero when using get<>() on scalar"); return vector; }

/// \brief Function that sets value to vector channel numbered Channel
///
template <size_t Channel, class Vec, class = enable_if_t<is_vector_type<Vec>::value, void>>
__ALWAYS_INLINE constexpr void set( Vec & vector, remove_attrs_t<vector_element_t<Vec>> value ) __NOEXCEPT { __details::__vec_index_helper<Vec, Channel>::set( vector, value ); }

namespace __details
{

#define IDX_G( CHANNEL ) case CHANNEL: return cl::get<CHANNEL>( vector );
#define IDX_S( CHANNEL ) case CHANNEL: cl::set<CHANNEL>( vector, value ); return;

/// \brief Helper class used for indexing compile time values with runtime specified indexes
///
/// Generates switch statements like that case n: return get<n>( vec ); that way we can use runtime
/// provided values to index over channels that are specified at compile time this method can also be
/// used in other contexts ( such as runtime selection of images or emulation of function pointers )
template <class T, size_t Size = vector_size<T>::value>
struct __index_helper;

/// \brief Helper class used for indexing compile time values with runtime specified indexes
///
/// Generates switch statements like that case n: return get<n>( vec ); that way we can use runtime
/// provided values to index over channels that are specified at compile time this method can also be
/// used in other contexts ( such as runtime selection of images or emulation of function pointers )
template <class T>
struct __index_helper<T, 16>
{
    __ALWAYS_INLINE static constexpr auto get( T& vector, size_t channel ) __NOEXCEPT
    {
        switch ( channel )
        {
        IDX_G(0) IDX_G(1) IDX_G(2) IDX_G(3) IDX_G(4) IDX_G(5) IDX_G(6) IDX_G(7) IDX_G(8) IDX_G(9) IDX_G(10) IDX_G(11) IDX_G(12) IDX_G(13) IDX_G(14) IDX_G(15)
        default: return vector_element_t<T>( );
        }
    }

    __ALWAYS_INLINE static constexpr void set( T& vector, size_t channel, remove_attrs_t<vector_element_t<T>> value ) __NOEXCEPT
    {
        switch ( channel )
        {
        IDX_S(0) IDX_S(1) IDX_S(2) IDX_S(3) IDX_S(4) IDX_S(5) IDX_S(6) IDX_S(7) IDX_S(8) IDX_S(9) IDX_S(10) IDX_S(11) IDX_S(12) IDX_S(13) IDX_S(14) IDX_S(15)
        default: return;
        }
    }
};

/// \brief Helper class used for indexing compile time values with runtime specified indexes
///
/// Generates switch statements like that case n: return get<n>( vector ); that way we can use runtime
/// provided values to index over channels that are specified at compile time this method can also be
/// used in other contexts ( such as runtime selection of images or emulation of function pointers )
template <class T>
struct __index_helper<T, 8>
{
    __ALWAYS_INLINE static constexpr auto get( T& vector, size_t channel ) __NOEXCEPT
    {
        switch ( channel )
        {
        IDX_G(0) IDX_G(1) IDX_G(2) IDX_G(3) IDX_G(4) IDX_G(5) IDX_G(6) IDX_G(7)
        default: return vector_element_t<T>( );
        }
    }

    __ALWAYS_INLINE static constexpr void set( T& vector, size_t channel, remove_attrs_t<vector_element_t<T>> value ) __NOEXCEPT
    {
        switch ( channel )
        {
        IDX_S(0) IDX_S(1) IDX_S(2) IDX_S(3) IDX_S(4) IDX_S(5) IDX_S(6) IDX_S(7)
        default: return;
        }
    }
};

/// \brief Helper class used for indexing compile time values with runtime specified indexes
///
/// Generates switch statements like that case n: return get<n>( vector ); that way we can use runtime
/// provided values to index over channels that are specified at compile time this method can also be
/// used in other contexts ( such as runtime selection of images or emulation of function pointers )
template <class T>
struct __index_helper<T, 4>
{
    __ALWAYS_INLINE static constexpr auto get( T& vector, size_t channel ) __NOEXCEPT
    {
        switch ( channel )
        {
        IDX_G(0) IDX_G(1) IDX_G(2) IDX_G(3)
        default: return vector_element_t<T>( );
        }
    }

    __ALWAYS_INLINE static constexpr void set( T& vector, size_t channel, remove_attrs_t<vector_element_t<T>> value ) __NOEXCEPT
    {
        switch ( channel )
        {
        IDX_S(0) IDX_S(1) IDX_S(2) IDX_S(3)
        default: return;
        }
    }
};

/// \brief Helper class used for indexing compile time values with runtime specified indexes
///
/// Generates switch statements like that case n: return get<n>( vector ); that way we can use runtime
/// provided values to index over channels that are specified at compile time this method can also be
/// used in other contexts ( such as runtime selection of images or emulation of function pointers )
template <class T>
struct __index_helper<T, 3>
{
    __ALWAYS_INLINE static constexpr auto get( T& vector, size_t channel ) __NOEXCEPT
    {
        switch ( channel )
        {
        IDX_G( 0 ) IDX_G( 1 ) IDX_G( 2 )
        default: return vector_element_t<T>( );
        }
    }

    __ALWAYS_INLINE static constexpr void set( T& vector, size_t channel, remove_attrs_t<vector_element_t<T>> value ) __NOEXCEPT
    {
        switch ( channel )
        {
        IDX_S(0) IDX_S(1) IDX_S(2)
        default: return;
        }
    }
};

/// \brief Helper class used for indexing compile time values with runtime specified indexes
///
/// Generates switch statements like that case n: return get<n>( vector ); that way we can use runtime
/// provided values to index over channels that are specified at compile time this method can also be
/// used in other contexts ( such as runtime selection of images or emulation of function pointers )
template <class T>
struct __index_helper<T, 2>
{
    __ALWAYS_INLINE static constexpr auto get( T& vector, size_t channel ) __NOEXCEPT
    {
        switch ( channel )
        {
        IDX_G(0) IDX_G(1)
        default: return vector_element_t<T>( );
        }
    }

    __ALWAYS_INLINE static constexpr void set( T& vector, size_t channel, remove_attrs_t<vector_element_t<T>> value ) __NOEXCEPT
    {
        switch ( channel )
        {
        IDX_S(0) IDX_S(1)
        default: return;
        }
    }
};

#undef IDX_G
#undef IDX_S

enum __vector_type : size_t { integral, floating_point, boolean };

/// \brief Helper evaluating given vector type T
///
template <class T, class U = remove_attrs_t<T>>
struct __vector_type_helper : integral_constant<size_t, is_same<bool, U>::value ? boolean : is_integral<U>::value ? integral : floating_point> { };

/// \brief Base class for vector channel reference type
///
template <class Vec>
struct __channel_ref_base
{
    __ALWAYS_INLINE constexpr __channel_ref_base( Vec& vector, size_t channel ) __NOEXCEPT : _vec( vector ), _channel( channel ) { }
    __ALWAYS_INLINE constexpr __channel_ref_base( ) = default;
    __ALWAYS_INLINE constexpr __channel_ref_base( const __channel_ref_base&) __NOEXCEPT = default;
    __ALWAYS_INLINE constexpr __channel_ref_base( __channel_ref_base&&) __NOEXCEPT = default;
    __ALWAYS_INLINE constexpr __channel_ref_base& operator=( const __channel_ref_base&) __NOEXCEPT = default;
    __ALWAYS_INLINE constexpr __channel_ref_base& operator=( __channel_ref_base&&) __NOEXCEPT = default;

    using type = remove_attrs_t<vector_element_t<Vec>>;

protected:
    __ALWAYS_INLINE constexpr type _get( ) __NOEXCEPT { return __index_helper<Vec>::get( _vec, _channel ); }
    __ALWAYS_INLINE constexpr void _set( type value ) __NOEXCEPT { __index_helper<Vec>::set( _vec, _channel, value ); }

    size_t _channel;
    Vec& _vec;
};

#define OP( SYM ) __ALWAYS_INLINE constexpr __channel_ref_impl& operator SYM##=( type value ) __NOEXCEPT { this->_set( this->_get( ) SYM value ); return *this; } \
                __ALWAYS_INLINE constexpr friend type operator SYM( __channel_ref_impl lhs, type rhs ) __NOEXCEPT { lhs SYM##= rhs; return lhs; }

/// \brief Channel reference implementation. Presents correct operator set for underlying type.
///
/// Has specializations for integral, floating point and boolean types.
template <class Vec, size_t = __details::__vector_type_helper<vector_element_t<Vec>>::value>
struct __channel_ref_impl : __details::__channel_ref_base<Vec>
{
    using __details::__channel_ref_base<Vec>::__channel_ref_base;
    using type = typename __details::__channel_ref_base<Vec>::type;

    __ALWAYS_INLINE constexpr operator type( ) __NOEXCEPT { return this->_get( ); }

    __ALWAYS_INLINE constexpr __channel_ref_impl& operator=( type value ) __NOEXCEPT { this->_set( value ); return *this; }

    OP(+) OP(-) OP(*) OP(/) OP(%) OP(^) OP(&) OP(|)

    __ALWAYS_INLINE constexpr __channel_ref_impl& operator++( ) __NOEXCEPT { operator+=(1); return *this; }
    __ALWAYS_INLINE constexpr __channel_ref_impl operator++( int ) __NOEXCEPT { __channel_ref_impl tmp(*this ); operator++( ); return tmp; }
    __ALWAYS_INLINE constexpr __channel_ref_impl& operator--( ) __NOEXCEPT { operator-=(1); return *this; }
    __ALWAYS_INLINE constexpr __channel_ref_impl operator--( int ) __NOEXCEPT { __channel_ref_impl tmp(*this ); operator--( ); return tmp; }
};

/// \brief Channel reference implementation. Presents correct operator set for underlying type.
///
/// Has specializations for integral, floating point and boolean types.
template <class Vec>
struct __channel_ref_impl<Vec, __details::__vector_type::floating_point> : __details::__channel_ref_base<Vec>
{
    using __details::__channel_ref_base<Vec>::__channel_ref_base;
    using type = typename __details::__channel_ref_base<Vec>::type;

    __ALWAYS_INLINE constexpr operator type( ) __NOEXCEPT { return this->_get( ); }

    __ALWAYS_INLINE constexpr __channel_ref_impl& operator=( type value ) __NOEXCEPT { this->_set( value ); return *this; }

    OP(+) OP(-) OP(*) OP(/)

    __ALWAYS_INLINE constexpr __channel_ref_impl& operator++( ) __NOEXCEPT { operator+=(1); return *this; }
    __ALWAYS_INLINE constexpr __channel_ref_impl operator++( int ) __NOEXCEPT { __channel_ref_impl tmp(*this ); operator++( ); return tmp; }
    __ALWAYS_INLINE constexpr __channel_ref_impl& operator--( ) __NOEXCEPT { operator-=(1); return *this; }
    __ALWAYS_INLINE constexpr __channel_ref_impl operator--( int ) __NOEXCEPT { __channel_ref_impl tmp(*this ); operator--( ); return tmp; }
};

/// \brief Channel reference implementation. Presents correct operator set for underlying type.
///
/// Has specializations for integral, floating point and boolean types.
template <class Vec>
struct __channel_ref_impl<Vec, __details::__vector_type::boolean> : __details::__channel_ref_base<Vec>
{
    using __details::__channel_ref_base<Vec>::__channel_ref_base;
    using type = typename __details::__channel_ref_base<Vec>::type;

    __ALWAYS_INLINE constexpr operator type( ) __NOEXCEPT { return this->_get( ); }

    __ALWAYS_INLINE constexpr __channel_ref_impl& operator=( type value ) __NOEXCEPT { this->_set( value ); return *this; }

    OP(+) OP(-) OP(*) OP(/) OP(%) OP(^) OP(&) OP(|)

    __ALWAYS_INLINE constexpr __channel_ref_impl& operator++( ) __NOEXCEPT { operator+=(1); return *this; }
    __ALWAYS_INLINE constexpr __channel_ref_impl operator++( int )__NOEXCEPT { __channel_ref_impl tmp(*this ); operator++( ); return tmp; }
};

#undef OP

}

/// \brief Reference wrapper for vector channel. Presents correct operator set for underlying type.
///
/// Has specializations for integral, floating point and boolean types.
template<class Vec>
struct channel_ref : __details::__channel_ref_impl<Vec>
{
    using __details::__channel_ref_impl<Vec>::__channel_ref_impl;
    using __details::__channel_ref_impl<Vec>::operator=;
};

/// \brief Pointer wrapper for vector channel. Dereferenced returns channel_ref.
///
template <class Vec>
struct channel_ptr
{
    __ALWAYS_INLINE constexpr channel_ptr( ) __NOEXCEPT { }
    __ALWAYS_INLINE constexpr channel_ptr( const channel_ref<Vec>& ref ) __NOEXCEPT : _ref( ref ) { }
    __ALWAYS_INLINE constexpr channel_ptr( const channel_ptr&) __NOEXCEPT = default;
    __ALWAYS_INLINE constexpr channel_ptr( channel_ptr&&) __NOEXCEPT = default;
    __ALWAYS_INLINE constexpr channel_ptr& operator=( const channel_ptr&) __NOEXCEPT = default;
    __ALWAYS_INLINE constexpr channel_ptr& operator=( channel_ptr&&) __NOEXCEPT = default;

    using type = remove_attrs_t<vector_element_t<Vec>>;

    __ALWAYS_INLINE constexpr channel_ref<Vec>& operator*( ) __NOEXCEPT { return _ref; }

protected:
    channel_ref<Vec> _ref;
};

/// \brief Vector iterator class.
///
/// Satisfies random access iterator requirements
template <class Vec>
struct vector_iterator : iterator<random_access_iterator_tag,
                                  remove_attrs_t<vector_element_t<remove_attrs_t<Vec>>>,
                                  ptrdiff_t,
                                  channel_ptr<remove_attrs_t<Vec>>,
                                  channel_ref<remove_attrs_t<Vec>>>
{
public:
    using type = remove_attrs_t<Vec>;

private:
    using _base = iterator<random_access_iterator_tag,
                           remove_attrs_t<vector_element_t<remove_attrs_t<Vec>>>,
                           ptrdiff_t,
                           channel_ptr<remove_attrs_t<Vec>>,
                           channel_ref<remove_attrs_t<Vec>>>;
    size_t _offset;
    type _vec;

public:
    using difference_type = typename _base::difference_type;
    using reference = typename _base::reference;
    using pointer = typename _base::pointer;

    __ALWAYS_INLINE constexpr vector_iterator( type & vector, size_t offset ) __NOEXCEPT : _vec( vector ), _offset( offset ) { }
    __ALWAYS_INLINE constexpr vector_iterator( ) __NOEXCEPT = default;
    __ALWAYS_INLINE constexpr vector_iterator( const vector_iterator&) __NOEXCEPT = default;
    __ALWAYS_INLINE constexpr vector_iterator( vector_iterator&&) __NOEXCEPT = default;
    __ALWAYS_INLINE constexpr vector_iterator& operator=( const vector_iterator&) __NOEXCEPT = default;
    __ALWAYS_INLINE constexpr vector_iterator& operator=( vector_iterator&&) __NOEXCEPT = default;

    __ALWAYS_INLINE constexpr vector_iterator& operator+=( difference_type value ) __NOEXCEPT { _offset += value; return *this; }
    __ALWAYS_INLINE constexpr friend vector_iterator operator+( const vector_iterator& lhs, difference_type rhs ) __NOEXCEPT { auto tmp = lhs; return tmp += rhs; }
    __ALWAYS_INLINE constexpr friend vector_iterator operator+( difference_type lhs, const vector_iterator& rhs ) __NOEXCEPT { auto tmp = rhs; return tmp += lhs; }
    __ALWAYS_INLINE constexpr vector_iterator& operator-=( difference_type value ) __NOEXCEPT { _offset += -value; return *this; }
    __ALWAYS_INLINE constexpr friend vector_iterator operator-( const vector_iterator& lhs, difference_type rhs ) __NOEXCEPT { auto tmp = lhs; return tmp -= rhs; }

    __ALWAYS_INLINE constexpr vector_iterator operator++( int ) __NOEXCEPT { auto temp = *this; ++*this; return temp; }
    __ALWAYS_INLINE constexpr vector_iterator& operator++( ) __NOEXCEPT { _offset++; return *this; }
    __ALWAYS_INLINE constexpr vector_iterator operator--( int ) __NOEXCEPT { auto temp = *this; --*this; return temp; }
    __ALWAYS_INLINE constexpr vector_iterator& operator--( ) __NOEXCEPT { _offset--; return *this; }

    #define OP( SYM ) friend __ALWAYS_INLINE constexpr bool operator SYM( const vector_iterator& lhs, const vector_iterator& rhs ) __NOEXCEPT { return lhs._offset SYM rhs._offset; }
    OP(==) OP(!=) OP(<) OP(<=) OP(>) OP(>=)
    #undef OP

    __ALWAYS_INLINE constexpr reference operator[ ]( difference_type value ) __NOEXCEPT { return reference( _vec, _offset + value ); }
    __ALWAYS_INLINE constexpr reference operator*( ) __NOEXCEPT { return channel_ref<type>( _vec, _offset ); }

    __ALWAYS_INLINE constexpr pointer operator->( ) __NOEXCEPT { return channel_ptr<type>( channel_ref<type>( _vec, _offset )); }
};

/// \brief Function returning channel_ref for given index of vector.
///
template <class Vec, class = enable_if_t<is_vector_type<Vec>::value, void>>
__ALWAYS_INLINE constexpr channel_ref<Vec> index( Vec& vector, size_t channel ) __NOEXCEPT { return channel_ref<Vec>( vector, channel ); }

/// \brief Non member begin function for builtin vector types. Returns vector_iterator.
///
template <class Vec, class = enable_if_t<is_vector_type<Vec>::value, void>>
__ALWAYS_INLINE constexpr vector_iterator<Vec> begin( Vec & vector ) __NOEXCEPT { return vector_iterator<Vec>( vector, 0); }

/// \brief Non member end function for builtin vector types. Returns vector_iterator.
///
template <class Vec, class = enable_if_t<is_vector_type<Vec>::value, void>>
__ALWAYS_INLINE constexpr vector_iterator<Vec> end( Vec & vector ) __NOEXCEPT { return vector_iterator<Vec>( vector, vector_size<Vec>::value ); }

}

