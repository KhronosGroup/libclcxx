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
#include <__ocl_type_traits_cv_ref_ptr.h>
#include <__ocl_type_traits_type_relations.h>

#define _REGION(name) 1

namespace cl
{

namespace __details
{

#if _REGION ( Dummy types )

/// \brief Special type used on static_asserts placed in invalid template specializations
///
/// This type always has a false value, but it is evaluated only if a template is instantiated
/// therefore we can provide more meaningfull messages when users pass invalid template parameters
template <class _Dummy>
struct __always_false : false_type { };

/// \brief Helper type used when a typedef should not exists but we'd like to avoid ugly compilation errors
///
struct __invalid_type { };

/// \brief Helper type which is convertible to any other type
///
struct __any_type
{
    template <typename T>
    operator T();
};

#endif //Dummy types

#if _REGION ( Simulate fold expressions )

/// \brief Helper simulating C++17 fold expression: value = First && ... && Args;
///
template <bool... Args>
struct __all : public true_type { };

/// \brief Helper simulating C++17 fold expression: value = First && ... && Args;
///
template <bool First, bool... Args>
struct __all<First, Args...> : public integral_constant<bool, First && __all<Args...>::value> { };

/// \brief Helper simulating C++17 fold expression: value = First || ... || Args;
///
template <bool... Args>
struct __any : public false_type { };

/// \brief Helper simulating C++17 fold expression: value = First || ... || Args;
///
template <bool First, bool... Args>
struct __any<First, Args...> : public integral_constant<bool, First || __any<Args...>::value> { };

#endif //Simulate fold expressions

#if _REGION ( Parameter pack storing and querying )

/// \brief Helper class used for passing parameter packs
///
template <class... C>
struct __params { using flat = __params<C...>; static constexpr size_t size = sizeof...(C); };

/// \brief Helper class used for passing parameter packs
///
template <class... C>
struct __params<__params<C...>> { using flat = __params<C...>; static constexpr size_t size = sizeof...(C); };

/// \brief Helper class used for passing parameter packs
///
template <class T, class... U>
struct __params<T, __params<U...>> { using flat = __params<T, U...>; static constexpr size_t size = 1 + sizeof...(U); };

/// \brief Helper class used for passing parameter packs
///
template <class... T, class... U>
struct __params<__params<T...>, __params<U...>> { using flat = __params<T..., U...>; static constexpr size_t size = sizeof...(T) + sizeof...(U); };

/// \brief Helper class used to generate __params structure containing Count number of types T
///
template <typename T, size_t Count>
struct __gen_params
{
    typedef typename __params<T, typename __gen_params<T, Count-1>::type>::flat type;
};

/// \brief Helper class used to generate __params structure containing Count number of types T
///
/// specialization when 0 is reached
template <typename T>
struct __gen_params<T, 0>
{
    typedef __params<> type;
};

/// \brief Type trait checking if the first passed type appears on the list following it
///
template <class T, class... Arg>
struct __is_one_of : false_type { };

/// \brief Type trait checking if the first passed type appears on the list following it
///
template <class T, class Arg, class... Args>
struct __is_one_of<T, Arg, Args...> { static constexpr bool value = is_same<T, Arg>::value
                                             || __is_one_of<T, Args...>::value; };

/// \brief Helper class to extract i-th type from parameter pack. Produces compilation error if I > sizeof...(T)
///
template <size_t I, typename... T>
struct __ithElement { };

/// \brief Helper class to extract i-th type from parameter pack. Produces compilation error if I > sizeof...(T)
///
template <size_t I, typename T, typename... Rest>
struct __ithElement<I, T, Rest...> { using type = typename __ithElement<I-1, Rest...>::type; };

/// \brief Helper class to extract i-th type from parameter pack. Produces compilation error if I > sizeof...(T)
///
template <typename T, typename... Rest>
struct __ithElement<0, T, Rest...> { using type = T; };

/// \brief Helper class to extract i-th type from parameter pack. Produces compilation error if I > sizeof...(T)
///
//handle params
template <size_t I, typename... T>
struct __ithElement<I, __params<T...>> { using type = typename __ithElement<I, T...>::type; };

/// \brief Helper class which shifts given Idx until it finds first type T in given parameter pack.
///     That is: if Idx == 0, returns index of first T in parameter pack,
///              if Idx > 0, returns Idx + index of first T in parameter pack.
///
template <size_t Idx, typename T, typename... InTypes>
struct __find { };

/// \brief Helper class which shifts given Idx until it finds first type T in given parameter pack.
///     That is: if Idx == 0, returns index of first T in parameter pack,
///              if Idx > 0, returns Idx + index of first T in parameter pack.
///
template <size_t Idx, typename T, typename C, typename... Rest>
struct __find<Idx, T, C, Rest...> : public integral_constant<size_t, is_same<T, C>::value ? Idx : __find<Idx+1, Rest...>::value> { };

/// \brief Helper class which shifts given Idx until it finds first type T in given parameter pack.
///     That is: if Idx == 0, returns index of first T in parameter pack,
///              if Idx > 0, returns Idx + index of first T in parameter pack.
///
//handle __params
template <size_t Idx, typename T, typename... InTypes>
struct __find<Idx, T, __params<InTypes...>> { using type = typename __find<Idx, T, InTypes...>::type; };


#endif //"Parameter pack storing and querying"

#if _REGION ( Compile-time sequences )

/// \brief Helper class used for passing multiple compile-time constants of type T (analogical to __params)
///
//todo: implement std::integer_sequence?
template <class T, T... I>
struct __seq { template <T II> using prepend = __seq<T, II, I...>; template <T II> using append = __seq<T, I..., II>; };

/// \brief shorthand when T == size_t
///
template <size_t... I>
using __size_t_seq = __seq<size_t, I...>;

/// \brief Helper class for making size_t sequences of form: Start, Start + 1, ..., End - 1
///
template <size_t Start, size_t End, bool Ok = (Start < End)>
struct __make_size_t_seq { using type = __size_t_seq<>; };

/// \brief Helper class for making size_t sequences of form: Start, Start + 1, ..., End - 1
///
template <size_t Start, size_t End>
struct __make_size_t_seq<Start, End, true> { using type = typename __make_size_t_seq<Start+1, End>::type::template prepend<Start>; };

/// \brief Helper alias for making size_t sequences of form: 0, 1, ..., sizeof...(T) - 1
///
template <typename... T>
struct __make_index { using type = typename __make_size_t_seq<0, sizeof...(T)>::type; };

template <typename... T>
struct __make_index<__params<T...>> { using type = typename __make_size_t_seq<0, sizeof...(T)>::type; };

template <typename... T>
using __make_index_t = typename __make_index<T...>::type;

#endif //Compile-time sequences

#if _REGION ( Parameter pack manipulating )

/// \brief Helper class for concatenating multiple __params structures
///
template <class... C> //note that this non-specialized template is used only when C... = <>, hence type = __params<>
struct __concat_params { using type = __params<>; };

/// \brief Helper class for concatenating multiple __params structures
///
template <class C, class... Rest>
struct __concat_params<C, Rest...> { using type = typename __params<C, typename __concat_params<Rest...>::type>::flat; };

/// \brief Helper class to filter parameter pack, using Selector to determinate if given type should be included in result
///
template <template <typename> class Selector, size_t IndexOffset, typename... Types>
struct __filter_impl                     { using passed = __params<>; using passed_indexes = __size_t_seq<>; using failed = __params<>; using failed_indexes = __size_t_seq<>; };

/// \brief Helper class to filter parameter pack, using Selector to determinate if given type should be included in result
///
template <template <typename> class Selector, size_t IndexOffset, typename T, typename... Rest>
struct __filter_impl<Selector, IndexOffset, T, Rest...>
{
    using passed = conditional_t<Selector<T>::value,
            typename __params<T, typename __filter_impl<Selector, IndexOffset+1, Rest...>::passed>::flat,
            typename __params<typename __filter_impl<Selector, IndexOffset+1, Rest...>::passed>::flat>;

