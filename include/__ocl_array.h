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
#include <__ocl_utility.h>
#include <__ocl_type_traits_address_spaces.h>
#include <__ocl_iterator.h>

namespace cl
{
/// \brief Array class similar to the one defined by C++ standard
///
template<class T, size_t N>
class array
{
public:
    //types:
    typedef T                                     value_type;
    typedef size_t                                size_type;
    typedef ptrdiff_t                             difference_type;
    typedef T&                                    reference;
    typedef const T&                              const_reference;
    typedef T*                                    iterator;
    typedef const T*                              const_iterator;
    typedef T*                                    pointer;
    typedef const T*                              const_pointer;
    typedef cl::reverse_iterator<iterator>        reverse_iterator;
    typedef cl::reverse_iterator<const_iterator>  const_reverse_iterator;

    value_type __elems[N > 0 ? N : 1];

    // iterators:
    __ALWAYS_INLINE iterator begin() __NOEXCEPT{ return iterator(__elems); }
    __ALWAYS_INLINE const_iterator begin() const __NOEXCEPT{ return const_iterator(__elems); }
    __ALWAYS_INLINE iterator end() __NOEXCEPT{ return iterator(__elems + N); }
    __ALWAYS_INLINE const_iterator end() const __NOEXCEPT{ return const_iterator(__elems + N); }

    __ALWAYS_INLINE reverse_iterator rbegin() __NOEXCEPT{ return reverse_iterator(end()); }
    __ALWAYS_INLINE const_reverse_iterator rbegin() const __NOEXCEPT{ return const_reverse_iterator(end()); }
    __ALWAYS_INLINE reverse_iterator rend() __NOEXCEPT{ return reverse_iterator(begin()); }
    __ALWAYS_INLINE const_reverse_iterator rend() const __NOEXCEPT{ return const_reverse_iterator(begin()); }

    __ALWAYS_INLINE const_iterator cbegin() const __NOEXCEPT{ return begin(); }
    __ALWAYS_INLINE const_iterator cend() const __NOEXCEPT{ return end(); }
    __ALWAYS_INLINE const_reverse_iterator crbegin() const __NOEXCEPT{ return rbegin(); }
    __ALWAYS_INLINE const_reverse_iterator crend() const __NOEXCEPT{ return rend(); }

        // capacity:
    __ALWAYS_INLINE constexpr size_type size() const __NOEXCEPT{ return N; }
    __ALWAYS_INLINE constexpr size_type max_size() const __NOEXCEPT{ return N; }
    __ALWAYS_INLINE constexpr bool empty() const __NOEXCEPT{ return N == 0; }

        // element access:
    __ALWAYS_INLINE reference operator[](size_type n) __NOEXCEPT{ return __elems[n]; }
    __ALWAYS_INLINE const_reference operator[](size_type n) const __NOEXCEPT{ return __elems[n]; }

    __ALWAYS_INLINE reference front() __NOEXCEPT{ return __elems[0]; }
    __ALWAYS_INLINE const_reference front() const __NOEXCEPT{ return __elems[0]; }
    __ALWAYS_INLINE reference back() __NOEXCEPT{ return __elems[N > 0 ? N - 1 : 0]; }
    __ALWAYS_INLINE const_reference back() const __NOEXCEPT{ return __elems[N > 0 ? N - 1 : 0]; }

    __ALWAYS_INLINE pointer data() __NOEXCEPT{ return __elems; }
    __ALWAYS_INLINE const_pointer data() const __NOEXCEPT{ return __elems; }
};
template <class T> struct tuple_size;
template <size_t I, class T> class tuple_element;

template <class T, size_t N>
struct tuple_size<array<T, N>> : integral_constant<size_t, N> { };

template <size_t I, class T, size_t N>
class tuple_element<I, array<T, N>>
{
public:
    static_assert(I < N, "Index is out of bounds");
    using type = T;
};

template <size_t I, class T, size_t N>
__ALWAYS_INLINE constexpr T& get(array<T, N>& a) __NOEXCEPT
{
    static_assert(I < N, "Index is out of bounds");
    return a.__elems[I];
}

template <size_t I, class T, size_t N>
__ALWAYS_INLINE constexpr T&& get(array<T, N>&& a) __NOEXCEPT
{
    return cl::move(get<I>(a));
}

template <size_t I, class T, size_t N>
__ALWAYS_INLINE constexpr const T& get(const array<T, N>& a) __NOEXCEPT
{
    static_assert(I < N, "Index is out of bounds");
    return a.__elems[I];
}

}
