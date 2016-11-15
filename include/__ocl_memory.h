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
#include <opencl_type_traits>

namespace cl
{
namespace __details
{

enum __as_ptr_type
{
    __as_ptr_referencable,
    __as_ptr_notrefencable,
    __as_ptr_array
};

template <class T, template <class> class AsModifier, template <class> class Impl, __as_ptr_type ImplType>
class __as_ptr_impl {
    template <class U>
    using add_as_t = typename AsModifier<U>::type;

public:
    typedef T                           element_type;
    typedef ptrdiff_t                   difference_type;
    typedef add_as_t<T>*                pointer;
    typedef add_as_t<add_const_t<T>>*   const_pointer;
    typedef add_as_t<T>&                reference;
    typedef add_as_t<add_const_t<T>>&   const_reference;

    //constructors:
    __ALWAYS_INLINE constexpr __as_ptr_impl() __NOEXCEPT = default;
    __ALWAYS_INLINE explicit __as_ptr_impl(pointer p) __NOEXCEPT: __ptr(p) { }
    __ALWAYS_INLINE __as_ptr_impl(const __as_ptr_impl &r) __NOEXCEPT = default;
    __ALWAYS_INLINE __as_ptr_impl(__as_ptr_impl &&r) __NOEXCEPT = default;
    __ALWAYS_INLINE constexpr __as_ptr_impl(nullptr_t) __NOEXCEPT: __as_ptr_impl() { }

    template <class U, class Guard = enable_if_t<is_convertible<typename Impl<U>::pointer, pointer>::value>>
    __ALWAYS_INLINE __as_ptr_impl(Impl<U> const& other) __NOEXCEPT : __ptr(other.get()) { }

    template <class U, class Guard = enable_if_t<is_convertible<typename Impl<U>::pointer, pointer>::value>>
    __ALWAYS_INLINE __as_ptr_impl(Impl<U>&& other) __NOEXCEPT : __ptr(move(other.get())) { }

    //assignment:
    __ALWAYS_INLINE Impl<T>& operator = (const __as_ptr_impl &r) __NOEXCEPT{ __ptr = r.__ptr; return reinterpret_cast<Impl<T>&>(*this); }
    __ALWAYS_INLINE Impl<T>& operator = (__as_ptr_impl &&r) __NOEXCEPT{ __ptr = cl::move(r.__ptr); return reinterpret_cast<Impl<T>&>(*this); }
    __ALWAYS_INLINE Impl<T>& operator = (pointer r) __NOEXCEPT{ __ptr = r; return reinterpret_cast<Impl<T>&>(*this); }
    __ALWAYS_INLINE Impl<T>& operator = (nullptr_t)__NOEXCEPT{ reset(); return reinterpret_cast<Impl<T>&>(*this); }

    template <class U>
    __ALWAYS_INLINE auto operator =(Impl<U> const& other) __NOEXCEPT
        -> enable_if_t<is_convertible<typename Impl<U>::pointer, pointer>::value, Impl<T>&>
    {
        __ptr = other.get();
        return reinterpret_cast<Impl<T>&>(*this);
    }

    template <class U>
    __ALWAYS_INLINE auto operator =(Impl<U>&& other) __NOEXCEPT
        -> enable_if_t<is_convertible<typename Impl<U>::pointer, pointer>::value, Impl<T>&>
    {
        __ptr = move(other.get());
        return reinterpret_cast<Impl<T>&>(*this);
    }

    //observers:
    __ALWAYS_INLINE reference operator*() const __NOEXCEPT{ return *get(); }
    __ALWAYS_INLINE pointer operator->() const __NOEXCEPT{ return get(); }
    __ALWAYS_INLINE pointer get() const __NOEXCEPT{ return __ptr; }
    __ALWAYS_INLINE explicit operator bool() const __NOEXCEPT{ return get() != nullptr; }

    //modifiers:
    __ALWAYS_INLINE pointer release() __NOEXCEPT{ pointer t = __ptr; __ptr = nullptr; return t; }
    __ALWAYS_INLINE void reset(pointer p = pointer()) __NOEXCEPT{ __ptr = p; }
    __ALWAYS_INLINE void swap(__as_ptr_impl& r) __NOEXCEPT{ cl::swap(__ptr, r.__ptr); }

