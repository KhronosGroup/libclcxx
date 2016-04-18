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

#include <opencl_memory>
#include <opencl_type_traits>

namespace cl
{
namespace __details
{

/// \brief Helper trait which checks if given type has member typedef 'type'
///
template <typename T>
struct __has_member_typedef_type
{
private:
    template <typename U>
    static true_type helper(typename U::type*);

    template <typename U>
    static false_type helper(...);

public:
    static constexpr bool value = decltype(helper<T>(nullptr))::value;

    constexpr operator bool() const { return value; }
    constexpr bool operator ()() const { return value; }
};

/// \brief Helper structure which enables passing of __params structure to result_of standard trait
///
template <typename F, typename P>
struct __result_of;

/// \brief Helper structure which enables passing of __params structure to result_of standard trait
///
template <typename F, typename... P>
struct __result_of<F, __params<P...>>
{
    typedef result_of_t<F(P...)> type;
};

/// \brief Helper structure which checks if invoke(Fun, Args...) is valid
///
/// takes Args... through __params structure
template <typename Fun, typename Args>
struct __is_invokeable;

/// \brief Helper structure which checks if invoke(Fun, Args...) is valid
///
/// takes Args... through __params structure
template <typename Fun, typename... Args>
struct __is_invokeable<Fun,__params<Args...>> : public __has_member_typedef_type<result_of<Fun(Args...)>> { };

/// \brief Helper structure which checks if type T, passed as argument to enqueue_kernel, is local_ptr.
/// if it's not, structure also contains member typedef 'deduced_param_t' which names deduced parameter type in functor signature
///
/// default case - deduced param is the same as passed argument
template <typename T>
struct __is_local_ptr
{
    static constexpr bool value = false;
    typedef T deduced_param_t;
};

/// \brief Helper structure which checks if type T, passed as argument to enqueue_kernel, is local_ptr.
/// if it's not, structure also contains member typedef 'deduced_param_t' which names deduced parameter type in functor signature
///
/// if __local_ptr_size was passed as argument, deduce parameter to be appropriate local_ptr
template <typename T>
struct __is_local_ptr<__local_ptr_size<T>>
{
    static constexpr bool value = false;
    typedef local_ptr<T> deduced_param_t;
};

/// \brief Helper structure which checks if type T, passed as argument to enqueue_kernel, is local_ptr.
/// if it's not, structure also contains member typedef 'deduced_param_t' which names deduced parameter type in functor signature
///
/// local_ptr was passed as argument which is an error, don't try to deduce param's type
template <typename T>
struct __is_local_ptr<local_ptr<T>>
{
    static constexpr bool value = true;
};

/// \brief Helper structure which checks if Fun is callable with sizeof...(Args) arguments
///
template <typename Fun, typename ArgsPack>
struct __valid_args_num : public __is_invokeable<Fun, typename __gen_params<__any_type, ArgsPack::size>::type> { };

/// \brief Helper structure which checks if Args... doesn't contain local_ptr
///
template <typename Fun, typename ArgsPack>
struct __no_local_ptr_arg;

template <typename Fun, typename... Args>
struct __no_local_ptr_arg<Fun, __params<Args...>> : public integral_constant<bool, !__any<__is_local_ptr<Args>::value...>::value> { };

/// \brief Helper structure which deduces Fun's parameters from passed Args... (i.e. converts local_ptr's placeholder to local_ptr)
///
/// note: Fun should be callable with sizeof...(Args) arguments and Args... should not contain any local_ptr type
template <typename Fun, typename ArgsPack>
struct __deduce_params;

/// \brief Helper structure which deduces Fun's parameters from passed Args... (i.e. converts local_ptrs' placeholders to local_ptrs)
///
/// note: Args... should not contain any local_ptr type
template <typename Fun, typename... Args>
struct __deduce_params<Fun, __params<Args...>>
{
    typedef __params<typename __is_local_ptr<Args>::deduced_param_t...> args;
};

/// \brief Helper structure which checks if Fun is callable witch arguments deduces from Args... (i.e. with local_ptrs' placeholders replaced with local_ptrs)
///
template <typename Fun, typename ArgsPack, bool = __no_local_ptr_arg<Fun,ArgsPack>::value>
struct __valid_params : public __is_invokeable<Fun, typename __deduce_params<Fun, ArgsPack>::args>
{
};

/// \brief Do not report invocation failure if local_ptr was passed directly as argument
///
template <typename Fun, typename ArgsPack>
struct __valid_params<Fun, ArgsPack, false> : public true_type { };

/// \brief Helper structure which checks if return type of invoke(Fun,deduced_args) is void
///
template <typename Fun, typename ArgsPack, bool = __no_local_ptr_arg<Fun,ArgsPack>::value && __valid_params<Fun, ArgsPack>::value>
struct __valid_return_type : public is_void<typename __result_of<Fun,typename __deduce_params<Fun, ArgsPack>::args>::type> { };

/// \brief Do not check return type if some other errors are already diagnosed
///
template <typename Fun, typename ArgsPack>
struct __valid_return_type<Fun, ArgsPack, false> : public true_type { };

/// \brief Helper structure which combine all previous checks - it tells if given Fun,Args... may be used in enqueue_kernel
///
template <class Fun, class ArgsPack>
struct __verify : public integral_constant<bool,
                                           __no_local_ptr_arg<Fun, ArgsPack>::value &&
                                           __valid_params<Fun, ArgsPack>::value &&
                                           __valid_return_type<Fun, ArgsPack>::value>
{ };

} //details
} //cl
