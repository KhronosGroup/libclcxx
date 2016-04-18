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

namespace cl
{
namespace __details
{
/// \brief Helper class to compute a size of local memory. The class is used by enqueue_kernel methods
///
template <class T>
struct __local_ptr_size
{
    explicit constexpr __local_ptr_size(size_t size) : my_size(size) {}
    operator size_t() { return my_size; }

    size_t my_size;
};

} // __details

/// \brief Explicit global address space pointer class
///
/// The explicit OpenCL AS pointer class provides similar interface to std::unique_ptr.
/// The class is needed to preserve the address space information without
/// extending C++ language.
template <class T>
class global_ptr {
public:
    //types:
    typedef T                       element_type;
    typedef ptrdiff_t               difference_type;
    typedef add_global_t<T>*        pointer;
    typedef add_global_t<const T>*  const_pointer;
    typedef add_global_t<T>&        reference;
    typedef add_global_t<const T>&  const_reference;

    //constructors:
    constexpr __ALWAYS_INLINE global_ptr() __NOEXCEPT = default;
    explicit __ALWAYS_INLINE global_ptr(pointer p) __NOEXCEPT: __ptr(p) { };
    __ALWAYS_INLINE global_ptr(const global_ptr &r) __NOEXCEPT = default;
    __ALWAYS_INLINE global_ptr(global_ptr &&r) __NOEXCEPT = default;
    constexpr __ALWAYS_INLINE global_ptr(nullptr_t) __NOEXCEPT: global_ptr() { };

    //assignment:
    global_ptr& __ALWAYS_INLINE operator = (const global_ptr &r) __NOEXCEPT{ __ptr = r.__ptr; return *this; }
    global_ptr& __ALWAYS_INLINE operator = (global_ptr &&r) __NOEXCEPT{ __ptr = cl::move(r.__ptr); return *this; }
    global_ptr& __ALWAYS_INLINE operator = (pointer r) __NOEXCEPT{ __ptr = r; return *this; }
    global_ptr& __ALWAYS_INLINE operator = (nullptr_t)__NOEXCEPT{ reset(); return *this; }

    //observers:
    add_lvalue_reference_t<add_global_t<T>> __ALWAYS_INLINE operator*() const __NOEXCEPT{ return *get(); }
    pointer __ALWAYS_INLINE operator->() const __NOEXCEPT{ return get(); }
    pointer __ALWAYS_INLINE get() const __NOEXCEPT{ return __ptr; }
    explicit __ALWAYS_INLINE operator bool() const __NOEXCEPT{ return get() != nullptr; }

    //modifiers:
    pointer __ALWAYS_INLINE release() __NOEXCEPT{ pointer t = __ptr; __ptr = nullptr; return t; }
    void __ALWAYS_INLINE reset(pointer p = pointer()) __NOEXCEPT{ __ptr = p; }
    void __ALWAYS_INLINE swap(global_ptr& r) __NOEXCEPT{ cl::swap(*this, r); }

    //modifiers specific for OpenCL C++:
    global_ptr __ALWAYS_INLINE operator++() __NOEXCEPT{ global_ptr t(*this); ++__ptr; return t; }
    global_ptr& __ALWAYS_INLINE operator++(int)__NOEXCEPT{ __ptr++; return *this; }
    global_ptr __ALWAYS_INLINE operator--() __NOEXCEPT{ global_ptr t(*this); --__ptr; return t; }
    global_ptr& __ALWAYS_INLINE operator--(int)__NOEXCEPT{ --__ptr; return *this; }
    global_ptr& __ALWAYS_INLINE operator += (difference_type r) __NOEXCEPT{ __ptr += r; return *this; }
    global_ptr& __ALWAYS_INLINE operator -= (difference_type r) __NOEXCEPT{ __ptr -= r; return *this; }
    global_ptr __ALWAYS_INLINE operator + (difference_type r) __NOEXCEPT{ global_ptr t(*this); t += r; return t; }
    global_ptr __ALWAYS_INLINE operator - (difference_type r) __NOEXCEPT{ global_ptr t(*this); t -= r; return t; }

private:
    add_global_t<T>* __ptr;
};

/// \brief Explicit address space pointer class specialization for arrays
///
template <class T>
class global_ptr<T[]> {
public:
    typedef T                       element_type;
    typedef ptrdiff_t               difference_type;
    typedef add_global_t<T>*        pointer;
    typedef add_global_t<const T>*  const_pointer;
    typedef add_global_t<T>&        reference;
    typedef add_global_t<const T>&  const_reference;

    //constructors:
    constexpr __ALWAYS_INLINE global_ptr() __NOEXCEPT = default;
    explicit __ALWAYS_INLINE global_ptr(pointer p) __NOEXCEPT: __ptr(p) { };
    __ALWAYS_INLINE global_ptr(const global_ptr &r) __NOEXCEPT = default;
    __ALWAYS_INLINE global_ptr(global_ptr &&r) __NOEXCEPT = default;
    constexpr __ALWAYS_INLINE global_ptr(nullptr_t) __NOEXCEPT: global_ptr() { };