    //modifiers specific for OpenCL C++:
    __ALWAYS_INLINE Impl<T> operator++(int) __NOEXCEPT{ Impl<T> t(reinterpret_cast<Impl<T>&>(*this)); ++__ptr; return t; }
    __ALWAYS_INLINE Impl<T>& operator++()__NOEXCEPT{ ++__ptr; return reinterpret_cast<Impl<T>&>(*this); }
    __ALWAYS_INLINE Impl<T> operator--(int) __NOEXCEPT{ Impl<T> t(reinterpret_cast<Impl<T>&>(*this)); --__ptr; return t; }
    __ALWAYS_INLINE Impl<T>& operator--()__NOEXCEPT{ --__ptr; return reinterpret_cast<Impl<T>&>(*this); }
    __ALWAYS_INLINE Impl<T>& operator += (difference_type r) __NOEXCEPT{ __ptr += r; return reinterpret_cast<Impl<T>&>(*this); }
    __ALWAYS_INLINE Impl<T>& operator -= (difference_type r) __NOEXCEPT{ __ptr -= r; return reinterpret_cast<Impl<T>&>(*this); }
    __ALWAYS_INLINE Impl<T> operator + (difference_type r) __NOEXCEPT{ Impl<T> t(reinterpret_cast<Impl<T>&>(*this)); t += r; return t; }
    __ALWAYS_INLINE Impl<T> operator - (difference_type r) __NOEXCEPT{ Impl<T> t(reinterpret_cast<Impl<T>&>(*this)); t -= r; return t; }

private:
    add_as_t<T>* __ptr;
};

template <class T, template <class> class AsModifier, template <class> class Impl>
class __as_ptr_impl<T, AsModifier, Impl, __as_ptr_notrefencable> {
    template <class U>
    using add_as_t = typename AsModifier<U>::type;

public:
    typedef T                               element_type;
    typedef ptrdiff_t                       difference_type;
    typedef add_as_t<T>*                    pointer;
    typedef add_as_t<add_constant_t<T>>*    const_pointer;

    //constructors:
    __ALWAYS_INLINE constexpr __as_ptr_impl() __NOEXCEPT = default;
    __ALWAYS_INLINE explicit __as_ptr_impl(pointer p) __NOEXCEPT: __ptr(p) { }
    __ALWAYS_INLINE __as_ptr_impl(const __as_ptr_impl &r) __NOEXCEPT = default;
    __ALWAYS_INLINE __as_ptr_impl(__as_ptr_impl &&r) __NOEXCEPT = default;
    __ALWAYS_INLINE constexpr __as_ptr_impl(nullptr_t) __NOEXCEPT: __as_ptr_impl() { }

    template <class U, class Guard = enable_if_t<is_convertible<typename Impl<U>::pointer, pointer>::value>>
    __ALWAYS_INLINE __as_ptr_impl(Impl<U> const& other) __NOEXCEPT : __ptr(other.get()) { }

    template <class U, class Guard = enable_if_t<is_convertible<typename Impl<U>::pointer, pointer>::value>>
    __ALWAYS_INLINE __as_ptr_impl(Impl<U>&& other) __NOEXCEPT : __ptr(move(other.get())) { }

    //assignment:
    __ALWAYS_INLINE Impl<T>& operator = (const __as_ptr_impl &r) __NOEXCEPT{ __ptr = r.__ptr; return reinterpret_cast<Impl<T>&>(*this); }
    __ALWAYS_INLINE Impl<T>& operator = (__as_ptr_impl &&r) __NOEXCEPT{ __ptr = cl::move(r.__ptr); return reinterpret_cast<Impl<T>&>(*this); }
    __ALWAYS_INLINE Impl<T>& operator = (pointer r) __NOEXCEPT{ __ptr = r; return reinterpret_cast<Impl<T>&>(*this); }
    __ALWAYS_INLINE Impl<T>& operator = (nullptr_t)__NOEXCEPT{ reset(); return reinterpret_cast<Impl<T>&>(*this); }

    template <class U>
    __ALWAYS_INLINE auto operator =(Impl<U> const& other) __NOEXCEPT
        -> enable_if_t<is_convertible<typename Impl<U>::pointer, pointer>::value, Impl<T>&>
    {
        __ptr = other.get();
        return reinterpret_cast<Impl<T>&>(*this);
    }

    template <class U>
    __ALWAYS_INLINE auto operator =(Impl<U>&& other) __NOEXCEPT
        -> enable_if_t<is_convertible<typename Impl<U>::pointer, pointer>::value, Impl<T>&>
    {
        __ptr = move(other.get());
        return reinterpret_cast<Impl<T>&>(*this);
    }

