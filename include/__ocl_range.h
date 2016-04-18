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
#include <__ocl_vector_utility.h>

namespace cl
{

    namespace __details
    {

        /// \brief Helper class to assess if given type has member typedef for difference_type
        ///
        template <class It>
        struct __has_diff_type
        {
        private:
            template<class I>
            static decltype(static_cast<void>(declval<typename I::difference_type>( )), true_type{}) helper( nullptr_t );

            template <class I>
            static false_type helper(void*);

        public:
            static const bool value = decltype(helper<It>(nullptr))::value;
        };

        /// \brief Helper class to unify difference type for normal iterable types and buitin vectors
        ///
        template <class It, bool = __has_diff_type<It>::value>
        struct __diff_type { using type = typename It::difference_type; };

        /// \brief Helper class to unify difference type for normal iterable types and buitin vectors
        ///
        template <class It>
        struct __diff_type<It, false> { using type = ptrdiff_t; };

        template <class It>
        using __diff_type_t = typename __diff_type<It>::type;

    }

    /// \brief Class defining range over iterable type
    ///
    template <class It, bool = false, bool = false>
    struct range_type
    {
    private:
        It& _it;
    public:
        __ALWAYS_INLINE constexpr range_type(It& it) __NOEXCEPT : _it(it) { }
        __ALWAYS_INLINE constexpr auto begin() __NOEXCEPT{ return cl::begin(_it); }
        __ALWAYS_INLINE constexpr auto end() __NOEXCEPT{ return cl::end(_it); }
    };

    /// \brief Class defining range over iterable type
    ///
    template <class It>
    struct range_type<It, true, false>
    {
    private:
        It& _it;
        using difference_type = __details::__diff_type_t<decltype(cl::begin(declval<It&>()))>;
        difference_type _end;
    public:
        __ALWAYS_INLINE constexpr range_type(It& it, difference_type end) __NOEXCEPT : _it(it), _end(end) { }
        __ALWAYS_INLINE constexpr auto begin() __NOEXCEPT{ return cl::begin(_it); }
        __ALWAYS_INLINE constexpr auto end() __NOEXCEPT{ auto temp = cl::begin(_it); advance(temp, _end); return temp; }
    };

    /// \brief Class defining range over iterable type
    ///
    template <class It>
    struct range_type<It, true, true>
    {
    private:
        It& _it;
        using difference_type = __details::__diff_type_t<decltype(cl::begin(declval<It&>()))>;
        difference_type _begin;
        difference_type _end;
    public:
        __ALWAYS_INLINE constexpr range_type(It& it, difference_type begin, difference_type end) __NOEXCEPT : _it(it), _begin(begin), _end(end) { }
        __ALWAYS_INLINE constexpr auto begin() __NOEXCEPT{ auto temp = cl::begin(_it); advance(temp, _begin); return temp; }
        __ALWAYS_INLINE constexpr auto end() __NOEXCEPT{ auto temp = cl::begin(_it); advance(temp, _end); return temp; }
    };

    /// \brief Function returning range_type for given parameters and iterable type (including builtin vector types)
    ///
    template <class It>
    __ALWAYS_INLINE constexpr auto range(It& it) __NOEXCEPT{ return range_type<It>(it); }

    /// \brief Function returning range_type for given parameters and iterable type (including builtin vector types)
    ///
    template <class It>
    __ALWAYS_INLINE constexpr auto range(It& it, __details::__diff_type_t<It> diff) __NOEXCEPT{ return range_type<It, true>(it, diff); }

    /// \brief Function returning range_type for given parameters and iterable type (including builtin vector types)
    ///
    template <class It>
    __ALWAYS_INLINE constexpr auto range(It& it, __details::__diff_type_t<It> begin, __details::__diff_type_t<It> end) __NOEXCEPT{ return range_type<It, true, true>(it, begin, end); }

}