    //assignment:
    global_ptr& __ALWAYS_INLINE operator = (const global_ptr &r) __NOEXCEPT{ __ptr = r.__ptr; return *this; }
    global_ptr& __ALWAYS_INLINE operator = (global_ptr &&r) __NOEXCEPT{ __ptr = cl::move(r.__ptr); return *this; }
    global_ptr& __ALWAYS_INLINE operator = (pointer r) __NOEXCEPT{ __ptr = r; return *this; }
    global_ptr& __ALWAYS_INLINE operator = (nullptr_t)__NOEXCEPT{ reset(); return *this; }

    //observers:
    reference __ALWAYS_INLINE operator[](size_t pos) const __NOEXCEPT{ return get()[pos]; }
    pointer __ALWAYS_INLINE get() const __NOEXCEPT{ return __ptr; }
    explicit __ALWAYS_INLINE operator bool() const __NOEXCEPT{ return get() != nullptr; }

    //modifiers:
    pointer __ALWAYS_INLINE release() __NOEXCEPT{ pointer tmp = __ptr; __ptr = nullptr; return tmp; }
    void __ALWAYS_INLINE reset(pointer p) __NOEXCEPT{ __ptr = p; }
    void __ALWAYS_INLINE reset(nullptr_t p = nullptr) __NOEXCEPT{ reset(pointer()); }
    void __ALWAYS_INLINE swap(global_ptr& r) __NOEXCEPT{ cl::swap(*this, r); }

    //modifiers specific for OpenCL C++:
    global_ptr __ALWAYS_INLINE operator++() __NOEXCEPT{ global_ptr t(*this); ++__ptr; return t; }
    global_ptr __ALWAYS_INLINE operator++(int)__NOEXCEPT{ __ptr++; return *this; }
    global_ptr __ALWAYS_INLINE operator--() __NOEXCEPT{ global_ptr t(*this); --__ptr; return t; }
    global_ptr __ALWAYS_INLINE operator--(int)__NOEXCEPT{ --__ptr; return *this; }
    global_ptr __ALWAYS_INLINE operator += (difference_type r) __NOEXCEPT{ __ptr += r; return *this; }
    global_ptr __ALWAYS_INLINE operator -= (difference_type r) __NOEXCEPT{ __ptr -= r; return *this; }
    global_ptr __ALWAYS_INLINE operator + (difference_type r) __NOEXCEPT{ global_ptr t(*this); t += r; return t; }
    global_ptr __ALWAYS_INLINE operator - (difference_type r) __NOEXCEPT{ global_ptr t(*this); t -= r; return t; }

private:
    add_global_t<T>* __ptr;
};

/// \brief Non-member address space pointer compare operators.
///
template<class T>
bool __ALWAYS_INLINE operator == (const global_ptr<T> &a, const global_ptr<T> &b) __NOEXCEPT{ return a.get() == b.get(); }
template<class T>
bool __ALWAYS_INLINE operator != (const global_ptr<T> &a, const global_ptr<T> &b) __NOEXCEPT{ return !(a == b); }
template<class T>
bool __ALWAYS_INLINE operator<(const global_ptr<T> &a, const global_ptr<T> &b) __NOEXCEPT{ return a.get() < b.get(); } //TODO: cl::less should be used
template<class T>
bool __ALWAYS_INLINE operator>(const global_ptr<T> &a, const global_ptr<T> &b) __NOEXCEPT{ return b < a; }
template<class T>
bool __ALWAYS_INLINE operator <= (const global_ptr<T> &a, const global_ptr<T> &b) __NOEXCEPT{ return !(b < a); }
template<class T>
bool __ALWAYS_INLINE operator >= (const global_ptr<T> &a, const global_ptr<T> &b) __NOEXCEPT{ return !(a < b); }

template<class T>
bool __ALWAYS_INLINE operator == (const global_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !x; }
template<class T>
bool __ALWAYS_INLINE operator == (nullptr_t, const global_ptr<T> &x) __NOEXCEPT{ return !x; }
template<class T>
bool __ALWAYS_INLINE operator != (const global_ptr<T> &x, nullptr_t) __NOEXCEPT{ return (bool)x; }
template<class T>
bool __ALWAYS_INLINE operator != (nullptr_t, const global_ptr<T> &x) __NOEXCEPT{ return (bool)x; }
template<class T>
bool __ALWAYS_INLINE operator<(const global_ptr<T> &x, nullptr_t) __NOEXCEPT{ return x.get() < nullptr; } //TODO: cl:less should be used
template<class T>
bool __ALWAYS_INLINE operator<(nullptr_t, const global_ptr<T> &x) __NOEXCEPT{ return nullptr < x.get(); } //TODO: cl:less should be used
template<class T>
bool __ALWAYS_INLINE operator>(const global_ptr<T> &x, nullptr_t) __NOEXCEPT{ return nullptr < x; }
template<class T>
bool __ALWAYS_INLINE operator>(nullptr_t, const global_ptr<T> &x) __NOEXCEPT{ return x < nullptr; }
template<class T>
bool __ALWAYS_INLINE operator <= (const global_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !(nullptr < x); }
template<class T>
bool __ALWAYS_INLINE operator <= (nullptr_t, const global_ptr<T> &x) __NOEXCEPT{ return !(x < nullptr); }
template<class T>
bool __ALWAYS_INLINE operator >= (const global_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !(x < nullptr); }
template<class T>
bool __ALWAYS_INLINE operator >= (nullptr_t, const global_ptr<T> &x) __NOEXCEPT{ return !(nullptr < x); }

/// \brief Non-member address space pointer swap function
///
template<class T>
void __ALWAYS_INLINE swap(global_ptr<T>& a, global_ptr<T>& b) __NOEXCEPT { a.swap(b); }

/// \brief Explicit local address space pointer class
///
/// The explicit OpenCL AS pointer class provides similar interface to std::unique_ptr.
/// The class is needed to preserve the address space information without
/// extending C++ language.
template <class T>
class local_ptr {
public:
    //types:
    typedef T                      element_type;
    typedef ptrdiff_t              difference_type;
    typedef add_local_t<T>*        pointer;
    typedef add_local_t<const T>*  const_pointer;
    typedef add_local_t<T>&        reference;
    typedef add_local_t<const T>&  const_reference;