    //observers:
    __ALWAYS_INLINE pointer operator->() const __NOEXCEPT{ return get(); }
    __ALWAYS_INLINE pointer get() const __NOEXCEPT{ return __ptr; }
    __ALWAYS_INLINE explicit operator bool() const __NOEXCEPT{ return get() != nullptr; }

    //modifiers:
    __ALWAYS_INLINE pointer release() __NOEXCEPT{ pointer t = __ptr; __ptr = nullptr; return t; }
    __ALWAYS_INLINE void reset(pointer p = pointer()) __NOEXCEPT{ __ptr = p; }
    __ALWAYS_INLINE void swap(__as_ptr_impl& r) __NOEXCEPT{ cl::swap(__ptr, r.__ptr); }

    //modifiers specific for OpenCL C++:
    __ALWAYS_INLINE Impl<T> operator++(int) __NOEXCEPT{ Impl<T> t(reinterpret_cast<Impl<T>&>(*this)); ++__ptr; return t; }
    __ALWAYS_INLINE Impl<T>& operator++()__NOEXCEPT{ ++__ptr; return reinterpret_cast<Impl<T>&>(*this); }
    __ALWAYS_INLINE Impl<T> operator--(int) __NOEXCEPT{ Impl<T> t(reinterpret_cast<Impl<T>&>(*this)); --__ptr; return t; }
    __ALWAYS_INLINE Impl<T>& operator--()__NOEXCEPT{ --__ptr; return reinterpret_cast<Impl<T>&>(*this); }
    __ALWAYS_INLINE Impl<T>& operator += (difference_type r) __NOEXCEPT{ __ptr += r; return reinterpret_cast<Impl<T>&>(*this); }
    __ALWAYS_INLINE Impl<T>& operator -= (difference_type r) __NOEXCEPT{ __ptr -= r; return reinterpret_cast<Impl<T>&>(*this); }
    __ALWAYS_INLINE Impl<T> operator + (difference_type r) __NOEXCEPT{ Impl<T> t(reinterpret_cast<Impl<T>&>(*this)); t += r; return t; }
    __ALWAYS_INLINE Impl<T> operator - (difference_type r) __NOEXCEPT{ Impl<T> t(reinterpret_cast<Impl<T>&>(*this)); t -= r; return t; }

private:
    add_as_t<T>* __ptr;
};

template <class T, template <class> class AsModifier, template <class> class Impl>
class __as_ptr_impl<T[], AsModifier, Impl, __as_ptr_array> {
    template <class U>
    using add_as_t = typename AsModifier<U>::type;

public:
    typedef T                           element_type;
    typedef ptrdiff_t                   difference_type;
    typedef add_as_t<T>*                pointer;
    typedef add_as_t<add_const_t<T>>*   const_pointer;
    typedef add_as_t<T>&                reference;
    typedef add_as_t<add_const_t<T>>&   const_reference;

    //constructors:
    __ALWAYS_INLINE constexpr __as_ptr_impl() __NOEXCEPT = default;
    __ALWAYS_INLINE explicit __as_ptr_impl(pointer p) __NOEXCEPT: __ptr(p) { }
    __ALWAYS_INLINE __as_ptr_impl(const __as_ptr_impl &r) __NOEXCEPT = default;
    __ALWAYS_INLINE __as_ptr_impl(__as_ptr_impl &&r) __NOEXCEPT = default;
    __ALWAYS_INLINE constexpr __as_ptr_impl(nullptr_t) __NOEXCEPT: __as_ptr_impl() { }

    template <class U, class Guard = enable_if_t<is_pointer<U>::value && is_convertible<remove_pointer_t<U>(*)[], add_as_t<element_type>(*)[]>::value>>
    __ALWAYS_INLINE __as_ptr_impl(U ptr) __NOEXCEPT : __ptr(ptr) { }

    template <class U, class Guard = enable_if_t<is_convertible<add_as_t<typename Impl<U[]>::element_type>(*)[], add_as_t<element_type>(*)[]>::value>>
    __ALWAYS_INLINE __as_ptr_impl(Impl<U[]> const& other) __NOEXCEPT : __ptr(other.get()) { }

    template <class U, class Guard = enable_if_t<is_convertible<add_as_t<typename Impl<U[]>::element_type>(*)[], add_as_t<element_type>(*)[]>::value>>
    __ALWAYS_INLINE __as_ptr_impl(Impl<U[]>&& other) __NOEXCEPT : __ptr(move(other.get())) { }

