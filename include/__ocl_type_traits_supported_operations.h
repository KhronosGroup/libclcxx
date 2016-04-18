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

#include <__ocl_type_traits_base.h>
#include <__ocl_type_traits_type_categories.h>
#include <__ocl_type_traits_extents.h>
#include <__ocl_utility.h>

namespace cl
{

template <class T> struct is_trivially_copyable;

namespace __details
{

/// \brief Helper class for is same trait
///
template <class From, class To>
struct __is_assignable_helper
{
private:
	template <class T, class U>
	static decltype( static_cast<const volatile void>( declval<T>( ) = declval<U>( ) ), true_type{ } ) helper( nullptr_t );
	
	template <class T, class U>
	static false_type helper( void* );
public:
	static constexpr bool value = decltype( helper<From, To>( nullptr ) )::value;
};

template <class T>
struct __is_destructible_helper
{
private:
	template <class U>
	static decltype( ( declval<U&>( ).~U( ) ), true_type{ } ) helper( nullptr_t );
	
	template <class U>
	static false_type helper( void* );
public:
	static constexpr bool value = decltype( helper<T>( nullptr ) )::value;
};

template <class T>
struct __is_nothrow_destructible_helper
{
private:
	template <class U>
	static integral_constant<bool, noexcept( declval<U&>( ).~U( ) )> helper( nullptr_t );
	
	template <class U>
	static false_type helper( void* );
public:
	static constexpr bool value = decltype( helper<T>( nullptr ) )::value;
};

}

/// \brief Type trait checking if one type is assignable to another
///
template <class T, class U>
struct is_assignable : integral_constant<bool, __details::__is_assignable_helper<T, U>::value >{ };

/// \brief Type trait checking if type has constructor with (Args...) signature
///
template <class T, class... Args>
struct is_constructible : integral_constant<bool, __is_constructible(T, Args...)> { };

/// \brief Type trait checking if type has default constructor
///
template <class T>
struct is_default_constructible : is_constructible<T> { };

/// \brief Type trait checking if type has copy constructor
///
template <class T>
struct is_copy_constructible : is_constructible<T, const add_lvalue_reference_t<T>> { };

/// \brief Type trait checking if type has move constructor
///
template <class T>
struct is_move_constructible : is_constructible<T, add_rvalue_reference_t<T>> { };

/// \brief Type trait checking if type has copy assignment operator
///
template <class T>
struct is_copy_assignable : is_assignable<add_lvalue_reference_t<T>, const add_lvalue_reference_t<T>> { };

/// \brief Type trait checking if type has move assignment operator
///
template <class T>
struct is_move_assignable : is_assignable<add_lvalue_reference_t<T>, add_rvalue_reference_t<T>> { };

/// \brief Type trait checking if type has destructor
///
template <class T>
struct is_destructible : integral_constant<bool, is_array<T>::value ?
                                                    __details::__is_destructible_helper<remove_all_extents_t<T>>::value :
                                                    is_reference<T>::value || __details::__is_destructible_helper<T>::value> { };

/// \brief Type trait checking if type has constructor with (Args...) signature which performs only trivial operations
///
template <class T, class... Args>
struct is_trivially_constructible : integral_constant<bool, __is_trivially_constructible(T, Args...)> { };

/// \brief Type trait checking if type has trivial default constructor
///
template <class T>
struct is_trivially_default_constructible : is_trivially_constructible<T> { };

/// \brief Type trait checking if type has trivial copy constructor
///
template <class T>
struct is_trivially_copy_constructible : is_trivially_constructible<T, const add_lvalue_reference_t<T>> { };

/// \brief Type trait checking if type has trivial move constructor
///
template <class T>
struct is_trivially_move_constructible : is_trivially_constructible<T, add_rvalue_reference_t<T>> { };

/// \brief Type trait checking if one type is trivially assignable to another
///
template <class T, class U>
struct is_trivially_assignable : integral_constant<bool, __is_trivially_assignable(T, U)> { };

/// \brief Type trait checking if type has trivial copy assignment operator
///
template <class T>
struct is_trivially_copy_assignable : is_trivially_assignable<add_lvalue_reference_t<T>, const add_lvalue_reference_t<T>> { };

/// \brief Type trait checking if type has trivial move assignment operator
///
template <class T>
struct is_trivially_move_assignable : is_trivially_assignable<add_lvalue_reference_t<T>, add_rvalue_reference_t<T>> { };

/// \brief Type trait checking if type has trivial destructor
///
template <class T>
struct is_trivially_destructible : integral_constant<bool, __has_trivial_destructor(T)> { };

/// \brief Type trait checking if type has constructor with (Args...) signature and nothrow specifier
///
template <class T, class... Args>
struct is_nothrow_constructible : integral_constant<bool, __is_nothrow_constructible(T, Args...)> { };

/// \brief Type trait checking if type has default constructor with nothrow specifier
///
template <class T>
struct is_nothrow_default_constructible : is_nothrow_constructible<T> { };

/// \brief Type trait checking if type has copy constructor with nothrow specifier
///
template <class T>
struct is_nothrow_copy_constructible : is_nothrow_constructible<T, const add_lvalue_reference_t<T>> { };

/// \brief Type trait checking if type has move constructor with nothrow specifier
///
template <class T>
struct is_nothrow_move_constructible : is_nothrow_constructible<T, add_rvalue_reference_t<T>> { };

/// \brief Type trait checking if one type can be assigned to another by nothrow operation
///
template <class T, class U>
struct is_nothrow_assignable : integral_constant<bool, __is_nothrow_assignable(T, U)> { };

/// \brief Type trait checking if type has copy assignment operator with nothrow specifier
///
template <class T>
struct is_nothrow_copy_assignable : is_nothrow_assignable<add_lvalue_reference_t<T>, const add_lvalue_reference_t<T>> { };

/// \brief Type trait checking if type has move assignment operator with nothrow specifier
///
template <class T>
struct is_nothrow_move_assignable : is_nothrow_assignable<add_lvalue_reference_t<T>, add_rvalue_reference_t<T>> { };

/// \brief Type trait checking if type has destructor with nothrow specifier
///
template <class T>
struct is_nothrow_destructible : integral_constant<bool, is_array<T>::value ?
                                                            is_nothrow_destructible<remove_all_extents_t<T>>::value :
                                                            is_reference<T>::value || __details::__is_nothrow_destructible_helper<T>::value> { };

/// \brief Type trait checking if type has destructor with virtual specifier which is always false since OCL C++ doesn't support virtual keyword
///
template <class T>
struct has_virtual_destructor : false_type { };

}