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
#include <__ocl_enqueue_verify.h>
#include <__ocl_enqueue_helpers.h>
#include <__ocl_spirv_enqueue_opcodes.h>
#include <opencl_tuple>

#define _ENQUEUE_VALIDATION_ERROR(Fun, Args) \
    static_assert(__details::__no_local_ptr_arg<Fun, __details::__params<Args...>>::value, "local_ptr<T> cannot be passed directly to enqueue_kernel, use local_ptr<T>::size_type instead."); \
    static_assert(__details::__valid_params<Fun, __details::__params<Args...>>::value, "Function passed to enqueue_kernel could not be called with deduced arguments. Type mismatch, ambiguity overloads or invalid parameters count."); \
    static_assert(__details::__valid_return_type<Fun, __details::__params<Args...>>::value, "Invocation of enqueued function with deduced arguments does not return void!")


namespace cl
{

/// \brief Class representing dimension of enqueued workload
///
struct ndrange
{
    /// \brief Creates representation of one-dimensional ndrange, with given global size and both local size and global offset set to 0
    ///
    explicit ndrange( size_t global_work_size ) :
            dimension{ 1 },
            global_work_offset{ 0, 0, 0 },
            global_work_size{ global_work_size, 0, 0 },
            local_work_size{ 0, 0, 0 } { }

    /// \brief Creates representation of one-dimensional ndrange, with given global and local size and global offset set to 0
    ///
    ndrange( size_t global_work_size, size_t local_work_size ) :
            dimension{ 1 },
            global_work_offset{ 0, 0, 0 },
            global_work_size{ global_work_size, 0, 0 },
            local_work_size{ local_work_size, 0, 0 } { }

    /// \brief Creates representation of one-dimensional ndrange, with given global size, local size and global offset
    ///
    ndrange( size_t global_work_offset, size_t global_work_size, size_t local_work_size ) :
            dimension{ 1 },
            global_work_offset{ global_work_offset, 0, 0 },
            global_work_size{ global_work_size, 0, 0 },
            local_work_size{ local_work_size, 0, 0 } { }

    /// \brief Creates representation of N-dimensional ndrange, with given global size and both local size and global offset set to 0
    ///
    /// N should be 2 or 3
    template <size_t N>
    ndrange( const size_t (&global_work_size)[N] ) :
            dimension{ N },
            global_work_offset{ 0, 0, 0 },
            global_work_size{ global_work_size[0], global_work_size[1], N == 3 ? global_work_size[2] : 0 },
            local_work_size{ 0, 0, 0 }
    { static_assert( N == 2 || N == 3, "Invalid dimension" ); }

    /// \brief Creates representation of N-dimensional ndrange, with given global and local size and global offset set to 0
    ///
    /// N should be 2 or 3
    template <size_t N>
    ndrange( const size_t (&global_work_size)[N], const size_t (&local_work_size)[N] ) :
            dimension{ N },
            global_work_offset{ 0, 0, 0 },
            global_work_size{ global_work_size[0], global_work_size[1], N == 3 ? global_work_size[2] : 0 },
            local_work_size{ local_work_size[0], local_work_size[1], N == 3 ? global_work_size[2] : 0 }
    { static_assert( N == 2 || N == 3, "Invalid dimension" ); }

    /// \brief Creates representation of N-dimensional ndrange, with given global size, local size and global offset
    ///
    /// N should be 2 or 3
    template <size_t N>
    ndrange( const size_t (&global_work_offset)[N], const size_t (&global_work_size)[N], const size_t (&local_work_size)[N] ) :
            dimension{ N },
            global_work_offset{ global_work_offset[0], global_work_offset[1], N == 3 ? global_work_size[2] : 0 },
            global_work_size{ global_work_size[0], global_work_size[1], N == 3 ? global_work_size[2] : 0 },
            local_work_size{ local_work_size[0], local_work_size[1], N == 3 ? global_work_size[2] : 0 }
    { static_assert( N == 2 || N == 3, "Invalid dimension" ); }

private:
    int32_t dimension;
    size_t global_work_offset[3];
    size_t global_work_size[3];
    size_t local_work_size[3];
};

/// \brief Opaque class representing device enqueue event
///
struct event
{
    /// \brief default constructor
    ///
    event() { }

    /// \brief defaulted copy constructor, as defined in OpenCL C++ spec
    ///
    event(event const&) = default;

    /// \brief defaulted move constructor, as defined in OpenCL C++ spec
    ///
    event(event&&) = default;

    /// \brief defaulted copy assign operator, as defined in OpenCL C++ spec
    ///
    event& operator =(event const&) = default;