    typedef __details::__local_ptr_size<T> size_type;

    //constructors:
    constexpr __ALWAYS_INLINE local_ptr() __NOEXCEPT = default;
    explicit __ALWAYS_INLINE local_ptr(pointer p) __NOEXCEPT: __ptr(p) { };
    __ALWAYS_INLINE local_ptr(const local_ptr &r) __NOEXCEPT = default;
    __ALWAYS_INLINE local_ptr(local_ptr &&r) __NOEXCEPT = default;
    constexpr __ALWAYS_INLINE local_ptr(nullptr_t) __NOEXCEPT: local_ptr() { };

    //assignment:
    local_ptr& __ALWAYS_INLINE operator = (const local_ptr &r) __NOEXCEPT{ __ptr = r.__ptr; return *this; }
    local_ptr& __ALWAYS_INLINE operator = (local_ptr &&r) __NOEXCEPT{ __ptr = cl::move(r.__ptr); return *this; }
    local_ptr& __ALWAYS_INLINE operator = (pointer r) __NOEXCEPT{ __ptr = r; return *this; }
    local_ptr& __ALWAYS_INLINE operator = (nullptr_t)__NOEXCEPT{ reset(); return *this; }

    //observers:
    add_lvalue_reference_t<add_local_t<T>> __ALWAYS_INLINE operator*() const __NOEXCEPT{ return *get(); }
    pointer __ALWAYS_INLINE operator->() const __NOEXCEPT{ return get(); }
    pointer __ALWAYS_INLINE get() const __NOEXCEPT{ return __ptr; }
    explicit __ALWAYS_INLINE operator bool() const __NOEXCEPT{ return get() != nullptr; }

    //modifiers:
    pointer __ALWAYS_INLINE release() __NOEXCEPT{ pointer t = __ptr; __ptr = nullptr; return t; }
    void __ALWAYS_INLINE reset(pointer p = pointer()) __NOEXCEPT{ __ptr = p; }
    void __ALWAYS_INLINE swap(local_ptr& r) __NOEXCEPT{ cl::swap(*this, r); }

    //modifiers specific for OpenCL C++:
    local_ptr __ALWAYS_INLINE operator++() __NOEXCEPT{ local_ptr t(*this); ++__ptr; return t; }
    local_ptr& __ALWAYS_INLINE operator++(int)__NOEXCEPT{ __ptr++; return *this; }
    local_ptr __ALWAYS_INLINE operator--() __NOEXCEPT{ local_ptr t(*this); --__ptr; return t; }
    local_ptr& __ALWAYS_INLINE operator--(int)__NOEXCEPT{ --__ptr; return *this; }
    local_ptr& __ALWAYS_INLINE operator += (difference_type r) __NOEXCEPT{ __ptr += r; return *this; }
    local_ptr& __ALWAYS_INLINE operator -= (difference_type r) __NOEXCEPT{ __ptr -= r; return *this; }
    local_ptr __ALWAYS_INLINE operator + (difference_type r) __NOEXCEPT{ local_ptr t(*this); t += r; return t; }
    local_ptr __ALWAYS_INLINE operator - (difference_type r) __NOEXCEPT{ local_ptr t(*this); t -= r; return t; }

private:
    add_local_t<T>* __ptr;
};

/// \brief Explicit address space pointer class specialization for arrays
///
template <class T>
class local_ptr<T[]> {
public:
    typedef T                      element_type;
    typedef ptrdiff_t              difference_type;
    typedef add_local_t<T>*        pointer;
    typedef add_local_t<const T>*  const_pointer;
    typedef add_local_t<T>&        reference;
    typedef add_local_t<const T>&  const_reference;

    typedef __details::__local_ptr_size<T> size_type;

    //constructors:
    constexpr __ALWAYS_INLINE local_ptr() __NOEXCEPT = default;
    explicit __ALWAYS_INLINE local_ptr(pointer p) __NOEXCEPT: __ptr(p) { };
    __ALWAYS_INLINE local_ptr(const local_ptr &r) __NOEXCEPT = default;
    __ALWAYS_INLINE local_ptr(local_ptr &&r) __NOEXCEPT = default;
    constexpr __ALWAYS_INLINE local_ptr(nullptr_t) __NOEXCEPT: local_ptr() { };

    //assignment:
    local_ptr& __ALWAYS_INLINE operator = (const local_ptr &r) __NOEXCEPT{ __ptr = r.__ptr; return *this; }
    local_ptr& __ALWAYS_INLINE operator = (local_ptr &&r) __NOEXCEPT{ __ptr = cl::move(r.__ptr); return *this; }
    local_ptr& __ALWAYS_INLINE operator = (pointer r) __NOEXCEPT{ __ptr = r; return *this; }
    local_ptr& __ALWAYS_INLINE operator = (nullptr_t)__NOEXCEPT{ reset(); return *this; }

