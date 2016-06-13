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

#ifdef SIMPLE_SWIZZLES
 #include <__ocl_swizzle_macros.h>
#endif

#include <__ocl_vector_utility.h>

namespace cl
{

static constexpr size_t undef_channel = static_cast<size_t>(-1);
enum class channel : size_t { r = 0, g = 1, b = 2, a = 3, x = 0, y = 1, z = 2, w = 3, undef = undef_channel };

/// \brief Forward declaration of standard cl::vec class
///
template <class T, size_t Size>
struct vec;

template <size_t... Swizzle, class Vec>
auto swizzle(Vec& v);

namespace __details
{

template <class SwizzleSeq>
struct __swizzle_seq_adapt;

template <size_t... Swizzle>
struct __swizzle_seq_adapt<__size_t_seq<Swizzle...>>
{
    template <typename Vec>
    __ALWAYS_INLINE static auto __swizzle(Vec& vec)
    {
        return cl::swizzle<Swizzle...>(vec);
    }
};

/// \brief Helper class which exposes all swizzle methods for given elements count
///
template <class CRTP>
struct __impl_swizzle
{
    //static_assert(is_base_of<__impl_swizzle<CRTP>, CRTP>::value, "Interal error: invalid CRTP");

    template <size_t... Swizzle>
    __ALWAYS_INLINE auto swizzle()
    {
        return cl::swizzle<Swizzle...>(static_cast<CRTP&>(*this));
    }

    template <size_t... Swizzle>
    __ALWAYS_INLINE auto swizzle() const
    {
        return cl::swizzle<Swizzle...>(static_cast<CRTP const&>(*this));
    }
};

#ifdef SIMPLE_SWIZZLES
template <class CRTP, size_t Elements>
struct __impl_special_swizzles : public __impl_swizzle<CRTP>
{
    __ALWAYS_INLINE auto lo()
    {
        return __swizzle_seq_adapt<
                    typename __make_size_t_seq<0, ((Elements % 2) ? Elements/2 + 1 : Elements/2)>::type
               >::__swizzle(static_cast<CRTP&>(*this));
    }

    __ALWAYS_INLINE auto lo() const
    {
        return __swizzle_seq_adapt<
                    typename __make_size_t_seq<0, ((Elements % 2) ? Elements/2 + 1 : Elements/2)>::type
               >::__swizzle(static_cast<CRTP const&>(*this));
    }

    __ALWAYS_INLINE auto hi()
    {
        return __swizzle_seq_adapt<
                    typename __concat_seq<size_t,
                        typename __make_size_t_seq<((Elements % 2) ? Elements/2 + 1 : Elements/2), Elements>::type,
                        typename __repeat<size_t, undef_channel, (Elements & 1 ? 1 : 0)>::type
                    >::type
               >::__swizzle(static_cast<CRTP&>(*this));
    }

    __ALWAYS_INLINE auto hi() const
    {
        return __swizzle_seq_adapt<
                    typename __concat_seq<size_t,
                        typename __make_size_t_seq<((Elements % 2) ? Elements/2 + 1 : Elements/2), Elements>::type,
                        typename __repeat<size_t, undef_channel, (Elements & 1 ? 1 : 0)>::type
                    >::type
               >::__swizzle(static_cast<CRTP const&>(*this));
    }

    __ALWAYS_INLINE auto even()
    {
        return __swizzle_seq_adapt<
                    typename __make_size_t_seq<0, Elements, 2>::type
               >::__swizzle(static_cast<CRTP&>(*this));
    }

    __ALWAYS_INLINE auto even() const
    {
        return __swizzle_seq_adapt<
                    typename __make_size_t_seq<0, Elements, 2>::type
               >::__swizzle(static_cast<CRTP const&>(*this));
    }

    __ALWAYS_INLINE auto odd()
    {
        return __swizzle_seq_adapt<
                    typename __concat_seq<size_t,
                        typename __make_size_t_seq<1, Elements, 2>::type,
                        typename __repeat<size_t, undef_channel, ((Elements % 2) ? 1 : 0)>::type
                    >::type
               >::__swizzle(static_cast<CRTP&>(*this));
    }

