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
#include <__ocl_type_traits_declval.h>
#include <__ocl_type_traits_cv_ref_ptr.h>
#include <__ocl_type_traits_extents.h>
#include <__ocl_type_traits_type_categories.h>

namespace cl
{

template <class T> struct decay;
template <class T> struct result_of;
template <bool b, class T = void> struct enable_if;
template <class... T> struct common_type;
template <class T> struct underlying_type;
template <size_t Len, class... Types> struct aligned_union;

template <class T>
using decay_t = typename decay<T>::type;
template <class T>
using result_of_t = typename result_of<T>::type;
template <bool b, class T = void>
using enable_if_t = typename enable_if<b,T>::type;
template <class... T>
using common_type_t = typename common_type<T...>::type;
template <class T>
using underlying_type_t = typename underlying_type<T>::type;
template <size_t Len, class... Types>
using aligned_union_t = typename aligned_union<Len,Types...>::type;
template <class...>
using void_t = void;

/// \brief Type trait that conditionally defines type
///
template <bool Cond, class T>
struct enable_if { };

/// \brief Type trait that conditionally defines type
///
template <class T>
struct enable_if<true, T> { typedef T type; };

namespace __details
{

/// \brief Helper trait checking if common type exists
///
template <class...>
struct __has_common_type;

/// \brief Helper trait checking if common type exists
///
template <class T, class U, class... Types>
struct __has_common_type<T, U, Types...> { static const bool value = __has_common_type<T, U>::value && __has_common_type<Types...>::value; };

/// \brief Helper trait checking if common type exists
///
template <class T, class U>
struct __has_common_type<T, U>
{
private:
    template<class X, class Y>
	static decltype( ( true ? declval<X>( ) : declval<Y>( ) ), true_type{ } ) helper( nullptr_t );
	
	template <class X, class Y>
	static false_type helper( void* );
public:
	static const bool value = decltype( helper<T, U>( nullptr ) )::value;
};

/// \brief Helper trait checking if common type exists
///
template <class T>
struct __has_common_type<T> { static const bool value = true; };

/// \brief Helper trait for common_type
///
template <bool, class...>
struct __common_type_helper;

/// \brief Helper trait for common_type
///
template <class... Types>
struct __common_type_helper<false, Types...> { };

/// \brief Helper trait for common_type
///
template <class T, class U>
struct __common_type_helper<true, T, U> { typedef decay_t<decltype( true ? declval<T>( ) : declval<U>( ) )> type; };

/// \brief Helper trait for common_type
///
template <class T, class U, class... Types>
struct __common_type_helper<true, T, U, Types...> { typedef common_type_t<common_type_t<T, U>, Types...> type; };

}

/// \brief Type trait that finds the common type that all provided types can be converted to
///
template <class... Types>
struct common_type;

/// \brief Type trait that finds the common type that all provided types can be converted to
///
template <class T>
struct common_type<T> { typedef decay_t<T> type; };

/// \brief Type trait that finds the common type that all provided types can be converted to
///
template <class T, class U>
struct common_type<T, U> : __details::__common_type_helper<__details::__has_common_type<T,U>::value, T, U> { };

/// \brief Type trait that finds the common type that all provided types can be converted to
///
template <class T>
struct common_type<T, T> { typedef decay_t<T> type; };

/// \brief Type trait that finds the common type that all provided types can be converted to
///
template <class T, class U, class... Types>
struct common_type<T, U, Types...> : __details::__common_type_helper<__details::__has_common_type<T,U, Types...>::value, T, U, Types...> { };

/// \brief Type trait obtaining storage type of an enum
///
template <class T>
struct underlying_type { static_assert(is_enum<T>::value, "You can only obtain underlying type of an enum"); typedef __underlying_type(T) type; };

namespace __details
{

/// \brief Implementation of forward
///
template <class T>
T&& __forward_helper(remove_reference_t<T>& t) { return static_cast<T&&>(t); };

/// \brief Implementation of forward
///
template <class T>
T&& __forward_helper(remove_reference_t<T>&& t) { return static_cast<T&&>(t); };

/// \brief Helper trait that gets class from a pointer to member
///
template <class T>
struct __get_class_from_pmf { typedef void type; };

/// \brief Helper trait that gets class from a pointer to member
///
template <class T, class U>
struct __get_class_from_pmf<T U::*> { typedef U type; };

template <class T>
using __get_class_from_pmf_t = typename __get_class_from_pmf<T>::type;

/// \brief Helper trait checking if U is a T, reference to T or reference to an object derived from T
///
template <class T, class U>
struct __is_derived_reference : integral_constant<bool, is_reference<U>::value && is_base_of<T, remove_reference_t<U>>::value> { };

/// \brief This implements INVOKE as specified in paragraph 1.1 of [func.require]
///
template <class Fun, class Obj, class... Args>
auto __invoke(Fun&& fun, Obj&& obj, Args&&... args)
    -> enable_if_t<is_member_function_pointer<Fun>::value && __is_derived_reference<Obj, __get_class_from_pmf_t<Fun>>::value,
        decltype((obj.*fun)(__forward_helper<Args>(args)...))>;

/// \brief This implements INVOKE as specified in paragraph 1.2 of [func.require]
///
template <class Fun, class Obj, class... Args>
auto __invoke(Fun&& fun, Obj&& obj, Args&&... args)
    -> enable_if_t<is_member_function_pointer<Fun>::value && !__is_derived_reference<Obj, __get_class_from_pmf_t<Fun>>::value,
        decltype(((*obj).*fun)(__forward_helper<Args>(args)...))>;

/// \brief This implements INVOKE as specified in paragraph 1.3 of [func.require]
///
template <class Fun, class Obj>
auto __invoke(Fun&& fun, Obj&& obj)
    -> enable_if_t<is_member_object_pointer<Fun>::value && __is_derived_reference<Obj, __get_class_from_pmf_t<Fun>>::value,
        decltype(obj.*fun)>;

/// \brief This implements INVOKE as specified in paragraph 1.4 of [func.require]
///
template <class Fun, class Obj>
auto __invoke(Fun&& fun, Obj&& obj)
    -> enable_if_t<is_member_object_pointer<Fun>::value && !__is_derived_reference<Obj, __get_class_from_pmf_t<Fun>>::value,
        decltype((*obj).*fun)>;

/// \brief This implements INVOKE as specified in paragraph 1.5 of [func.require]
///
template <class Fun, class... Args>
auto __invoke(Fun && fun, Args&&... args) -> decltype(__forward_helper<Fun>(fun)(__forward_helper<Args>(args)...))
{
    return (__forward_helper<Fun>(fun)(__forward_helper<Args>(args)...));
}

/// \brief Helper class for is same trait
///
template <class... TypeList>
struct __is_invokable_helper
{
private:
	template <class... Types>
	static decltype( declval<decltype(__invoke(declval<Types>( )...))>( ), true_type{ } ) helper( nullptr_t );
	