    //assignment:
    __ALWAYS_INLINE Impl<T>& operator = (const __as_ptr_impl &r) __NOEXCEPT{ __ptr = r.__ptr; return reinterpret_cast<Impl<T>&>(*this); }
    __ALWAYS_INLINE Impl<T>& operator = (__as_ptr_impl &&r) __NOEXCEPT{ __ptr = cl::move(r.__ptr); return reinterpret_cast<Impl<T>&>(*this); }
    __ALWAYS_INLINE Impl<T>& operator = (pointer r) __NOEXCEPT{ __ptr = r; return reinterpret_cast<Impl<T>&>(*this); }
    __ALWAYS_INLINE Impl<T>& operator = (nullptr_t)__NOEXCEPT{ reset(); return reinterpret_cast<Impl<T>&>(*this); }

    template <class U>
    __ALWAYS_INLINE auto operator =(Impl<U[]> const& other) __NOEXCEPT
        -> enable_if_t<is_convertible<add_as_t<typename Impl<U[]>::element_type>(*)[], add_as_t<element_type>(*)[]>::value, Impl<T>&>
    {
        __ptr = other.get();
        return reinterpret_cast<Impl<T>&>(*this);
    }

    template <class U>
    __ALWAYS_INLINE auto operator =(Impl<U[]>&& other) __NOEXCEPT
        -> enable_if_t<is_convertible<add_as_t<typename Impl<U[]>::element_type>(*)[], add_as_t<element_type>(*)[]>::value, Impl<T>&>
    {
        __ptr = move(other.get());
        return reinterpret_cast<Impl<T>&>(*this);
    }

    //observers:
    __ALWAYS_INLINE reference operator[](size_t pos) const __NOEXCEPT{ return get()[pos]; }
    __ALWAYS_INLINE pointer get() const __NOEXCEPT{ return __ptr; }
    __ALWAYS_INLINE explicit operator bool() const __NOEXCEPT{ return get() != nullptr; }

    //modifiers:
    __ALWAYS_INLINE pointer release() __NOEXCEPT{ pointer tmp = __ptr; __ptr = nullptr; return tmp; }
    __ALWAYS_INLINE void reset(pointer p) __NOEXCEPT{ __ptr = p; }
    __ALWAYS_INLINE void reset(nullptr_t p = nullptr) __NOEXCEPT{ reset(pointer()); }
    __ALWAYS_INLINE void swap(__as_ptr_impl& r) __NOEXCEPT{ cl::swap(__ptr, r.__ptr); }

    //modifiers specific for OpenCL C++:
    __ALWAYS_INLINE Impl<T> operator++(int) __NOEXCEPT{ Impl<T> t(reinterpret_cast<Impl<T>&>(*this)); ++__ptr; return t; }
    __ALWAYS_INLINE Impl<T>& operator++()__NOEXCEPT{ ++__ptr; return reinterpret_cast<Impl<T>&>(*this); }
    __ALWAYS_INLINE Impl<T> operator--(int) __NOEXCEPT{ Impl<T> t(reinterpret_cast<Impl<T>&>(*this)); --__ptr; return t; }
    __ALWAYS_INLINE Impl<T>& operator--()__NOEXCEPT{ --__ptr; return reinterpret_cast<Impl<T>&>(*this); }
    __ALWAYS_INLINE Impl<T>& operator += (difference_type r) __NOEXCEPT{ __ptr += r; return reinterpret_cast<Impl<T>&>(*this); }
    __ALWAYS_INLINE Impl<T>& operator -= (difference_type r) __NOEXCEPT{ __ptr -= r; return reinterpret_cast<Impl<T>&>(*this); }
    __ALWAYS_INLINE Impl<T> operator + (difference_type r) __NOEXCEPT{ Impl<T> t(reinterpret_cast<Impl<T>&>(*this)); t += r; return t; }
    __ALWAYS_INLINE Impl<T> operator - (difference_type r) __NOEXCEPT{ Impl<T> t(reinterpret_cast<Impl<T>&>(*this)); t -= r; return t; }

private:
    add_as_t<T>* __ptr;
};

template <class T>
struct __choose_as_ptr_impl_type : public integral_constant<__as_ptr_type, ((is_array<T>::value && extent<T>::value == 0) ? __as_ptr_array : (is_void<T>::value ? __as_ptr_notrefencable : __as_ptr_referencable))> {};

/// \brief Helper class to compute a size of local memory. The class is used by enqueue_kernel methods
///
template <class T>
struct __local_ptr_size
{
    explicit constexpr __local_ptr_size(size_t size) : my_size(size) {}
    constexpr operator size_t() { return my_size; }