    /// \brief defaulted move assign operator, as defined in OpenCL C++ spec
    ///
    event& operator =(event&&) = default;

    __ALWAYS_INLINE bool is_valid() const __NOEXCEPT                { return __spirv::OpIsValidEvent(__this); }
    __ALWAYS_INLINE void retain() __NOEXCEPT                        { return __spirv::OpRetainEvent(__this); }
    __ALWAYS_INLINE void release() __NOEXCEPT                       { return __spirv::OpReleaseEvent(__this); }
    __ALWAYS_INLINE void set_status(event_status status) __NOEXCEPT { return __spirv::OpSetUserEventStatus(__this, static_cast<int>(status)); }

    __ALWAYS_INLINE explicit operator bool () const __NOEXCEPT      { return is_valid(); }

    template <typename T>
    __ALWAYS_INLINE void profiling_info(event_profiling_info name, global_ptr<T> value) __NOEXCEPT
    {
        return __spirv::OpCaptureEventProfilingInfo(__this, static_cast<int>(name), reinterpret_cast<__global void*>(value.get()));
    }

private:
    __global __spirv::OpTypeDeviceEvent* __this;

    friend event make_user_event();
    event(__global __spirv::OpTypeDeviceEvent* ptr) : __this(ptr) {}
};

/// \brief Class representing device enqueue queue
///
struct device_queue
{
    /// \brief deleted default constructor, as defined in OpenCL C++ spec
    ///
    device_queue() = delete;

    /// \brief defaulted copy constructor, as defined in OpenCL C++ spec
    ///
    device_queue(device_queue const&) = default;

    /// \brief defaulted move constructor, as defined in OpenCL C++ spec
    ///
    device_queue(device_queue&&) = default;

    /// \brief deleted copy assign operator, as defined in OpenCL C++ spec
    ///
    device_queue& operator = (device_queue const&) = delete;

    /// \brief deleted move assign operator, as defined in OpenCL C++ spec
    ///
    device_queue& operator = (device_queue&&) = delete;

    /// \brief deleted address-of operator, as defined in OpenCL C++ spec
    ///
    device_queue* operator & () = delete;

    /// \brief device enqueue function which enqueues given callable object 'fun' with set of arguments 'args...'
    ///
    /// If 'fun' expects local_ptr<T> argument, it should be given in 'args...' as local_ptr<T>::size (size_t value). During enqueueing memory necessary for holding up to
    /// given number of objects of type T will be allocated in local memory and passed as valid pointer to enqueued function. Passing local_ptr<T> value directly is
    /// forbidden.
    ///
    /// __details::__verify - enables this overload only if passed arguments form valid invocation of 'fun', fallbacks to overload below which prints detailed information about failure cause
    template <class Fun, class... Args>
    __ALWAYS_INLINE auto enqueue_kernel( enqueue_policy flag,
                         uint num_events_in_wait_list,
                         const event * event_wait_list,
                         event * event_ret,
                         const ndrange & ndrange,
                         Fun fun,
                         Args... args ) __NOEXCEPT
        -> enable_if_t<__details::__verify<Fun, __details::__params<Args...>>::value, enqueue_status>
    {
        return __details::__build_enqueue_helper_t<Fun, Args...>::__enqueue(
                __this,
                static_cast<int>(flag),
                ndrange,
                num_events_in_wait_list,
                reinterpret_cast<__global const __spirv::OpTypeDeviceEvent* const*>(event_wait_list),
                reinterpret_cast<__global __spirv::OpTypeDeviceEvent**>(event_ret),
                fun,
                forward_as_tuple(forward<Args&&>(args)...));
    }

    /// \brief device enqueue function which enqueues given callable object 'fun' with set of arguments 'args...'
    ///
    /// If 'fun' expects local_ptr<T> argument, it should be given in 'args...' as local_ptr<T>::size (size_t value). During enqueueing memory necessary for holding up to
    /// given number of objects of type T will be allocated in local memory and passed as valid pointer to enqueued function. Passing local_ptr<T> value directly is
    /// forbidden.
    ///
    /// !__details::__verify - enables this overload only as fallback in case of invocation failure, prints detailed information about failure cause
    template <class Fun, class... Args>
    __ALWAYS_INLINE auto enqueue_kernel( enqueue_policy flag,
                         uint num_events_in_wait_list,
                         const event * event_wait_list,
                         event * event_ret,
                         const ndrange & ndrange,
                         Fun fun,
                         Args... args )
        -> enable_if_t<!__details::__verify<Fun, __details::__params<Args...>>::value, enqueue_status>
    {
        _ENQUEUE_VALIDATION_ERROR(Fun, Args);
        return enqueue_status::failure;
    }