    __ALWAYS_INLINE auto odd() const
    {
        return __swizzle_seq_adapt<
                    typename __concat_seq<size_t,
                        typename __make_size_t_seq<1, Elements, 2>::type,
                        typename __repeat<size_t, undef_channel, ((Elements % 2) ? 1 : 0)>::type
                    >::type
               >::__swizzle(static_cast<CRTP const&>(*this));
    }
};

/// \brief Helper class which exposes "simple swizzle" methods for given elements count
///
template <class CRTP, size_t Elements>
struct __impl_simple_swizzle : public __impl_special_swizzles<CRTP, Elements>
{
    COMB_RPT4LVL1(r, g, b, a);
    COMB_RPT4LVL1(x, y, z, w);
};

template <class CRTP>
struct __impl_simple_swizzle<CRTP, 3> : public __impl_special_swizzles<CRTP, 3>
{
    COMB_RPT3LVL1(r, g, b);
    COMB_RPT3LVL1(x, y, z);
};

template <class CRTP>
struct __impl_simple_swizzle<CRTP, 2> : public __impl_special_swizzles<CRTP, 2>
{
    COMB_RPT2LVL1(r, g);
    COMB_RPT2LVL1(x, y);
};

template <class CRTP, size_t Elements>
using __impl_swizzle_t = __impl_simple_swizzle<CRTP, Elements>;

#else

template <class CRTP, size_t>
using __impl_swizzle_t = __impl_swizzle<CRTP>;

#endif

/// \brief helper struct which checks whatever given size_t list does not contain duplicates
///
/// handles case when Indexes... is empty => returns true
///
template <int CheckMask, size_t... Indexes>
struct __is_valid_write_swizzle : public true_type {};

/// \brief helper struct which checks whatever given size_t list does not contain duplicates
///
/// handles case when Indexes... has at least one element 'Check' => checks if in CheckMask bit at 'Check' position is already set,
///  if yes returns false_type, otherwise set bit and call validation recursively for 'Rest' elements
///
template <int CheckMask, size_t Check, size_t... Rest>
struct __is_valid_write_swizzle<CheckMask, Check, Rest...> : public conditional_t<(CheckMask & (1 << Check)) != 0, false_type, __is_valid_write_swizzle<CheckMask | (1 << Check), Rest...>> {};


/// \brief helper structure which flattens two swizzles during assignment swizzle<...>() = swizzle<...>(). LH swizzle must be write-swizzle. This structure is 'called' for every
/// index N in LH vector and returns index such as: LH[N] = __builtin_shufflevector(LH, RH, __resolve_single_index<N>::index) is valid.
///
/// Elements, Curr, ReadSwizzleSeq and WriteSwizzleSeq are passed from __write_swizzle_shufflevector and mean that we need to resolve Curr-th element in shufflevector's resulting vector,
/// where total number of elements is Elements (which is also size of shufflevector's first vector), lh vector is swizzled with WriteSwizzleSeq and rh vector is swizzled with ReadSwizzleSeq.
/// For more information about __write_swizzle assignment see __write_swizzle_shufflevector description.
/// This class in addition takes argument 'Swizzled' which tells whether Curr-th element in lh operand of assignment is swizzled by WriteSwizzleSeq.
/// Check specializations for behaviour in both (swizzled and not) cases.
///
/// ReadSwizzleSeq and WriteSwizzleSeq should both be __size_t_seq<...>
///
template <size_t Elements, size_t Curr, class ReadSwizzleSeq, class WriteSwizzleSeq, bool Swizzled>
struct __resolve_single_index;

/// \brief helper structure which flattens two swizzles during assignment swizzle<...>() = swizzle<...>(). LH swizzle must be write-swizzle. This structure is 'called' for every
/// index N in LH vector and returns index such as: LH[N] = __builtin_shufflevector(LH, RH, __resolve_single_index<N>::index) is valid.
///
/// If current element is swizzled we need to find it's position in WriteSwizzle and get element at corresponding position from ReadSwizzle + rh vector offset (== Elements)
/// i.e.:
///  vec.y() = tmp.x()
///  gives us Elements = 4, WriteSwizzle<1> and ReadSwizzle<0>
///   when resolving 2-nd element (Curr == 1), we need to check if it's present in WriteSwizzle (it is), takes it's position (0) and take ReadSwizzle[0] + Elements == 4
///   so resulting code will look like: vec = __builtin_shufflevector(..., 4, ...., ....);
///
template <size_t Elements, size_t Curr, size_t... ReadSwizzle, size_t... WriteSwizzle>
struct __resolve_single_index<Elements, Curr, __size_t_seq<ReadSwizzle...>, __size_t_seq<WriteSwizzle...>, true>
    : public integral_constant<int,
                               __ithElement<
                                    __find<0, __size_t_seq<Curr>, __size_t_seq<WriteSwizzle>...>::value,
                                    integral_constant<int, static_cast<int>(ReadSwizzle)>...
                                >::type::value + Elements>
{};

/// \brief helper structure which flattens two swizzles during assignment swizzle<...>() = swizzle<...>(). LH swizzle must be write-swizzle. This structure is 'called' for every
/// index N in LH vector and returns index such as: LH[N] = __builtin_shufflevector(LH, RH, __resolve_single_index<N>::index) is valid.
///
/// If current element isn't swizzled we just pass it
/// i.e.:
///  vec.y() = tmp.x()
///  gives us Elements = 4, WriteSwizzle<1> and ReadSwizzle<0>
///   when resolving 1-st element (Curr == 0), we need to check if it's present in WriteSwizzle (it is not) so we return 0 (== Curr)
///   resulting code will look like: vec = __builtin_shufflevector(0, ..., ...., ....);
///
template <size_t Elements, size_t Curr, size_t... ReadSwizzle, size_t... WriteSwizzle>
struct __resolve_single_index<Elements, Curr, __size_t_seq<ReadSwizzle...>, __size_t_seq<WriteSwizzle...>, false>
    : public integral_constant<int, static_cast<int>(Curr)>
{};

/// \brief helper struct which builds indexes to pass to clang's __builtin_shufflevector
///
/// This helper generates indexes valid for swizzles used in write operations, i.e.:
///    vec.wxy() = tmp.xzy();
/// first swizzle method will return __write_swizzle<3,0,1> object which later is assigned with a __read_swizzle<0,2,1> object build from 3-component vector 'tmp'.
/// assuming vec is 4-component vector, generated code should look like:
///    vec = __builtin_shufflevector(vec, tmp, 6, 5, 2, 4); --> 3-rd element from tmp, 2-nd element from tmp, 3-rd element from vec, 1-st element from tmp
/// this helper is responsible for generating (6,5,2,4) sequence being given write swizzle's sequence (3,0,1), read swizzle's sequence (0,2,1) and first vector's length
///
///  Elements -> no of elements in resulting vector == no of indexes to generate == no of elements in lh vector
///  Curr -> position of __builtin_sufflevector's index being currently processed
///  ReadSwizzleSeq -> swizzle sequence from __read_swizzle
///  WriteSwizzleSeq -> swizzle sequence from __write_swizzle
///
/// Recurrence strategy is to firstly obtain empty sequence by recursive calls and later prepend single indexes in each instantiation (process from end to beginning).
/// Both ReadSwizzleSeq and WriteSwizzleSeq should be __size_t_seq<...>
///
template <size_t Elements, size_t Curr, class ReadSwizzleSeq, class WriteSwizzleSeq>
struct __write_swizzle_shufflevector;

/// \brief helper struct which builds indexes to pass to clang's __builtin_shufflevector
///
template <size_t Elements, size_t Curr, size_t... ReadSwizzle, size_t... WriteSwizzle>
struct __write_swizzle_shufflevector<Elements, Curr, __size_t_seq<ReadSwizzle...>, __size_t_seq<WriteSwizzle...>>
{
    using __is_swizzled = __is_one_of<__size_t_seq<Curr>, __size_t_seq<WriteSwizzle>...>;