    size_t my_size;
};

} // __details

/// \brief Explicit global address space pointer class
///
/// The explicit OpenCL AS pointer class provides similar interface to std::unique_ptr.
/// The class is needed to preserve the address space information without
/// extending C++ language.
template <class T>
class global_ptr : public __details::__as_ptr_impl<T, add_global, global_ptr, __details::__choose_as_ptr_impl_type<T>::value> {
    using __parent = __details::__as_ptr_impl<T, add_global, cl::global_ptr, __details::__choose_as_ptr_impl_type<T>::value>;
public:
    using __parent::__parent;
    using __parent::operator =;
};

/// \brief Non-member address space pointer compare operators.
///
template<class T, class U>
__ALWAYS_INLINE bool operator == (const global_ptr<T> &a, const global_ptr<U> &b) __NOEXCEPT{ return a.get() == b.get(); }
template<class T, class U>
__ALWAYS_INLINE bool operator != (const global_ptr<T> &a, const global_ptr<U> &b) __NOEXCEPT{ return !(a == b); }
template<class T, class U>
__ALWAYS_INLINE bool operator<(const global_ptr<T> &a, const global_ptr<U> &b) __NOEXCEPT{ return a.get() < b.get(); } //TODO: cl::less should be used
template<class T, class U>
__ALWAYS_INLINE bool operator>(const global_ptr<T> &a, const global_ptr<U> &b) __NOEXCEPT{ return b < a; }
template<class T, class U>
__ALWAYS_INLINE bool operator <= (const global_ptr<T> &a, const global_ptr<U> &b) __NOEXCEPT{ return !(b < a); }
template<class T, class U>
__ALWAYS_INLINE bool operator >= (const global_ptr<T> &a, const global_ptr<U> &b) __NOEXCEPT{ return !(a < b); }

template<class T>
__ALWAYS_INLINE bool operator == (const global_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !x; }
template<class T>
__ALWAYS_INLINE bool operator == (nullptr_t, const global_ptr<T> &x) __NOEXCEPT{ return !x; }
template<class T>
__ALWAYS_INLINE bool operator != (const global_ptr<T> &x, nullptr_t) __NOEXCEPT{ return (bool)x; }
template<class T>
__ALWAYS_INLINE bool operator != (nullptr_t, const global_ptr<T> &x) __NOEXCEPT{ return (bool)x; }
template<class T>
__ALWAYS_INLINE bool operator<(const global_ptr<T> &x, nullptr_t) __NOEXCEPT{ return x.get() < nullptr; } //TODO: cl:less should be used
template<class T>
__ALWAYS_INLINE bool operator<(nullptr_t, const global_ptr<T> &x) __NOEXCEPT{ return nullptr < x.get(); } //TODO: cl:less should be used
template<class T>
__ALWAYS_INLINE bool operator>(const global_ptr<T> &x, nullptr_t) __NOEXCEPT{ return nullptr < x; }
template<class T>
__ALWAYS_INLINE bool operator>(nullptr_t, const global_ptr<T> &x) __NOEXCEPT{ return x < nullptr; }
template<class T>
__ALWAYS_INLINE bool operator <= (const global_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !(nullptr < x); }
template<class T>
__ALWAYS_INLINE bool operator <= (nullptr_t, const global_ptr<T> &x) __NOEXCEPT{ return !(x < nullptr); }
template<class T>
__ALWAYS_INLINE bool operator >= (const global_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !(x < nullptr); }
template<class T>
__ALWAYS_INLINE bool operator >= (nullptr_t, const global_ptr<T> &x) __NOEXCEPT{ return !(nullptr < x); }

/// \brief Non-member address space pointer swap function
///
template<class T>
__ALWAYS_INLINE void swap(global_ptr<T>& a, global_ptr<T>& b) __NOEXCEPT { a.swap(b); }

/// \brief Explicit local address space pointer class
///
/// The explicit OpenCL AS pointer class provides similar interface to std::unique_ptr.
/// The class is needed to preserve the address space information without
/// extending C++ language.
template <class T>
class local_ptr : public __details::__as_ptr_impl<T, add_local, local_ptr, __details::__choose_as_ptr_impl_type<T>::value> {
    using __parent = __details::__as_ptr_impl<T, add_local, cl::local_ptr, __details::__choose_as_ptr_impl_type<T>::value>;
public:
    using __parent::__parent;
    using __parent::operator =;