    //observers:
    reference __ALWAYS_INLINE operator[](size_t pos) const __NOEXCEPT{ return get()[pos]; }
    pointer __ALWAYS_INLINE get() const __NOEXCEPT{ return __ptr; }
    explicit __ALWAYS_INLINE operator bool() const __NOEXCEPT{ return get() != nullptr; }

    //modifiers:
    pointer __ALWAYS_INLINE release() __NOEXCEPT{ pointer tmp = __ptr; __ptr = nullptr; return tmp; }
    void __ALWAYS_INLINE reset(pointer p) __NOEXCEPT{ __ptr = p; }
    void __ALWAYS_INLINE reset(nullptr_t p = nullptr) __NOEXCEPT{ reset(pointer()); }
    void __ALWAYS_INLINE swap(local_ptr& r) __NOEXCEPT{ cl::swap(*this, r); }

    //modifiers specific for OpenCL C++:
    local_ptr __ALWAYS_INLINE operator++() __NOEXCEPT{ local_ptr t(*this); ++__ptr; return t; }
    local_ptr __ALWAYS_INLINE operator++(int)__NOEXCEPT{ __ptr++; return *this; }
    local_ptr __ALWAYS_INLINE operator--() __NOEXCEPT{ local_ptr t(*this); --__ptr; return t; }
    local_ptr __ALWAYS_INLINE operator--(int)__NOEXCEPT{ --__ptr; return *this; }
    local_ptr __ALWAYS_INLINE operator += (difference_type r) __NOEXCEPT{ __ptr += r; return *this; }
    local_ptr __ALWAYS_INLINE operator -= (difference_type r) __NOEXCEPT{ __ptr -= r; return *this; }
    local_ptr __ALWAYS_INLINE operator + (difference_type r) __NOEXCEPT{ local_ptr t(*this); t += r; return t; }
    local_ptr __ALWAYS_INLINE operator - (difference_type r) __NOEXCEPT{ local_ptr t(*this); t -= r; return t; }

private:
    add_local_t<T>* __ptr;
};

/// \brief Non-member address space pointer compare operators.
///
template<class T>
bool __ALWAYS_INLINE operator == (const local_ptr<T> &a, const local_ptr<T> &b) __NOEXCEPT{ return a.get() == b.get(); }
template<class T>
bool __ALWAYS_INLINE operator != (const local_ptr<T> &a, const local_ptr<T> &b) __NOEXCEPT{ return !(a == b); }
template<class T>
bool __ALWAYS_INLINE operator<(const local_ptr<T> &a, const local_ptr<T> &b) __NOEXCEPT{ return a.get() < b.get(); } //TODO: cl::less should be used
template<class T>
bool __ALWAYS_INLINE operator>(const local_ptr<T> &a, const local_ptr<T> &b) __NOEXCEPT{ return b < a; }
template<class T>
bool __ALWAYS_INLINE operator <= (const local_ptr<T> &a, const local_ptr<T> &b) __NOEXCEPT{ return !(b < a); }
template<class T>
bool __ALWAYS_INLINE operator >= (const local_ptr<T> &a, const local_ptr<T> &b) __NOEXCEPT{ return !(a < b); }

template<class T>
bool __ALWAYS_INLINE operator == (const local_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !x; }
template<class T>
bool __ALWAYS_INLINE operator == (nullptr_t, const local_ptr<T> &x) __NOEXCEPT{ return !x; }
template<class T>
bool __ALWAYS_INLINE operator != (const local_ptr<T> &x, nullptr_t) __NOEXCEPT{ return (bool)x; }
template<class T>
bool __ALWAYS_INLINE operator != (nullptr_t, const local_ptr<T> &x) __NOEXCEPT{ return (bool)x; }
template<class T>
bool __ALWAYS_INLINE operator<(const local_ptr<T> &x, nullptr_t) __NOEXCEPT{ return x.get() < nullptr; } //TODO: cl:less should be used
template<class T>
bool __ALWAYS_INLINE operator<(nullptr_t, const local_ptr<T> &x) __NOEXCEPT{ return nullptr < x.get(); } //TODO: cl:less should be used
template<class T>
bool __ALWAYS_INLINE operator>(const local_ptr<T> &x, nullptr_t) __NOEXCEPT{ return nullptr < x; }
template<class T>
bool __ALWAYS_INLINE operator>(nullptr_t, const local_ptr<T> &x) __NOEXCEPT{ return x < nullptr; }
template<class T>
bool __ALWAYS_INLINE operator <= (const local_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !(nullptr < x); }
template<class T>
bool __ALWAYS_INLINE operator <= (nullptr_t, const local_ptr<T> &x) __NOEXCEPT{ return !(x < nullptr); }
template<class T>
bool __ALWAYS_INLINE operator >= (const local_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !(x < nullptr); }
template<class T>
bool __ALWAYS_INLINE operator >= (nullptr_t, const local_ptr<T> &x) __NOEXCEPT{ return !(nullptr < x); }

/// \brief Non-member address space pointer swap function
///
template<class T>
void __ALWAYS_INLINE swap(local_ptr<T>& a, local_ptr<T>& b) __NOEXCEPT { a.swap(b); }

/// \brief Explicit constant address space pointer class
///
/// The explicit OpenCL AS pointer class provides similar interface to std::unique_ptr.
/// The class is needed to preserve the address space information without
/// extending C++ language.
template <class T>
class constant_ptr {
public:
    //types:
    typedef T                         element_type;
    typedef ptrdiff_t                 difference_type;
    typedef add_constant_t<T>*        pointer;
    typedef add_constant_t<const T>*  const_pointer;
    typedef add_constant_t<T>&        reference;
    typedef add_constant_t<const T>&  const_reference;