    using __reccurence = typename __write_swizzle_shufflevector<Elements, Curr + 1, __size_t_seq<ReadSwizzle...>, __size_t_seq<WriteSwizzle...>>::__indexes;

    using __indexes = typename __reccurence::template prepend<__resolve_single_index<Elements, Curr, __size_t_seq<ReadSwizzle...>, __size_t_seq<WriteSwizzle...>, __is_swizzled::value>::value>;
};

/// \brief helper struct which builds indexes to pass to clang's __builtin_shufflevector
///
/// In case when we have reached 'Elements' => return empty sequence
///
template <size_t Elements, size_t... ReadSwizzle, size_t... WriteSwizzle>
struct __write_swizzle_shufflevector<Elements, Elements, __size_t_seq<ReadSwizzle...>, __size_t_seq<WriteSwizzle...>>
{
    using __indexes = __seq<int>;
};

/// \brief Forward declaration of helper struct which is capable of emitting __builtin_shufflevector instructions
///  for any given pair of vectors V1, V2 as long as they have the same component type (but not necessarily  size)
///
template <class ShufflevectorIndexesSeq>
struct __emit_shufflevector;

/// \brief helper function which extends given vector Vec by padding it with undef elements
///
/// Assuming v has n elements and Padding == 4, generated call will look like:
///  __builtin_shufflevector(v, v, 0, 1, ..., n, -1, -1, -1, -1);
///
template <size_t Padding, class Vec>
__ALWAYS_INLINE auto __ext_vector(Vec const& v)
{
    return __emit_shufflevector<typename __concat_seq<
            int,
            typename __make_size_t_seq<0, vector_size<Vec>::value>::type,
            typename __repeat<int, -1, Padding>::type
        >::type
    >::__make_call(v, v);
}

/// \brief helper function which trims given vector Vec so it have exactly Count elements
///
/// generates: __builtin_shufflevector(v, v, 0, 1, ..., Count);
///
template <size_t Count, class Vec>
__ALWAYS_INLINE auto __trim_vector(Vec const& v)
{
    return __emit_shufflevector<typename __concat_seq<
            int,
            typename __make_size_t_seq<0, Count>::type,
            __seq<int>
        >::type
    >::__make_call(v, v);
}

/// \brief Helper struct which is capable of emitting __builtin_shufflevector instructions
///  for any given pair of vectors V1, V2 as long as they have the same component type (but not necessarily  size)
///
template <int... ShufflevectorIndexes>
struct __emit_shufflevector<__seq<int, ShufflevectorIndexes...>>
{
    // When both Vec1 and Vec2 have the same size, emit simple __builtin_shufflevector
    //
    template <class Vec1, class Vec2>
    __ALWAYS_INLINE static auto __make_call(Vec1 const& v1, Vec2 const& v2, enable_if_t<(vector_size<Vec1>::value == vector_size<Vec2>::value), nullptr_t> = nullptr)
    {
        return __builtin_shufflevector(v1, v2, ShufflevectorIndexes...);
    }

