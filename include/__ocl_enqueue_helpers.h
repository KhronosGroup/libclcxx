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

/*
** This file contains all logic related with kernel enqueueing.
** Please note that verification is outside of this file's scope since it's performed at the time of calling main 'enqueu_kernel' function from OpTypeQueue class.
*/

#include <__ocl_config.h>
#include <__ocl_enqueue_verify.h>
#include <__ocl_spirv_enqueue_opcodes.h>
#include <opencl_tuple>

namespace cl
{
namespace __details
{

/// \brief Helper function wrapping passed function and its arguments to kernel call
///
template <class WrapperLambda, class... LocalPtrs>
static void __enqueue_kernel_wrapper(__private void* wrapping_lambda, LocalPtrs... locals)
{
    reinterpret_cast<__private WrapperLambda*>(wrapping_lambda)->operator()(move(locals)...);
}

/// \brief Helper structure used while merging two already merged sequences
///
template <size_t SeqIdx, size_t InSeqIdx>
struct __merge_pos { };

/// \brief Helper structure which exposes member typedef 'type' holding sequence of '__merge_pos' structures.
///
/// This definition handles case when both sequences have been already exhausted.
/// Generated sequence is used in __merge implementation.
template <typename Seq1, size_t Seq1Offset, typename Seq2, size_t Seq2Offset>
struct __make_merge_pos_sequence { using type = __params<>; };

/// \brief Helper structure which exposes member typedef 'type' holding sequence of '__merge_pos' structures.
///
/// This definition handles case when both sequences have at least one element (needs to compare them)
template <size_t Seq1E, size_t... Seq1Rest, size_t Seq1Offset,
          size_t Seq2E, size_t... Seq2Rest, size_t Seq2Offset>
struct __make_merge_pos_sequence<__size_t_seq<Seq1E, Seq1Rest...>, Seq1Offset,
               __size_t_seq<Seq2E, Seq2Rest...>, Seq2Offset>
{
    using AppendFirst = typename __params<
            __merge_pos<0, Seq1Offset>,
            typename __make_merge_pos_sequence<__size_t_seq<Seq1Rest...>, Seq1Offset + 1,
                                               __size_t_seq<Seq2E, Seq2Rest...>, Seq2Offset>::type
        >::flat;

    using AppendSecond = typename __params<
            __merge_pos<1, Seq2Offset>,
            typename __make_merge_pos_sequence<__size_t_seq<Seq1E, Seq1Rest...>, Seq1Offset,
                                               __size_t_seq<Seq2Rest...>, Seq2Offset + 1>::type
        >::flat;

    using type = conditional_t<(Seq1E < Seq2E), AppendFirst, AppendSecond>;
};

/// \brief Helper structure which exposes member typedef 'type' holding sequence of '__merge_pos' structures.
///
/// This definition handles case when only the second sequence has been exhausted.
template <size_t Seq1E, size_t... Seq1Rest, size_t Seq1Offset, size_t Seq2Offset>
struct __make_merge_pos_sequence<__size_t_seq<Seq1E, Seq1Rest...>, Seq1Offset, __size_t_seq<>, Seq2Offset>
{
    using type = typename __params<
            __merge_pos<0, Seq1Offset>,
            typename __make_merge_pos_sequence<__size_t_seq<Seq1Rest...>, Seq1Offset + 1,
                                               __size_t_seq<>, Seq2Offset>::type
        >::flat;
};

/// \brief Helper structure which exposes member typedef 'type' holding sequence of '__merge_pos' structures.
///
/// This definition handles case when only the first sequence has been exhausted.
template <size_t Seq1Offset, size_t Seq2E, size_t... Seq2Rest, size_t Seq2Offset>
struct __make_merge_pos_sequence<__size_t_seq<>, Seq1Offset, __size_t_seq<Seq2E, Seq2Rest...>, Seq2Offset>
{
    using type = typename __params<
            __merge_pos<1, Seq2Offset>,
            typename __make_merge_pos_sequence<__size_t_seq<>, Seq1Offset,
                                               __size_t_seq<Seq2Rest...>, Seq2Offset + 1>::type
        >::flat;
};

/// \brief Forward declaration of helper __merge structure. It's supposed to take single __merge_pos (see specialization below)
///
/// Having two tuples and __merge_pos<I, J> given __merge returns J-th element from I-th tuple.
/// __merge together with __merge_pos and __make_merge_pos_sequence provide nice way to merge previously split tuple.
/// For example lets start with tuple t0 with 5 elements (we will use indexes to identify them):
///   <0, 1, 2, 3, 4> -- sequence of elements handled by t0
/// Later on this tuple has been split in two new tuples t1 and t2:
///   <0, 2, 3> -- sequence of elements handled by t1
///   rest, i.e. <1, 4> --sequence of elements handled by t2
/// As long as we remember mapping from t0 to t1 (mapping to t2 is therefore also known) we can obtain reversed mapping by using __make_merge_pos_sequence<t1, t2>.
/// As a result we would obtain sequence of two-dimensional indexes, for our example as follows:
///   <0, 0>        -- first element from t1 == 0 in original sequence
///   <1, 0>        -- first element from t2 == 1 in original sequence
///   <0, 1>        -- second element from t1 == 2 in original sequence
///   <0, 2>        -- third element from t1 == 3 in original sequence
///   <1, 1>        -- second element from t2 == 4 in original sequence
/// Let's identify this sequence as M. By having M we can merge back tuples t1 and t2 to form original tuple t0 by expanding __merge::__get for each element in M.
///   t0 = make_tuple(__merge<M>::__get(t1, t2)...);
template <typename MergePos>
struct __merge;

/// \ brief Implementation of __merge helper structure used to fetch single element from two tuples depending on provided two-dimensional index (__merge_pos)
///
/// Specialization when taking element from first tuple
template <size_t InTupleIdx>
struct __merge<__merge_pos<0, InTupleIdx>>
{
    template <typename... T, typename... U>
    __ALWAYS_INLINE static auto __get(tuple<T...> const& t, tuple<U...> const&u) -> decltype(get<InTupleIdx>(t))
    {
        return get<InTupleIdx>(t);
    }
};

/// \ brief Implementation of __merge helper structure used to fetch single element from two tuples depending on provided two-dimensional index (__merge_pos)
///
/// Specialization when taking element from second tuple
template <size_t InTupleIdx>
struct __merge<__merge_pos<1, InTupleIdx>>
{
    template <typename... T, typename... U>
    __ALWAYS_INLINE static auto __get(tuple<T...> const& t, tuple<U...> const&u) -> decltype(get<InTupleIdx>(u))
    {
        return get<InTupleIdx>(u);
    }
};

/// \brief Forward declaration of __enqueue_helper struct, used to create storage for spliting and merging back arguments passed to enqueue_kernel
///
/// template parameters named as *Pack are supposed to be __params<T...> and *Seq to be __size_t_seq<I...>. Fun is funtor object passed to enqueue_kernel.
template <class Fun,
          class PointersTyPack,
          class PointersIdxSeq,
          class NonPointersIdxSeq,
          class MergePosTyPack,
          class ArgsPack>
struct __enqueue_helper;

/// \brief Forward declaration of __enqueue_helper struct, used to create storage for spliting and merging back arguments passed to enqueue_kernel
///
/// PointersTy are all local_ptr<T> types from signature of Fun::operator (), in order of appearance on arguments list
/// PointersIdx are indexes of PointersTy within arguments list of Fun::operator (), where first argument has index 0, also in order of appearance
/// NonPointersIdx are indexes of all other arguments, also in order of appearance
/// MergePosTy is sequence of __merge_pos two-dimensional indexes used to merge back Pointers and NonPointers in order to call original Fun::operator () (see __merge)
/// Args are types of argument passed directly to enqueue_kernel (validation if they match types deducted from signature of Fun::operator () should be made before using this helper)
template <class Fun,
          class... PointersTy,
          size_t... PointersIdx,
          size_t... NonPointersIdx,
          class... MergePosTy,
          class... Args>
struct __enqueue_helper<Fun,
                        __params<PointersTy...>,
                        __size_t_seq<PointersIdx...>,
                        __size_t_seq<NonPointersIdx...>,
                        __params<MergePosTy...>,
                        __params<Args...>>
{
    __ALWAYS_INLINE static auto __get_enqueue_kernel_static_data(Fun&& fun, tuple<Args...>&& args)
    {
        auto&& data = make_tuple(get<NonPointersIdx>(move(args))...);

        // create merging lambda, which holds original function, captured data and gets local_ptr by arguments
        return [fun, data](PointersTy... ptrs) mutable {
            // merge captured data with given local_ptr and call original functor
            invoke(fun, __merge<MergePosTy>::__get(forward_as_tuple(move(ptrs)...), data)...);
        };
    }

    __ALWAYS_INLINE static auto& __get_enqueue_kernel_wrapper()
    {
        return __enqueue_kernel_wrapper<decltype(__get_enqueue_kernel_static_data(declval<Fun>(), declval<tuple<Args...>&&>())), PointersTy...>;
    }

    /// \brief backend for kernel_enqueue, splits passed arguments into trivial arguments and group of local_ptr<T>::size_type,
    /// first is captured into single data block (alongside enqueued object) and latter is passed directly to SPIRV intrinsic.
    /// Passed callable object is enqueued indirectly via data block which is firstly unpacked by wrapping lambda, which also
    /// merge back captured trivial arguments with formed by runtime group of local_ptr<T>, in the end enqueued object is called.
    __ALWAYS_INLINE static enqueue_status __enqueue(
        __global __spirv::OpTypeQueue* queue,
        int flag,
        const ndrange& nd,
        uint num_events_in_wait_list,
        __global const __spirv::OpTypeDeviceEvent* const* event_wait_list,
        __global __spirv::OpTypeDeviceEvent** event_ret,
        Fun fun,
        tuple<Args...>&& args)
    {
        // capture all data which are not local_ptr<T>
        __private auto static_data = __get_enqueue_kernel_static_data(move(fun), move(args));

        // enqueue 'kernel' wrapper, pass wrapping_lambda as void* block of data and size_t arguments as separate arguments to form valid pointers on called kernel's side
        return __spirv::OpEnqueueKernel(
            queue,
            flag,
            nd,
            num_events_in_wait_list,
            event_wait_list,
            event_ret,
            __get_enqueue_kernel_wrapper(),
            &static_data,
            0,
            0,
            static_cast<size_t>(get<PointersIdx>(args))...); //pass size_t arguments
    }
};

template <class Fun, class... Args>
struct __build_enqueue_helper
{
    using ParamsTy = typename __deduce_params<Fun, __params<Args...>>::args;
    using PointersTy = typename __filter<__is_local_ptr, ParamsTy>::passed;
    using PointersIdx = typename __filter<__is_local_ptr, ParamsTy>::passed_indexes;
    using NonPointersIdx = typename __filter<__is_local_ptr, ParamsTy>::failed_indexes;
    using MergePosTy = typename __make_merge_pos_sequence<PointersIdx, 0, NonPointersIdx, 0>::type;

    using type = __enqueue_helper<
            Fun,
            PointersTy,
            PointersIdx,
            NonPointersIdx,
            MergePosTy,
            __params<Args...>
        >;
};

template <class Fun, class... Args>
using __build_enqueue_helper_t = typename __build_enqueue_helper<Fun, Args...>::type;

} //end namespace details
} //end namespace cl