    //constructors:
    constexpr __ALWAYS_INLINE constant_ptr() __NOEXCEPT = default;
    explicit __ALWAYS_INLINE constant_ptr(pointer p) __NOEXCEPT: __ptr(p) { };
    __ALWAYS_INLINE constant_ptr(const constant_ptr &r) __NOEXCEPT = default;
    __ALWAYS_INLINE constant_ptr(constant_ptr &&r) __NOEXCEPT = default;
    constexpr __ALWAYS_INLINE constant_ptr(nullptr_t) __NOEXCEPT: constant_ptr() { };

    //assignment:
    constant_ptr& __ALWAYS_INLINE operator = (const constant_ptr &r) __NOEXCEPT{ __ptr = r.__ptr; return *this; }
    constant_ptr& __ALWAYS_INLINE operator = (constant_ptr &&r) __NOEXCEPT{ __ptr = cl::move(r.__ptr); return *this; }
    constant_ptr& __ALWAYS_INLINE operator = (pointer r) __NOEXCEPT{ __ptr = r; return *this; }
    constant_ptr& __ALWAYS_INLINE operator = (nullptr_t)__NOEXCEPT{ reset(); return *this; }

    //observers:
    add_lvalue_reference_t<add_constant_t<T>> __ALWAYS_INLINE operator*() const __NOEXCEPT{ return *get(); }
    pointer __ALWAYS_INLINE operator->() const __NOEXCEPT{ return get(); }
    pointer __ALWAYS_INLINE get() const __NOEXCEPT{ return __ptr; }
    explicit __ALWAYS_INLINE operator bool() const __NOEXCEPT{ return get() != nullptr; }

    //modifiers:
    pointer __ALWAYS_INLINE release() __NOEXCEPT{ pointer t = __ptr; __ptr = nullptr; return t; }
    void __ALWAYS_INLINE reset(pointer p = pointer()) __NOEXCEPT{ __ptr = p; }
    void __ALWAYS_INLINE swap(constant_ptr& r) __NOEXCEPT{ cl::swap(*this, r); }

    //modifiers specific for OpenCL C++:
    constant_ptr __ALWAYS_INLINE operator++() __NOEXCEPT{ constant_ptr t(*this); ++__ptr; return t; }
    constant_ptr& __ALWAYS_INLINE operator++(int)__NOEXCEPT{ __ptr++; return *this; }
    constant_ptr __ALWAYS_INLINE operator--() __NOEXCEPT{ constant_ptr t(*this); --__ptr; return t; }
    constant_ptr& __ALWAYS_INLINE operator--(int)__NOEXCEPT{ --__ptr; return *this; }
    constant_ptr& __ALWAYS_INLINE operator += (difference_type r) __NOEXCEPT{ __ptr += r; return *this; }
    constant_ptr& __ALWAYS_INLINE operator -= (difference_type r) __NOEXCEPT{ __ptr -= r; return *this; }
    constant_ptr __ALWAYS_INLINE operator + (difference_type r) __NOEXCEPT{ constant_ptr t(*this); t += r; return t; }
    constant_ptr __ALWAYS_INLINE operator - (difference_type r) __NOEXCEPT{ constant_ptr t(*this); t -= r; return t; }

private:
    add_constant_t<T>* __ptr;
};

/// \brief Explicit address space pointer class specialization for arrays
///
template <class T>
class constant_ptr<T[]> {
public:
    typedef T                         element_type;
    typedef ptrdiff_t                 difference_type;
    typedef add_constant_t<T>*        pointer;
    typedef add_constant_t<const T>*  const_pointer;
    typedef add_constant_t<T>&        reference;
    typedef add_constant_t<const T>&  const_reference;

    //constructors:
    constexpr __ALWAYS_INLINE constant_ptr() __NOEXCEPT = default;
    explicit __ALWAYS_INLINE constant_ptr(pointer p) __NOEXCEPT: __ptr(p) { };
    __ALWAYS_INLINE constant_ptr(const constant_ptr &r) __NOEXCEPT = default;
    __ALWAYS_INLINE constant_ptr(constant_ptr &&r) __NOEXCEPT = default;
    constexpr __ALWAYS_INLINE constant_ptr(nullptr_t) __NOEXCEPT: constant_ptr() { };

    //assignment:
    constant_ptr& __ALWAYS_INLINE operator = (const constant_ptr &r) __NOEXCEPT{ __ptr = r.__ptr; return *this; }
    constant_ptr& __ALWAYS_INLINE operator = (constant_ptr &&r) __NOEXCEPT{ __ptr = cl::move(r.__ptr); return *this; }
    constant_ptr& __ALWAYS_INLINE operator = (pointer r) __NOEXCEPT{ __ptr = r; return *this; }
    constant_ptr& __ALWAYS_INLINE operator = (nullptr_t)__NOEXCEPT{ reset(); return *this; }