    // When Vec1 has more elements than Vec2, extend Vec2 with undef values so it has the same elements count
    //
    template <class Vec1, class Vec2>
    __ALWAYS_INLINE static auto __make_call(Vec1 const& v1, Vec2 const& v2, enable_if_t<(vector_size<Vec1>::value > vector_size<Vec2>::value), nullptr_t> = nullptr)
    {
        return __builtin_shufflevector(v1,
            static_cast<Vec1 const&>(__ext_vector<vector_size<Vec1>::value - vector_size<Vec2>::value>(v2)),
            ShufflevectorIndexes...);
    }

    // When Vec1 has less elements than Vec2, trim Vec2 so it has the same elements count
    //
    template <class Vec1, class Vec2>
    __ALWAYS_INLINE static auto __make_call(Vec1 const& v1, Vec2 const& v2, enable_if_t<(vector_size<Vec1>::value < vector_size<Vec2>::value), nullptr_t> = nullptr)
    {
        return __builtin_shufflevector(v1,
            static_cast<Vec1 const&>(__trim_vector<vector_size<Vec1>::value>(v2)),
            ShufflevectorIndexes...);
    }
};

/// \brief Base class for all swizzles
///
/// Contains reference to swizzled vector and validates passed swizzle indexes
///
template <class Vec, size_t... Indexes>
struct __swizzle : public __impl_swizzle_t<__swizzle<Vec, Indexes...>, sizeof...(Indexes)>
{
    static_assert(__all<(static_cast<int>(Indexes) < static_cast<int>(vector_size<Vec>::value))...>::value, "Swizzle index out of vector's range!");

    using underlying_t = make_vector_t<vector_element_t<Vec>, sizeof...(Indexes)>;
    using wrapper_t = vec<vector_element_t<Vec>, sizeof...(Indexes)>;

    static_assert(vector_size<underlying_t>::value == sizeof...(Indexes), "Invalid swizzle! (unsupported element type or element's count)");

    static constexpr bool __IsWriteSwizzle = __is_valid_write_swizzle<0, Indexes...>::value && !is_const<Vec>::value;

    __swizzle(Vec& v) : _vec(v) {}
    __swizzle(__swizzle const& s) = default;
    __swizzle(__swizzle && s) = default;

    __ALWAYS_INLINE operator underlying_t() const
    {
        return __emit_shufflevector<__seq<int, static_cast<int>(Indexes)...>>::__make_call(_vec, _vec);
    }

    __ALWAYS_INLINE operator wrapper_t() const
    {
        return wrapper_t{ static_cast<underlying_t>(*this) };
    }