	template <class... Types>
	static false_type helper( void* );
public:
	static constexpr bool value = decltype( helper<TypeList...>( nullptr ) )::value;
};

/// \brief Helper trait obtaining return type of call expression
///
template <bool, class...>
struct __result_of_helper { };

/// \brief Helper trait obtaining return type of call expression
///
template <class... Args>
struct __result_of_helper<true, Args...> { typedef decltype(__invoke(declval<Args>( )...)) type; };

}

template <class T>
struct result_of { };

template <class Fun, class... Types>
struct result_of<Fun(Types...)> : __details::__result_of_helper<__details::__is_invokable_helper<Fun, Types...>::value, Fun, Types...> { };

namespace __details
{
/// \brief Helper trait for decay
///
template <class T, bool = is_function<T>::value>
struct __decay_helper { typedef remove_attrs_t<T> type; };

/// \brief Helper trait for decay
///
template <class T>
struct __decay_helper<T[], false> { typedef add_pointer_t<remove_extent_t<T>> type; };

/// \brief Helper trait for decay
///
template <class T, size_t Size>
struct __decay_helper<T[Size], false> { typedef add_pointer_t<remove_extent_t<T>> type; };

/// \brief Helper trait for decay
///
template <class T>
struct __decay_helper<T, true> { typedef add_pointer_t<T> type; };
}

/// \brief Trait obtaining decay type for a type
///
template <class T>
struct decay : __details::__decay_helper<remove_reference_t<T>> { };

namespace __details
{

/// \brief Helper trait calculating maximal value from given compile time constants
///
template <size_t A, size_t... Remainder>
struct __max_helper : integral_constant<size_t, (A > __max_helper<Remainder...>::value ? A : __max_helper<Remainder...>::value)> { };

/// \brief Helper trait calculating maximal value from given compile time constants
///
template <size_t A, size_t B>
struct __max_helper<A, B> : integral_constant<size_t, (A > B ? A : B)> { };

/// \brief Helper function calculating bit length of a number
///
constexpr size_t __len_helper(size_t size) { return (size == 0) ? 0 : 1 + __len_helper(size >> 1); }

/// \brief Helper function calculating next power of two of a number
///
constexpr size_t __alignment_helper(size_t size) { return size == 0 ? 0 : 1 << __len_helper(size - 1); }

}

/// \brief Trait generating POD type that can store at least Len bytes with alignment equal to Alignment
///
template <size_t Len, size_t Alignment = sizeof(unsigned long) * 16 < __details::__alignment_helper(Len) ?
                                                __details::__alignment_helper(Len) :
                                                sizeof(unsigned long) * 16>
struct aligned_storage { typedef struct { alignas(Alignment) unsigned char __storage[Len]; } type; };

/// \brief Trait generating a POD type that has size and suitable alignment to store object of any type listed in Types
///
template <size_t Len, class... Types>
struct aligned_union
{
    static constexpr size_t alignment_value = __details::__max_helper<alignof(Types)...>::value;
    struct type { alignas(alignment_value) char __storage[__details::__max_helper<Len, sizeof(Types)...>::value]; };
};

}