    //observers:
    reference __ALWAYS_INLINE operator[](size_t pos) const __NOEXCEPT{ return get()[pos]; }
    pointer __ALWAYS_INLINE get() const __NOEXCEPT{ return __ptr; }
    explicit __ALWAYS_INLINE operator bool() const __NOEXCEPT{ return get() != nullptr; }

    //modifiers:
    pointer __ALWAYS_INLINE release() __NOEXCEPT{ pointer tmp = __ptr; __ptr = nullptr; return tmp; }
    void __ALWAYS_INLINE reset(pointer p) __NOEXCEPT{ __ptr = p; }
    void __ALWAYS_INLINE reset(nullptr_t p = nullptr) __NOEXCEPT{ reset(pointer()); }
    void __ALWAYS_INLINE swap(constant_ptr& r) __NOEXCEPT{ cl::swap(*this, r); }

    //modifiers specific for OpenCL C++:
    constant_ptr __ALWAYS_INLINE operator++() __NOEXCEPT{ constant_ptr t(*this); ++__ptr; return t; }
    constant_ptr __ALWAYS_INLINE operator++(int)__NOEXCEPT{ __ptr++; return *this; }
    constant_ptr __ALWAYS_INLINE operator--() __NOEXCEPT{ constant_ptr t(*this); --__ptr; return t; }
    constant_ptr __ALWAYS_INLINE operator--(int)__NOEXCEPT{ --__ptr; return *this; }
    constant_ptr __ALWAYS_INLINE operator += (difference_type r) __NOEXCEPT{ __ptr += r; return *this; }
    constant_ptr __ALWAYS_INLINE operator -= (difference_type r) __NOEXCEPT{ __ptr -= r; return *this; }
    constant_ptr __ALWAYS_INLINE operator + (difference_type r) __NOEXCEPT{ constant_ptr t(*this); t += r; return t; }
    constant_ptr __ALWAYS_INLINE operator - (difference_type r) __NOEXCEPT{ constant_ptr t(*this); t -= r; return t; }

private:
    add_constant_t<T>* __ptr;
};

/// \brief Non-member address space pointer compare operators.
///
template<class T>
bool __ALWAYS_INLINE operator == (const constant_ptr<T> &a, const constant_ptr<T> &b) __NOEXCEPT{ return a.get() == b.get(); }
template<class T>
bool __ALWAYS_INLINE operator != (const constant_ptr<T> &a, const constant_ptr<T> &b) __NOEXCEPT{ return !(a == b); }
template<class T>
bool __ALWAYS_INLINE operator<(const constant_ptr<T> &a, const constant_ptr<T> &b) __NOEXCEPT{ return a.get() < b.get(); } //TODO: cl::less should be used
template<class T>
bool __ALWAYS_INLINE operator>(const constant_ptr<T> &a, const constant_ptr<T> &b) __NOEXCEPT{ return b < a; }
template<class T>
bool __ALWAYS_INLINE operator <= (const constant_ptr<T> &a, const constant_ptr<T> &b) __NOEXCEPT{ return !(b < a); }
template<class T>
bool __ALWAYS_INLINE operator >= (const constant_ptr<T> &a, const constant_ptr<T> &b) __NOEXCEPT{ return !(a < b); }

template<class T>
bool __ALWAYS_INLINE operator == (const constant_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !x; }
template<class T>
bool __ALWAYS_INLINE operator == (nullptr_t, const constant_ptr<T> &x) __NOEXCEPT{ return !x; }
template<class T>
bool __ALWAYS_INLINE operator != (const constant_ptr<T> &x, nullptr_t) __NOEXCEPT{ return (bool)x; }
template<class T>
bool __ALWAYS_INLINE operator != (nullptr_t, const constant_ptr<T> &x) __NOEXCEPT{ return (bool)x; }
template<class T>
bool __ALWAYS_INLINE operator<(const constant_ptr<T> &x, nullptr_t) __NOEXCEPT{ return x.get() < nullptr; } //TODO: cl:less should be used
template<class T>
bool __ALWAYS_INLINE operator<(nullptr_t, const constant_ptr<T> &x) __NOEXCEPT{ return nullptr < x.get(); } //TODO: cl:less should be used
template<class T>
bool __ALWAYS_INLINE operator>(const constant_ptr<T> &x, nullptr_t) __NOEXCEPT{ return nullptr < x; }
template<class T>
bool __ALWAYS_INLINE operator>(nullptr_t, const constant_ptr<T> &x) __NOEXCEPT{ return x < nullptr; }
template<class T>
bool __ALWAYS_INLINE operator <= (const constant_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !(nullptr < x); }
template<class T>
bool __ALWAYS_INLINE operator <= (nullptr_t, const constant_ptr<T> &x) __NOEXCEPT{ return !(x < nullptr); }
template<class T>
bool __ALWAYS_INLINE operator >= (const constant_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !(x < nullptr); }
template<class T>
bool __ALWAYS_INLINE operator >= (nullptr_t, const constant_ptr<T> &x) __NOEXCEPT{ return !(nullptr < x); }

/// \brief Non-member address space pointer swap function
///
template<class T>
void __ALWAYS_INLINE swap(constant_ptr<T>& a, constant_ptr<T>& b) __NOEXCEPT { a.swap(b); }

/// \brief Explicit private address space pointer class
///
/// The explicit OpenCL AS pointer class provides similar interface to std::unique_ptr.
/// The class is needed to preserve the address space information without
/// extending C++ language.
template <class T>
class private_ptr {
public:
    //types:
    typedef T                        element_type;
    typedef ptrdiff_t                difference_type;
    typedef add_private_t<T>*        pointer;
    typedef add_private_t<const T>*  const_pointer;
    typedef add_private_t<T>&        reference;
    typedef add_private_t<const T>&  const_reference;