    __ALWAYS_INLINE void operator = (underlying_t const& vec)
    {
        static_assert(__IsWriteSwizzle, "This swizzle does not support assign operator");

        _vec = __emit_shufflevector<
            typename __write_swizzle_shufflevector<
                vector_size<Vec>::value,
                0,
                typename __make_size_t_seq<0, sizeof...(Indexes)>::type,
                __size_t_seq<Indexes...>
            >::__indexes
        >::__make_call(_vec, vec);
    }

    template <class ReadVec, size_t... ReadIndexes>
    __ALWAYS_INLINE enable_if_t<(sizeof...(ReadIndexes) > 1), void> operator = (__swizzle<ReadVec, ReadIndexes...> const& rs)
    {
        static_assert(__IsWriteSwizzle, "This swizzle does not support assign operator");
        static_assert(is_same<remove_cv_t<vector_element_t<Vec>>, remove_cv_t<vector_element_t<ReadVec>>>::value, "Cannot assign vector with different element type to swizzle");

        _vec = __emit_shufflevector<
            typename __write_swizzle_shufflevector<
                vector_size<Vec>::value,
                0,
                __size_t_seq<ReadIndexes...>,
                __size_t_seq<Indexes...>
            >::__indexes
        >::__make_call(_vec, rs._vec);
    }

    Vec& _vec;
};

template <class Vec, size_t Index>
struct __swizzle<Vec, Index> : public channel_ref<Vec>, public __impl_swizzle_t<__swizzle<Vec, Index>, 1>
{
    __swizzle(Vec& v) : channel_ref<Vec>(v, Index) {}
    __swizzle(__swizzle const& s) = default;
    __swizzle(__swizzle && s) = default;

    using channel_ref<Vec>::operator =;
};

template <class Vec, size_t... Swizzle>
struct __make_swizzle_type
{
    using type = __swizzle<Vec, Swizzle...>;
};

template <class VecChannel, size_t VecSize, size_t... Swizzle>
struct __make_swizzle_type<vec<VecChannel, VecSize>, Swizzle...>
{
    using type = __swizzle<typename vec<VecChannel, VecSize>::vector_type, Swizzle...>;
};

template <class VecChannel, size_t VecSize, size_t... Swizzle>
struct __make_swizzle_type<const vec<VecChannel, VecSize>, Swizzle...>
{
    using type = __swizzle<add_const_t<typename vec<VecChannel, VecSize>::vector_type>, Swizzle...>;
};

template <class SwizzleV, size_t... SwizzleI, size_t... Swizzle>
struct __make_swizzle_type<__swizzle<SwizzleV, SwizzleI...>, Swizzle...>
{
    using type = __swizzle<SwizzleV, __ithElement<Swizzle, integral_constant<size_t, SwizzleI>...>::type::value...>;
};

template <class Vec, size_t... Swizzle>
__ALWAYS_INLINE enable_if_t<(sizeof...(Swizzle) > 1), Vec&> __get_underlying_vec(__swizzle<Vec, Swizzle...>& s)
{
    return s._vec;
}

template <class Vec, size_t... Swizzle>
__ALWAYS_INLINE enable_if_t<(sizeof...(Swizzle) > 1), Vec&> __get_underlying_vec(__swizzle<Vec, Swizzle...> const& s)
{
    return s._vec;
}

template <class Vec, size_t Swizzle>
__ALWAYS_INLINE Vec& __get_underlying_vec(__swizzle<Vec, Swizzle>& s)
{
    return s._vec;
}

template <class Vec, size_t Swizzle>
__ALWAYS_INLINE Vec& __get_underlying_vec(__swizzle<Vec, Swizzle> const& s)
{
    return s._vec;
}

template <class Vec>
__ALWAYS_INLINE Vec& __get_underlying_vec(__channel_ref_base<Vec>& s)
{
    return s._vec;
}

template <class Vec>
__ALWAYS_INLINE Vec& __get_underlying_vec(__channel_ref_base<Vec> const& s)
{
    return s._vec;
}

template <class VecChannel, size_t VecSize>
__ALWAYS_INLINE auto& __get_underlying_vec(vec<VecChannel, VecSize>& s)
{
    return s.__get();
}

template <class VecChannel, size_t VecSize>
__ALWAYS_INLINE auto& __get_underlying_vec(vec<VecChannel, VecSize> const& s)
{
    return s.__get();
}

template <class Vec>
__ALWAYS_INLINE auto& __get_underlying_vec(Vec& v)
{
    return v;
}

} //end namespace __details

} //end namespace cl