    using size_type = __details::__local_ptr_size<T>;
};

/// \brief Non-member address space pointer compare operators.
///
template<class T, class U>
__ALWAYS_INLINE bool operator == (const local_ptr<T> &a, const local_ptr<U> &b) __NOEXCEPT{ return a.get() == b.get(); }
template<class T, class U>
__ALWAYS_INLINE bool operator != (const local_ptr<T> &a, const local_ptr<U> &b) __NOEXCEPT{ return !(a == b); }
template<class T, class U>
__ALWAYS_INLINE bool operator<(const local_ptr<T> &a, const local_ptr<U> &b) __NOEXCEPT{ return a.get() < b.get(); } //TODO: cl::less should be used
template<class T, class U>
__ALWAYS_INLINE bool operator>(const local_ptr<T> &a, const local_ptr<U> &b) __NOEXCEPT{ return b < a; }
template<class T, class U>
__ALWAYS_INLINE bool operator <= (const local_ptr<T> &a, const local_ptr<U> &b) __NOEXCEPT{ return !(b < a); }
template<class T, class U>
__ALWAYS_INLINE bool operator >= (const local_ptr<T> &a, const local_ptr<U> &b) __NOEXCEPT{ return !(a < b); }

template<class T>
__ALWAYS_INLINE bool operator == (const local_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !x; }
template<class T>
__ALWAYS_INLINE bool operator == (nullptr_t, const local_ptr<T> &x) __NOEXCEPT{ return !x; }
template<class T>
__ALWAYS_INLINE bool operator != (const local_ptr<T> &x, nullptr_t) __NOEXCEPT{ return (bool)x; }
template<class T>
__ALWAYS_INLINE bool operator != (nullptr_t, const local_ptr<T> &x) __NOEXCEPT{ return (bool)x; }
template<class T>
__ALWAYS_INLINE bool operator<(const local_ptr<T> &x, nullptr_t) __NOEXCEPT{ return x.get() < nullptr; } //TODO: cl:less should be used
template<class T>
__ALWAYS_INLINE bool operator<(nullptr_t, const local_ptr<T> &x) __NOEXCEPT{ return nullptr < x.get(); } //TODO: cl:less should be used
template<class T>
__ALWAYS_INLINE bool operator>(const local_ptr<T> &x, nullptr_t) __NOEXCEPT{ return nullptr < x; }
template<class T>
__ALWAYS_INLINE bool operator>(nullptr_t, const local_ptr<T> &x) __NOEXCEPT{ return x < nullptr; }
template<class T>
__ALWAYS_INLINE bool operator <= (const local_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !(nullptr < x); }
template<class T>
__ALWAYS_INLINE bool operator <= (nullptr_t, const local_ptr<T> &x) __NOEXCEPT{ return !(x < nullptr); }
template<class T>
__ALWAYS_INLINE bool operator >= (const local_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !(x < nullptr); }
template<class T>
__ALWAYS_INLINE bool operator >= (nullptr_t, const local_ptr<T> &x) __NOEXCEPT{ return !(nullptr < x); }

/// \brief Non-member address space pointer swap function
///
template<class T>
__ALWAYS_INLINE void swap(local_ptr<T>& a, local_ptr<T>& b) __NOEXCEPT { a.swap(b); }

/// \brief Explicit constant address space pointer class
///
/// The explicit OpenCL AS pointer class provides similar interface to std::unique_ptr.
/// The class is needed to preserve the address space information without
/// extending C++ language.
template <class T>
class constant_ptr : public __details::__as_ptr_impl<T, add_constant, constant_ptr, __details::__choose_as_ptr_impl_type<T>::value> {
    using __parent = __details::__as_ptr_impl<T, add_constant, cl::constant_ptr, __details::__choose_as_ptr_impl_type<T>::value>;
public:
    using __parent::__parent;
    using __parent::operator =;
};

/// \brief Non-member address space pointer compare operators.
///
template<class T, class U>
__ALWAYS_INLINE bool operator == (const constant_ptr<T> &a, const constant_ptr<U> &b) __NOEXCEPT{ return a.get() == b.get(); }
template<class T, class U>
__ALWAYS_INLINE bool operator != (const constant_ptr<T> &a, const constant_ptr<U> &b) __NOEXCEPT{ return !(a == b); }
template<class T, class U>
__ALWAYS_INLINE bool operator<(const constant_ptr<T> &a, const constant_ptr<U> &b) __NOEXCEPT{ return a.get() < b.get(); } //TODO: cl::less should be used
template<class T, class U>
__ALWAYS_INLINE bool operator>(const constant_ptr<T> &a, const constant_ptr<U> &b) __NOEXCEPT{ return b < a; }
template<class T, class U>
__ALWAYS_INLINE bool operator <= (const constant_ptr<T> &a, const constant_ptr<U> &b) __NOEXCEPT{ return !(b < a); }
template<class T, class U>
__ALWAYS_INLINE bool operator >= (const constant_ptr<T> &a, const constant_ptr<U> &b) __NOEXCEPT{ return !(a < b); }

template<class T>
__ALWAYS_INLINE bool operator == (const constant_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !x; }
template<class T>
__ALWAYS_INLINE bool operator == (nullptr_t, const constant_ptr<T> &x) __NOEXCEPT{ return !x; }
template<class T>
__ALWAYS_INLINE bool operator != (const constant_ptr<T> &x, nullptr_t) __NOEXCEPT{ return (bool)x; }
template<class T>
__ALWAYS_INLINE bool operator != (nullptr_t, const constant_ptr<T> &x) __NOEXCEPT{ return (bool)x; }
template<class T>
__ALWAYS_INLINE bool operator<(const constant_ptr<T> &x, nullptr_t) __NOEXCEPT{ return x.get() < nullptr; } //TODO: cl:less should be used
template<class T>
__ALWAYS_INLINE bool operator<(nullptr_t, const constant_ptr<T> &x) __NOEXCEPT{ return nullptr < x.get(); } //TODO: cl:less should be used
template<class T>
__ALWAYS_INLINE bool operator>(const constant_ptr<T> &x, nullptr_t) __NOEXCEPT{ return nullptr < x; }
template<class T>
__ALWAYS_INLINE bool operator>(nullptr_t, const constant_ptr<T> &x) __NOEXCEPT{ return x < nullptr; }
template<class T>
__ALWAYS_INLINE bool operator <= (const constant_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !(nullptr < x); }
template<class T>
__ALWAYS_INLINE bool operator <= (nullptr_t, const constant_ptr<T> &x) __NOEXCEPT{ return !(x < nullptr); }
template<class T>
__ALWAYS_INLINE bool operator >= (const constant_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !(x < nullptr); }
template<class T>
__ALWAYS_INLINE bool operator >= (nullptr_t, const constant_ptr<T> &x) __NOEXCEPT{ return !(nullptr < x); }

/// \brief Non-member address space pointer swap function
///
template<class T>
__ALWAYS_INLINE void swap(constant_ptr<T>& a, constant_ptr<T>& b) __NOEXCEPT { a.swap(b); }

/// \brief Explicit private address space pointer class
///
/// The explicit OpenCL AS pointer class provides similar interface to std::unique_ptr.
/// The class is needed to preserve the address space information without
/// extending C++ language.
template <class T>
class private_ptr : public __details::__as_ptr_impl<T, add_private, private_ptr, __details::__choose_as_ptr_impl_type<T>::value> {
    using __parent = __details::__as_ptr_impl<T, add_private, cl::private_ptr, __details::__choose_as_ptr_impl_type<T>::value>;
public:
    using __parent::__parent;
    using __parent::operator =;
};

/// \brief Non-member address space pointer compare operators.
///
template<class T, class U>
__ALWAYS_INLINE bool operator == (const private_ptr<T> &a, const private_ptr<U> &b) __NOEXCEPT{ return a.get() == b.get(); }
template<class T, class U>
__ALWAYS_INLINE bool operator != (const private_ptr<T> &a, const private_ptr<U> &b) __NOEXCEPT{ return !(a == b); }
template<class T, class U>
__ALWAYS_INLINE bool operator<(const private_ptr<T> &a, const private_ptr<U> &b) __NOEXCEPT{ return a.get() < b.get(); } //TODO: cl::less should be used
template<class T, class U>
__ALWAYS_INLINE bool operator>(const private_ptr<T> &a, const private_ptr<U> &b) __NOEXCEPT{ return b < a; }
template<class T, class U>
__ALWAYS_INLINE bool operator <= (const private_ptr<T> &a, const private_ptr<U> &b) __NOEXCEPT{ return !(b < a); }
template<class T, class U>
__ALWAYS_INLINE bool operator >= (const private_ptr<T> &a, const private_ptr<U> &b) __NOEXCEPT{ return !(a < b); }

template<class T>
__ALWAYS_INLINE bool operator == (const private_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !x; }
template<class T>
__ALWAYS_INLINE bool operator == (nullptr_t, const private_ptr<T> &x) __NOEXCEPT{ return !x; }
template<class T>
__ALWAYS_INLINE bool operator != (const private_ptr<T> &x, nullptr_t) __NOEXCEPT{ return (bool)x; }
template<class T>
__ALWAYS_INLINE bool operator != (nullptr_t, const private_ptr<T> &x) __NOEXCEPT{ return (bool)x; }
template<class T>
__ALWAYS_INLINE bool operator<(const private_ptr<T> &x, nullptr_t) __NOEXCEPT{ return x.get() < nullptr; } //TODO: cl:less should be used
template<class T>
__ALWAYS_INLINE bool operator<(nullptr_t, const private_ptr<T> &x) __NOEXCEPT{ return nullptr < x.get(); } //TODO: cl:less should be used
template<class T>
__ALWAYS_INLINE bool operator>(const private_ptr<T> &x, nullptr_t) __NOEXCEPT{ return nullptr < x; }
template<class T>
__ALWAYS_INLINE bool operator>(nullptr_t, const private_ptr<T> &x) __NOEXCEPT{ return x < nullptr; }
template<class T>
__ALWAYS_INLINE bool operator <= (const private_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !(nullptr < x); }
template<class T>
__ALWAYS_INLINE bool operator <= (nullptr_t, const private_ptr<T> &x) __NOEXCEPT{ return !(x < nullptr); }
template<class T>
__ALWAYS_INLINE bool operator >= (const private_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !(x < nullptr); }
template<class T>
__ALWAYS_INLINE bool operator >= (nullptr_t, const private_ptr<T> &x) __NOEXCEPT{ return !(nullptr < x); }

/// \brief Non-member address space pointer swap function
///
template<class T>
__ALWAYS_INLINE void swap(private_ptr<T>& a, private_ptr<T>& b) __NOEXCEPT { a.swap(b); }

namespace __details
{

template <template <class> class AsWrapper>
struct __asptr_cast_maker
{
    template <class SrcT, class DstT>
    __ALWAYS_INLINE static auto __make_static_cast(AsWrapper<SrcT> const& r)
    {
        return AsWrapper<DstT>{ //3. re-wrap cast result
            static_cast<typename AsWrapper<DstT>::pointer>( //2. cast content to a new type
                r.get() //1. remove wrapper
            )
        };
    }

