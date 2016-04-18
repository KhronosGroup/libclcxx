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
    iterator __ALWAYS_INLINE begin() __NOEXCEPT{ return iterator(__elems); }
    const_iterator __ALWAYS_INLINE begin() const __NOEXCEPT{ return const_iterator(__elems); }
    iterator __ALWAYS_INLINE end() __NOEXCEPT{ return iterator(__elems + N); }
    const_iterator __ALWAYS_INLINE end() const __NOEXCEPT{ return const_iterator(__elems + N); }

    reverse_iterator __ALWAYS_INLINE rbegin() __NOEXCEPT{ return reverse_iterator(end()); }
    const_reverse_iterator __ALWAYS_INLINE rbegin() const __NOEXCEPT{ return const_reverse_iterator(end()); }
    reverse_iterator __ALWAYS_INLINE rend() __NOEXCEPT{ return reverse_iterator(begin()); }
    const_reverse_iterator __ALWAYS_INLINE rend() const __NOEXCEPT{ return const_reverse_iterator(begin()); }

    const_iterator __ALWAYS_INLINE cbegin() const __NOEXCEPT{ return begin(); }
    const_iterator __ALWAYS_INLINE cend() const __NOEXCEPT{ return end(); }
    const_reverse_iterator __ALWAYS_INLINE crbegin() const __NOEXCEPT{ return rbegin(); }
    const_reverse_iterator __ALWAYS_INLINE crend() const __NOEXCEPT{ return rend(); }

        // capacity:
    constexpr size_type size() const __NOEXCEPT{ return N; }
    constexpr size_type max_size() const __NOEXCEPT{ return N; }
    constexpr bool empty() const __NOEXCEPT{ return N == 0; }

        // element access:
    reference operator[](size_type n) __NOEXCEPT{ return __elems[n]; }
    const_reference operator[](size_type n) const __NOEXCEPT{ return __elems[n]; }

    reference __ALWAYS_INLINE front() __NOEXCEPT{ return __elems[0]; }
    const_reference __ALWAYS_INLINE front() const __NOEXCEPT{ return __elems[0]; }
    reference __ALWAYS_INLINE back() __NOEXCEPT{ return __elems[N > 0 ? N - 1 : 0]; }
    const_reference __ALWAYS_INLINE back() const __NOEXCEPT{ return __elems[N > 0 ? N - 1 : 0]; }

    pointer __ALWAYS_INLINE data() __NOEXCEPT{ return __elems; }
    const_pointer __ALWAYS_INLINE data() const __NOEXCEPT{ return __elems; }
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
constexpr T& get(array<T, N>& a) __NOEXCEPT
{
    static_assert(I < N, "Index is out of bounds");
    return a.__elems[I];
}

template <size_t I, class T, size_t N>
constexpr T&& get(array<T, N>&& a) __NOEXCEPT
{
    return cl::move(get<I>(a));
}

template <size_t I, class T, size_t N>
constexpr const T& get(const array<T, N>& a) __NOEXCEPT
{
    static_assert(I < N, "Index is out of bounds");
    return a.__elems[I];
}

}