    //constructors:
    constexpr __ALWAYS_INLINE private_ptr() __NOEXCEPT = default;
    explicit __ALWAYS_INLINE private_ptr(pointer p) __NOEXCEPT: __ptr(p) { };
    __ALWAYS_INLINE private_ptr(const private_ptr &r) __NOEXCEPT = default;
    __ALWAYS_INLINE private_ptr(private_ptr &&r) __NOEXCEPT = default;
    constexpr __ALWAYS_INLINE private_ptr(nullptr_t) __NOEXCEPT: private_ptr() { };

    //assignment:
    private_ptr& __ALWAYS_INLINE operator = (const private_ptr &r) __NOEXCEPT{ __ptr = r.__ptr; return *this; }
    private_ptr& __ALWAYS_INLINE operator = (private_ptr &&r) __NOEXCEPT{ __ptr = cl::move(r.__ptr); return *this; }
    private_ptr& __ALWAYS_INLINE operator = (pointer r) __NOEXCEPT{ __ptr = r; return *this; }
    private_ptr& __ALWAYS_INLINE operator = (nullptr_t)__NOEXCEPT{ reset(); return *this; }

    //observers:
    add_lvalue_reference_t<add_private_t<T>> __ALWAYS_INLINE operator*() const __NOEXCEPT{ return *get(); }
    pointer __ALWAYS_INLINE operator->() const __NOEXCEPT{ return get(); }
    pointer __ALWAYS_INLINE get() const __NOEXCEPT{ return __ptr; }
    explicit __ALWAYS_INLINE operator bool() const __NOEXCEPT{ return get() != nullptr; }

    //modifiers:
    pointer __ALWAYS_INLINE release() __NOEXCEPT{ pointer t = __ptr; __ptr = nullptr; return t; }
    void __ALWAYS_INLINE reset(pointer p = pointer()) __NOEXCEPT{ __ptr = p; }
    void __ALWAYS_INLINE swap(private_ptr& r) __NOEXCEPT{ cl::swap(*this, r); }

    //modifiers specific for OpenCL C++:
    private_ptr __ALWAYS_INLINE operator++() __NOEXCEPT{ private_ptr t(*this); ++__ptr; return t; }
    private_ptr& __ALWAYS_INLINE operator++(int)__NOEXCEPT{ __ptr++; return *this; }
    private_ptr __ALWAYS_INLINE operator--() __NOEXCEPT{ private_ptr t(*this); --__ptr; return t; }
    private_ptr& __ALWAYS_INLINE operator--(int)__NOEXCEPT{ --__ptr; return *this; }
    private_ptr& __ALWAYS_INLINE operator += (difference_type r) __NOEXCEPT{ __ptr += r; return *this; }
    private_ptr& __ALWAYS_INLINE operator -= (difference_type r) __NOEXCEPT{ __ptr -= r; return *this; }
    private_ptr __ALWAYS_INLINE operator + (difference_type r) __NOEXCEPT{ private_ptr t(*this); t += r; return t; }
    private_ptr __ALWAYS_INLINE operator - (difference_type r) __NOEXCEPT{ private_ptr t(*this); t -= r; return t; }

private:
    add_private_t<T>* __ptr;
};

/// \brief Explicit address space pointer class specialization for arrays
///
template <class T>
class private_ptr<T[]> {
public:
    typedef T                        element_type;
    typedef ptrdiff_t                difference_type;
    typedef add_private_t<T>*        pointer;
    typedef add_private_t<const T>*  const_pointer;
    typedef add_private_t<T>&        reference;
    typedef add_private_t<const T>&  const_reference;

    //constructors:
    constexpr __ALWAYS_INLINE private_ptr() __NOEXCEPT = default;
    explicit __ALWAYS_INLINE private_ptr(pointer p) __NOEXCEPT: __ptr(p) { };
    __ALWAYS_INLINE private_ptr(const private_ptr &r) __NOEXCEPT = default;
    __ALWAYS_INLINE private_ptr(private_ptr &&r) __NOEXCEPT = default;
    constexpr __ALWAYS_INLINE private_ptr(nullptr_t) __NOEXCEPT: private_ptr() { };

    //assignment:
    private_ptr& __ALWAYS_INLINE operator = (const private_ptr &r) __NOEXCEPT{ __ptr = r.__ptr; return *this; }
    private_ptr& __ALWAYS_INLINE operator = (private_ptr &&r) __NOEXCEPT{ __ptr = cl::move(r.__ptr); return *this; }
    private_ptr& __ALWAYS_INLINE operator = (pointer r) __NOEXCEPT{ __ptr = r; return *this; }
    private_ptr& __ALWAYS_INLINE operator = (nullptr_t)__NOEXCEPT{ reset(); return *this; }

