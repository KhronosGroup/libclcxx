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
#include <__ocl_memory.h>
#include <__ocl_type_traits_type_properties.h>

namespace cl
{
namespace __details
{
/// \brief Explicit address space storage class for the fundamental and array types
///
template<class T>
struct __data_fundamental
{
    T __elem;

    __ALWAYS_INLINE __data_fundamental() __NOEXCEPT  = default;
    __ALWAYS_INLINE __data_fundamental(const __data_fundamental&) __NOEXCEPT = default;
    __ALWAYS_INLINE __data_fundamental(__data_fundamental&&) __NOEXCEPT = default;
    __ALWAYS_INLINE constexpr __data_fundamental() __CONSTANT_QUALIFIER __NOEXCEPT = default;
    __ALWAYS_INLINE constexpr __data_fundamental(const __data_fundamental&) __CONSTANT_QUALIFIER __NOEXCEPT = default;
    __ALWAYS_INLINE constexpr __data_fundamental(__data_fundamental&&) __CONSTANT_QUALIFIER __NOEXCEPT = default;
    __ALWAYS_INLINE constexpr __data_fundamental() __GLOBAL_QUALIFIER __NOEXCEPT = default;
    __ALWAYS_INLINE constexpr __data_fundamental(const __data_fundamental&) __GLOBAL_QUALIFIER __NOEXCEPT = default;
    __ALWAYS_INLINE constexpr __data_fundamental(__data_fundamental&&) __GLOBAL_QUALIFIER __NOEXCEPT = default;

    __ALWAYS_INLINE __data_fundamental& operator=(const __data_fundamental&)__NOEXCEPT = default;
    __ALWAYS_INLINE __data_fundamental& operator=(__data_fundamental&&)__NOEXCEPT  = default;
    __ALWAYS_INLINE __data_fundamental& operator=(const T &rhs) __NOEXCEPT{ __elem = rhs; return *this; }

    __ALWAYS_INLINE T *operator&() __NOEXCEPT{ return &__elem; }
    __ALWAYS_INLINE const T *operator&() const __NOEXCEPT{ return &__elem; }
    __ALWAYS_INLINE constant_ptr<T> operator&() __CONSTANT_QUALIFIER __NOEXCEPT{ return constant_ptr<T>(&__elem); }
    __ALWAYS_INLINE constant_ptr<const T> operator&() __CONSTANT_QUALIFIER const __NOEXCEPT{ return constant_ptr<const T>(&__elem); }

    __ALWAYS_INLINE operator T&() __NOEXCEPT{ return __elem; }
    __ALWAYS_INLINE operator const T&() const __NOEXCEPT{ return __elem; }
    __ALWAYS_INLINE operator add_constant_t<T>&() __CONSTANT_QUALIFIER __NOEXCEPT{ return __elem; }
    __ALWAYS_INLINE operator const add_constant_t<T>&() __CONSTANT_QUALIFIER const __NOEXCEPT{ return __elem; }

    __ALWAYS_INLINE global_ptr<T> ptr() __GLOBAL_QUALIFIER __NOEXCEPT{ return global_ptr<T>(&__elem); }
    __ALWAYS_INLINE global_ptr<const T> ptr() __GLOBAL_QUALIFIER const __NOEXCEPT{ return global_ptr<const T>(&__elem); }
    __ALWAYS_INLINE local_ptr<T> ptr() __LOCAL_QUALIFIER __NOEXCEPT{ return local_ptr<T>(&__elem); }
    __ALWAYS_INLINE local_ptr<const T> ptr() __LOCAL_QUALIFIER const __NOEXCEPT{ return local_ptr<const T>(&__elem); }
    __ALWAYS_INLINE private_ptr<T> ptr() __PRIVATE_QUALIFIER __NOEXCEPT{ return private_ptr<T>(&__elem); }
    __ALWAYS_INLINE private_ptr<const T> ptr() __PRIVATE_QUALIFIER const __NOEXCEPT{ return private_ptr<const T>(&__elem); }
    __ALWAYS_INLINE constant_ptr<T> ptr() __CONSTANT_QUALIFIER __NOEXCEPT{ return constant_ptr<T>(&__elem); }
    __ALWAYS_INLINE constant_ptr<const T> ptr() __CONSTANT_QUALIFIER const __NOEXCEPT{ return constant_ptr<const T>(&__elem); }
};

/// \brief Explicit address space storage class for the classes
///
template<class T>
struct __data_class : public T
{
    using T::T;
    using T::operator=;

    __ALWAYS_INLINE T *operator&() __NOEXCEPT{ return this; }
    __ALWAYS_INLINE const T *operator&() const __NOEXCEPT{ return this; }
    __ALWAYS_INLINE constant_ptr<T> operator&() __CONSTANT_QUALIFIER __NOEXCEPT{ return constant_ptr<T>(this); }
    __ALWAYS_INLINE constant_ptr<const T>  *operator&() __CONSTANT_QUALIFIER const __NOEXCEPT{ return constant_ptr<const T>(this); }

    __ALWAYS_INLINE operator T&() __NOEXCEPT{ return *this; }
    __ALWAYS_INLINE operator const T&() const __NOEXCEPT{ return *this; }
    __ALWAYS_INLINE operator add_constant_t<T>&() __CONSTANT_QUALIFIER __NOEXCEPT{ return *this; }
    __ALWAYS_INLINE operator const add_constant_t<T>&() __CONSTANT_QUALIFIER const __NOEXCEPT{ return *this; }

    __ALWAYS_INLINE global_ptr<T> ptr() __GLOBAL_QUALIFIER __NOEXCEPT{ return global_ptr<T>(this); }
    __ALWAYS_INLINE global_ptr<const T> ptr() __GLOBAL_QUALIFIER const __NOEXCEPT{ return global_ptr<const T>(this); }
    __ALWAYS_INLINE local_ptr<T> ptr() __LOCAL_QUALIFIER __NOEXCEPT{ return local_ptr<T>(this); }
    __ALWAYS_INLINE local_ptr<const T> ptr() __LOCAL_QUALIFIER const __NOEXCEPT{ return local_ptr<const T>(this); }
    __ALWAYS_INLINE private_ptr<T> ptr() __PRIVATE_QUALIFIER __NOEXCEPT{ return private_ptr<T>(this); }
    __ALWAYS_INLINE private_ptr<const T> ptr() __PRIVATE_QUALIFIER const __NOEXCEPT{ return private_ptr<const T>(this); }
    __ALWAYS_INLINE constant_ptr<T> ptr() __CONSTANT_QUALIFIER __NOEXCEPT{ return constant_ptr<T>(this); }
    __ALWAYS_INLINE constant_ptr<const T> ptr() __CONSTANT_QUALIFIER const __NOEXCEPT{ return constant_ptr<const T>(this); }
};

template<class T>
using __data = conditional_t<is_fundamental<remove_as_t<T>>::value || is_array<remove_as_t<T>>::value, __data_fundamental<T>, __data_class<T>>;

} // namespace __details

} // namespace cl