    /// \brief device enqueue function which enqueues given callable object 'fun' with set of arguments 'args...'
    ///
    /// If 'fun' expects local_ptr<T> argument, it should be given in 'args...' as local_ptr<T>::size_type (size_t value). During enqueueing memory necessary for holding up to
    /// given number of objects of type T will be allocated in local memory and passed as valid pointer to enqueued function. Passing local_ptr<T> value directly is
    /// forbidden.
    template <class Fun, class... Args>
    __ALWAYS_INLINE enqueue_status enqueue_kernel( enqueue_policy flag, const ndrange & ndrange, Fun fun, Args... args ) __NOEXCEPT
    {
        return enqueue_kernel(flag, 0, nullptr, nullptr, ndrange, fun, forward<Args&&>(args)...);
    }

    /// \brief device enqueue function which enqueues marker
    ///
    __ALWAYS_INLINE enqueue_status enqueue_marker(uint num_events_in_wait_list, const event * event_wait_list, event * event_ret) __NOEXCEPT
    {
        return __spirv::OpEnqueueMarker(__this, num_events_in_wait_list, reinterpret_cast<__global const __spirv::OpTypeDeviceEvent* const*>(event_wait_list), reinterpret_cast<__global __spirv::OpTypeDeviceEvent**>(event_ret));
    }

private:
    __global __spirv::OpTypeQueue* __this;