    //observers:
    reference __ALWAYS_INLINE operator[](size_t pos) const __NOEXCEPT{ return get()[pos]; }
    pointer __ALWAYS_INLINE get() const __NOEXCEPT{ return __ptr; }
    explicit __ALWAYS_INLINE operator bool() const __NOEXCEPT{ return get() != nullptr; }

    //modifiers:
    pointer __ALWAYS_INLINE release() __NOEXCEPT{ pointer tmp = __ptr; __ptr = nullptr; return tmp; }
    void __ALWAYS_INLINE reset(pointer p) __NOEXCEPT{ __ptr = p; }
    void __ALWAYS_INLINE reset(nullptr_t p = nullptr) __NOEXCEPT{ reset(pointer()); }
    void __ALWAYS_INLINE swap(private_ptr& r) __NOEXCEPT{ cl::swap(*this, r); }

    //modifiers specific for OpenCL C++:
    private_ptr __ALWAYS_INLINE operator++() __NOEXCEPT{ private_ptr t(*this); ++__ptr; return t; }
    private_ptr __ALWAYS_INLINE operator++(int)__NOEXCEPT{ __ptr++; return *this; }
    private_ptr __ALWAYS_INLINE operator--() __NOEXCEPT{ private_ptr t(*this); --__ptr; return t; }
    private_ptr __ALWAYS_INLINE operator--(int)__NOEXCEPT{ --__ptr; return *this; }
    private_ptr __ALWAYS_INLINE operator += (difference_type r) __NOEXCEPT{ __ptr += r; return *this; }
    private_ptr __ALWAYS_INLINE operator -= (difference_type r) __NOEXCEPT{ __ptr -= r; return *this; }
    private_ptr __ALWAYS_INLINE operator + (difference_type r) __NOEXCEPT{ private_ptr t(*this); t += r; return t; }
    private_ptr __ALWAYS_INLINE operator - (difference_type r) __NOEXCEPT{ private_ptr t(*this); t -= r; return t; }

private:
    add_private_t<T>* __ptr;
};

/// \brief Non-member address space pointer compare operators.
///
template<class T>
bool __ALWAYS_INLINE operator == (const private_ptr<T> &a, const private_ptr<T> &b) __NOEXCEPT{ return a.get() == b.get(); }
template<class T>
bool __ALWAYS_INLINE operator != (const private_ptr<T> &a, const private_ptr<T> &b) __NOEXCEPT{ return !(a == b); }
template<class T>
bool __ALWAYS_INLINE operator<(const private_ptr<T> &a, const private_ptr<T> &b) __NOEXCEPT{ return a.get() < b.get(); } //TODO: cl::less should be used
template<class T>
bool __ALWAYS_INLINE operator>(const private_ptr<T> &a, const private_ptr<T> &b) __NOEXCEPT{ return b < a; }
template<class T>
bool __ALWAYS_INLINE operator <= (const private_ptr<T> &a, const private_ptr<T> &b) __NOEXCEPT{ return !(b < a); }
template<class T>
bool __ALWAYS_INLINE operator >= (const private_ptr<T> &a, const private_ptr<T> &b) __NOEXCEPT{ return !(a < b); }

template<class T>
bool __ALWAYS_INLINE operator == (const private_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !x; }
template<class T>
bool __ALWAYS_INLINE operator == (nullptr_t, const private_ptr<T> &x) __NOEXCEPT{ return !x; }
template<class T>
bool __ALWAYS_INLINE operator != (const private_ptr<T> &x, nullptr_t) __NOEXCEPT{ return (bool)x; }
template<class T>
bool __ALWAYS_INLINE operator != (nullptr_t, const private_ptr<T> &x) __NOEXCEPT{ return (bool)x; }
template<class T>
bool __ALWAYS_INLINE operator<(const private_ptr<T> &x, nullptr_t) __NOEXCEPT{ return x.get() < nullptr; } //TODO: cl:less should be used
template<class T>
bool __ALWAYS_INLINE operator<(nullptr_t, const private_ptr<T> &x) __NOEXCEPT{ return nullptr < x.get(); } //TODO: cl:less should be used
template<class T>
bool __ALWAYS_INLINE operator>(const private_ptr<T> &x, nullptr_t) __NOEXCEPT{ return nullptr < x; }
template<class T>
bool __ALWAYS_INLINE operator>(nullptr_t, const private_ptr<T> &x) __NOEXCEPT{ return x < nullptr; }
template<class T>
bool __ALWAYS_INLINE operator <= (const private_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !(nullptr < x); }
template<class T>
bool __ALWAYS_INLINE operator <= (nullptr_t, const private_ptr<T> &x) __NOEXCEPT{ return !(x < nullptr); }
template<class T>
bool __ALWAYS_INLINE operator >= (const private_ptr<T> &x, nullptr_t) __NOEXCEPT{ return !(x < nullptr); }
template<class T>
bool __ALWAYS_INLINE operator >= (nullptr_t, const private_ptr<T> &x) __NOEXCEPT{ return !(nullptr < x); }

/// \brief Non-member address space pointer swap function
///
template<class T>
void __ALWAYS_INLINE swap(private_ptr<T>& a, private_ptr<T>& b) __NOEXCEPT { a.swap(b); }

}