    template <class SrcT, class DstT>
    __ALWAYS_INLINE static auto __make_reinterpret_cast(AsWrapper<SrcT> const& r)
    {
        return AsWrapper<DstT>{
            reinterpret_cast<typename AsWrapper<DstT>::pointer>(
                r.get()
            )
        };
    }
};

} // namespace __details

template <class T, class U> __ALWAYS_INLINE local_ptr<T> static_asptr_cast(local_ptr<U> const& ptr) __NOEXCEPT { return __details::__asptr_cast_maker<local_ptr>::__make_static_cast<U, T>(ptr); }
template <class T, class U> __ALWAYS_INLINE global_ptr<T> static_asptr_cast(global_ptr<U> const& ptr) __NOEXCEPT { return __details::__asptr_cast_maker<global_ptr>::__make_static_cast<U, T>(ptr); }
template <class T, class U> __ALWAYS_INLINE constant_ptr<T> static_asptr_cast(constant_ptr<U> const& ptr) __NOEXCEPT { return __details::__asptr_cast_maker<constant_ptr>::__make_static_cast<U, T>(ptr); }
template <class T, class U> __ALWAYS_INLINE private_ptr<T> static_asptr_cast(private_ptr<U> const& ptr) __NOEXCEPT { return __details::__asptr_cast_maker<private_ptr>::__make_static_cast<U, T>(ptr); }

template <class T, class U> __ALWAYS_INLINE local_ptr<T> reinterpret_asptr_cast(local_ptr<U> const& ptr) __NOEXCEPT { return __details::__asptr_cast_maker<local_ptr>::__make_reinterpret_cast<U, T>(ptr); }
template <class T, class U> __ALWAYS_INLINE global_ptr<T> reinterpret_asptr_cast(global_ptr<U> const& ptr) __NOEXCEPT { return __details::__asptr_cast_maker<global_ptr>::__make_reinterpret_cast<U, T>(ptr); }
template <class T, class U> __ALWAYS_INLINE constant_ptr<T> reinterpret_asptr_cast(constant_ptr<U> const& ptr) __NOEXCEPT { return __details::__asptr_cast_maker<constant_ptr>::__make_reinterpret_cast<U, T>(ptr); }
template <class T, class U> __ALWAYS_INLINE private_ptr<T> reinterpret_asptr_cast(private_ptr<U> const& ptr) __NOEXCEPT { return __details::__asptr_cast_maker<private_ptr>::__make_reinterpret_cast<U, T>(ptr); }

}