    using passed_indexes = conditional_t<Selector<T>::value,
            typename __filter_impl<Selector, IndexOffset+1, Rest...>::passed_indexes::template prepend<IndexOffset>,
            typename __filter_impl<Selector, IndexOffset+1, Rest...>::passed_indexes>;

    using failed = conditional_t<Selector<T>::value,
            typename __params<typename __filter_impl<Selector, IndexOffset+1, Rest...>::failed>::flat,
            typename __params<T, typename __filter_impl<Selector, IndexOffset+1, Rest...>::failed>::flat>;

    using failed_indexes = conditional_t<Selector<T>::value,
            typename __filter_impl<Selector, IndexOffset+1, Rest...>::failed_indexes,
            typename __filter_impl<Selector, IndexOffset+1, Rest...>::failed_indexes::template prepend<IndexOffset>>;
};

/// \brief Helper class to filter parameter pack, using Selector to determinate if given type should be included in result
///
template <template <typename> class Selector, size_t IndexOffset, typename... T>
struct __filter_impl<Selector, IndexOffset, __params<T...>>
{
    using passed = typename __filter_impl<Selector, IndexOffset, T...>::passed;
    using passed_indexes = typename __filter_impl<Selector, IndexOffset, T...>::passed_indexes;
    using failed = typename __filter_impl<Selector, IndexOffset, T...>::failed;
    using failed_indexes = typename __filter_impl<Selector, IndexOffset, T...>::failed_indexes;
};

/// \brief Helper alias to make __filter_impl with IndexOffset = 0
///
template <template <typename> class Selector, typename... Types>
using __filter = __filter_impl<Selector, 0, Types...>;

#endif //Parameter pack storing and manipulating

#if _REGION ( Type decomposition )

/// \brief Helper class to determine the signature of function type
///
template <typename F>
struct __call_type
{
public:
    using args = __invalid_type;
    using ret = __invalid_type;
    using obj = __invalid_type;
};

/// \brief Helper class to determine the signature of function type
///
template <typename Ret, typename... Args>
struct __call_type<Ret(Args...)>
{
    using args = __params<Args...>;
    using ret = Ret;
    using obj = __invalid_type;
};

/// \brief Helper class to determine the signature of function type
///
template <class C, typename Ret, typename... Args>
struct __call_type<Ret(C::*)(Args...)>
{
    using args = __params<Args...>;
    using ret = remove_cv_t<Ret>;
    using obj = C*;
};

/// \brief Helper class to determine the signature of function type
///
template <class C, typename Ret, typename... Args>
struct __call_type<Ret(C::*)(Args...) const>
{
    using args = __params<Args...>;
    using ret = remove_cv_t<Ret>;
    using obj =  const C*;
};

/// \brief Helper class to determine the signature of function type
///
template <class C, typename Ret, typename... Args>
struct __call_type<Ret(C::*)(Args...) volatile>
{
    using args = __params<Args...>;
    using ret = remove_cv_t<Ret>;
    using obj = volatile C*;
};

/// \brief Helper class to determine the signature of function type
///
template <class C, typename Ret, typename... Args>
struct __call_type<Ret(C::*)(Args...) const volatile>
{
    using args = __params<Args...>;
    using ret = remove_cv_t<Ret>;
    using obj = const volatile C*;
};

#endif //Type decomposition

} //end namespace __details

} //end namespace cl

#undef _REGION