    friend device_queue get_default_device_queue();
    device_queue(__global __spirv::OpTypeQueue* ptr) : __this(ptr) {}
};


/// \brief standard function which allows user to create custom events, execution status of the user event is set to event_status::submitted
///
__ALWAYS_INLINE event make_user_event()
{
    return event{ __spirv::OpCreateUserEvent() };
}

/// \brief standard function which returns default device_queue object
///
__ALWAYS_INLINE device_queue get_default_device_queue()
{
    return  device_queue{ __spirv::OpGetDefaultQueue() };
}

/// \brief function which queries the maximum work-group size that can be used to execute given block
///
template <class Fun, class... Args>
__ALWAYS_INLINE enable_if_t<__details::__verify<Fun, __details::__params<Args...>>::value, uint> get_kernel_work_group_size(Fun fun, Args... args)
{
    using EnqueueHelper = __details::__build_enqueue_helper_t<Fun, Args...>;

    __private auto static_data = EnqueueHelper::__get_enqueue_kernel_static_data(move(fun), make_tuple(move(args)...));
    return static_cast<uint>(__spirv::OpGetKernelWorkGroupSize(EnqueueHelper::__get_enqueue_kernel_wrapper(), &static_data, 0, 0));
}

/// \brief fallback if given object 'fun' is not invokable with given arguments
///
template <class Fun, class... Args>
__ALWAYS_INLINE enable_if_t<!__details::__verify<Fun, __details::__params<Args...>>::value, uint> get_kernel_work_group_size(Fun fun, Args... args)
{
    _ENQUEUE_VALIDATION_ERROR(Fun, Args);
    return 0;
}

/// \brief function which returns preferred multiple of work-group size for launch.
///
template <class Fun, class... Args>
__ALWAYS_INLINE enable_if_t<__details::__verify<Fun, __details::__params<Args...>>::value, uint> get_kernel_preferred_work_group_size_multiple(Fun fun, Args... args)
{
    using EnqueueHelper = __details::__build_enqueue_helper_t<Fun, Args...>;

    __private auto static_data = EnqueueHelper::__get_enqueue_kernel_static_data(move(fun), make_tuple(move(args)...));
    return static_cast<uint>(__spirv::OpGetKernelPreferredWorkGroupSizeMultiple(EnqueueHelper::__get_enqueue_kernel_wrapper(), &static_data, 0, 0));
}

/// \brief fallback if given object 'fun' is not invokable with given arguments
///
template <class Fun, class... Args>
__ALWAYS_INLINE enable_if_t<!__details::__verify<Fun, __details::__params<Args...>>::value, uint> get_kernel_preferred_work_group_size_multiple(Fun fun, Args... args)
{
    _ENQUEUE_VALIDATION_ERROR(Fun, Args);
    return 0;
}

/// \brief function which returns the number of sub-groups in each work-group of the dispatch.
///
template <class Fun, class... Args>
__ALWAYS_INLINE enable_if_t<__details::__verify<Fun, __details::__params<Args...>>::value, uint> get_kernel_sub_group_count_for_ndrange(const ndrange & ndrange, Fun fun, Args... args)
{
    using EnqueueHelper = __details::__build_enqueue_helper_t<Fun, Args...>;

    __private auto static_data = EnqueueHelper::__get_enqueue_kernel_static_data(move(fun), make_tuple(move(args)...));
    return static_cast<uint>(__spirv::OpGetKernelNDrangeSubGroupCount(ndrange, EnqueueHelper::__get_enqueue_kernel_wrapper(), &static_data, 0, 0));
}

/// \brief fallback if given object 'fun' is not invokable with given arguments
///
template <class Fun, class... Args>
__ALWAYS_INLINE enable_if_t<!__details::__verify<Fun, __details::__params<Args...>>::value, uint> get_kernel_sub_group_count_for_ndrange(const ndrange & ndrange, Fun fun, Args... args)
{
    _ENQUEUE_VALIDATION_ERROR(Fun, Args);
    return 0;
}

/// \brief funtion which returns the maximum sub-group size for a lambda
///
template <class Fun, class... Args>
__ALWAYS_INLINE enable_if_t<__details::__verify<Fun, __details::__params<Args...>>::value, uint> get_kernel_max_sub_group_size_for_ndrange(const ndrange & ndrange, Fun fun, Args... args)
{
    using EnqueueHelper = __details::__build_enqueue_helper_t<Fun, Args...>;

    __private auto static_data = EnqueueHelper::__get_enqueue_kernel_static_data(move(fun), make_tuple(move(args)...));
    return static_cast<uint>(__spirv::OpGetKernelNDrangeMaxSubGroupSize(ndrange, EnqueueHelper::__get_enqueue_kernel_wrapper(), &static_data, 0, 0));
}

/// \brief fallback if given object 'fun' is not invokable with given arguments
///
template <class Fun, class... Args>
__ALWAYS_INLINE enable_if_t<!__details::__verify<Fun, __details::__params<Args...>>::value, uint> get_kernel_max_sub_group_size_for_ndrange(const ndrange & ndrange, Fun fun, Args... args)
{
    _ENQUEUE_VALIDATION_ERROR(Fun, Args);
    return 0;
}

/// \brief function which returns a valid local size that would produce the requested number of sub-groups such that each sub-group is complete with no partial sub-groups
template <class Fun, class... Args>
__ALWAYS_INLINE enable_if_t<__details::__verify<Fun, __details::__params<Args...>>::value, uint> get_kernel_local_size_for_sub_group_count(uint num_sub_groups, Fun fun, Args... args)
{
    using EnqueueHelper = __details::__build_enqueue_helper_t<Fun, Args...>;

    __private auto static_data = EnqueueHelper::__get_enqueue_kernel_static_data(move(fun), make_tuple(move(args)...));
    return static_cast<uint>(__spirv::OpGetKernelLocalSizeForSubgroupCount(num_sub_groups, EnqueueHelper::__get_enqueue_kernel_wrapper(), &static_data, 0, 0));
}

/// \brief fallback if given object 'fun' is not invokable with given arguments
///
template <class Fun, class... Args>
__ALWAYS_INLINE enable_if_t<!__details::__verify<Fun, __details::__params<Args...>>::value, uint> get_kernel_local_size_for_sub_group_count(uint num_sub_groups, Fun fun, Args... args)
{
    _ENQUEUE_VALIDATION_ERROR(Fun, Args);
    return 0;
}

/// \brief function which provides a mechanism to query the maximum number of sub-groups that can be used to execute the passed lambda
///
template <class Fun, class... Args>
__ALWAYS_INLINE enable_if_t<__details::__verify<Fun, __details::__params<Args...>>::value, uint> get_kernel_max_num_sub_groups(Fun fun, Args... args)
{
    using EnqueueHelper = __details::__build_enqueue_helper_t<Fun, Args...>;

    __private auto static_data = EnqueueHelper::__get_enqueue_kernel_static_data(move(fun), make_tuple(move(args)...));
    return static_cast<uint>(__spirv::OpGetKernelMaxNumSubgroups(EnqueueHelper::__get_enqueue_kernel_wrapper(), &static_data, 0, 0));
}

/// \brief fallback if given object 'fun' is not invokable with given arguments
///
template <class Fun, class... Args>
__ALWAYS_INLINE enable_if_t<!__details::__verify<Fun, __details::__params<Args...>>::value, uint> get_kernel_max_num_sub_groups(Fun fun, Args... args)
{
    _ENQUEUE_VALIDATION_ERROR(Fun, Args);
    return 0;
}

#undef _ENQUEUE_VALIDATION_ERROR

} //end namespace cl
