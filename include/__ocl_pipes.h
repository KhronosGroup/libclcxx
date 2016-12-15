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

#include <__ocl_pipes_enums.h>
#include <__ocl_marker_type.h>
#include <__ocl_spirv_pipe_opcodes.h>
#include <__ocl_type_traits_type_properties.h>
#include <__ocl_type_traits_type_generators.h>

namespace cl
{
template <class T, pipe_access Access>
class pipe;

namespace __details
{
/// \brief Helper trait to select the OpCreatePipeFromPipeStorage function which creates a pipe with read access
///
template<pipe_access Access = pipe_access::read>
struct __choose_create_pipe_from_pipe_storage
{
    __ALWAYS_INLINE static __global __spirv::OpTypePipe<__spirv::AccessQualifier::Read>* __make_call(__global const __spirv::OpTypePipeStorage* p) __NOEXCEPT
    {
        return __spirv::OpCreatePipeFromPipeStorage_read(p);
    }
};

/// \brief Helper trait to select the OpCreatePipeFromPipeStorage function which creates a pipe with write access
///
template<>
struct __choose_create_pipe_from_pipe_storage<pipe_access::write>
{
    __ALWAYS_INLINE static __global __spirv::OpTypePipe<__spirv::AccessQualifier::Write>* __make_call(__global const __spirv::OpTypePipeStorage* p) __NOEXCEPT
    {
        return __spirv::OpCreatePipeFromPipeStorage_write(p);
    }
};

template<int S, int A, int C>
struct OpConstantPipeStorage_Creator
{
    static __spirv::OpConstantPipeStorage value;
};

template<int S, int A, int C>
__spirv::OpConstantPipeStorage OpConstantPipeStorage_Creator<S, A, C>::value(S, A, C);

}

/// \brief Class representing pipe storages / program scope pipes
///
template<class T, size_t N>
class pipe_storage: marker_type
{
public:
    static_assert(is_pod<T>::value, "Template parameter T in pipe_storage does not satisfy POD type requirements.");

    constexpr pipe_storage() __global: _handle(
        // force evaluation as constant value (if possible)
        __builtin_constant_p((__global const __spirv::OpTypePipeStorage*)(&__details::OpConstantPipeStorage_Creator<static_cast<int>(sizeof(T)), static_cast<int>(alignof(T)), static_cast<int>(N)>::value))
            ? (__global const __spirv::OpTypePipeStorage*)(&__details::OpConstantPipeStorage_Creator<static_cast<int>(sizeof(T)), static_cast<int>(alignof(T)), static_cast<int>(N)>::value)
            : (__global const __spirv::OpTypePipeStorage*)(&__details::OpConstantPipeStorage_Creator<static_cast<int>(sizeof(T)), static_cast<int>(alignof(T)), static_cast<int>(N)>::value)
    ) { }

    /// \brief Copy constructor of pipe storage class must be defaulted per OpenCL C++ spec.
    ///
    pipe_storage(const pipe_storage&) __global = default;

    /// \brief Move constructor of pipe storage class must be defaulted per OpenCL C++ spec.
    ///
    pipe_storage(pipe_storage&&) __global = default;

    /// \brief Copy assignment operator of pipe storage class must be deleted per OpenCL C++ spec.
    ///
    pipe_storage& operator=(const pipe_storage&) = delete;

    /// \brief Move assignment operator of pipe storage class must be deleted per OpenCL C++ spec.
    ///
    pipe_storage& operator=(pipe_storage&&) = delete;

    /// \brief Address-of operator of pipe storage class must be deleted per OpenCL C++ spec.
    ///
    pipe_storage* operator&() = delete;

    /// \brief Constructs a read only or write only pipe from pipe_storage object.
    ///
    template<pipe_access Access = pipe_access::read>
    __ALWAYS_INLINE pipe<T, Access> get() const __NOEXCEPT
    {
        return pipe<T, Access>(__details::__choose_create_pipe_from_pipe_storage<Access>::__make_call(_handle));
    }

private:
    __global const __spirv::OpTypePipeStorage* _handle;
};

// \brief Class representing read only pipes
///
template <class T, pipe_access Access = pipe_access::read>
class pipe : marker_type
{
public:
    static_assert(is_pod<T>::value, "Template parameter T in pipe does not satisfy POD type requirements.");

    typedef T element_type;
    static constexpr pipe_access access = Access;

    /// \brief Class representing read only reservations
    ///
    template<memory_scope S>
    class reservation : marker_type
    {
    public:
        static_assert(S == memory_scope::memory_scope_work_item || S == memory_scope::memory_scope_work_group || S == memory_scope::memory_scope_sub_group, "Invalid memory scope.");

        /// \brief Default constructor of reservation class must be deleted per OpenCL C++ spec.
        ///
        reservation() = delete;

        /// \brief Copy constructor of reservation class must be defaulted per OpenCL C++ spec.
        ///
        reservation(const reservation&) = default;

        /// \brief Move constructor of reservation class must be defaulted per OpenCL C++ spec.
        ///
        reservation(reservation&&) = default;

        /// \brief Copy assignment operator of reservation class must be deleted per OpenCL C++ spec.
        ///
        reservation& operator=(const reservation&) = delete;

        /// \brief Move assignment operator of reservation class must be deleted per OpenCL C++ spec.
        ///
        reservation& operator=(reservation&&) = delete;

        /// \brief Address-of operator of reservation class must be deleted per OpenCL C++ spec.
        ///
        reservation* operator&() = delete;

        /// \brief Tests if reservation object is valid
        ///
        __ALWAYS_INLINE bool is_valid() const __NOEXCEPT
        {
            return __spirv::__make_OpIsValidReserveId_call<bool>(_reserve_id);
        }

        /// \brief Tests if reservation object is valid. This operator has the same behavior as is_valid.
        ///
        __ALWAYS_INLINE explicit operator bool() const __NOEXCEPT
        {
            return is_valid();
        }

        /// \brief Performs read packet from the reserved area of the pipe referred to by index into ref.
        ///
        __ALWAYS_INLINE bool read(uint index, T& ref) const __NOEXCEPT
        {
            return __spirv::__make_OpReservedReadPipe_call<int>(_pipe, _reserve_id, index, (void *)&ref, static_cast<unsigned int>(sizeof(T)), static_cast<unsigned int>(alignof(T)));
        }

        /// \brief Commits read associated with reservation
        ///
        template<memory_scope K = S>
        __ALWAYS_INLINE enable_if_t<K == memory_scope::memory_scope_work_item> commit() __NOEXCEPT
        {
            __spirv::__make_OpCommitReadPipe_call<void>(_pipe, _reserve_id, static_cast<unsigned int>(sizeof(T)), static_cast<unsigned int>(alignof(T)));
        }

        /// \brief Commits read associated with reservation returned by work_group_reserve or sub_group_reserve
        ///
        template<memory_scope K = S>
        __ALWAYS_INLINE enable_if_t<K != memory_scope::memory_scope_work_item> commit() __NOEXCEPT
        {
            __spirv::__make_OpGroupCommitReadPipe_call<void>(S, _pipe, _reserve_id, static_cast<unsigned int>(sizeof(T)), static_cast<unsigned int>(alignof(T)));
        }

    protected:
        friend reservation<memory_scope::memory_scope_work_item> pipe<T, access>::reserve(uint num_packets) const __NOEXCEPT;
        friend reservation<memory_scope::memory_scope_work_group> pipe<T, access>::work_group_reserve(uint num_packets) const __NOEXCEPT;
        friend reservation<memory_scope::memory_scope_sub_group> pipe<T, access>::sub_group_reserve(uint num_packets) const __NOEXCEPT;

        reservation(__global const __spirv::OpTypePipe<__spirv::AccessQualifier::Read>* p, __global const __spirv::OpTypeReserveId* rid) : _pipe(p), _reserve_id(rid) {}

    private:
        __global const __spirv::OpTypePipe<__spirv::AccessQualifier::Read>* _pipe;
        __global const __spirv::OpTypeReserveId* _reserve_id;
    };

    /// \brief Default constructor of pipe class must be deleted per OpenCL C++ spec.
    ///
    pipe() = delete;

    /// \brief Copy constructor of pipe class must be defaulted per OpenCL C++ spec.
    ///
    pipe(const pipe&) = default;

    /// \brief Move constructor of pipe class must be defaulted per OpenCL C++ spec.
    ///
    pipe(pipe&&) = default;

    /// \brief Copy assignment operator of pipe class must be deleted per OpenCL C++ spec.
    ///
    pipe& operator=(const pipe&) = delete;

    /// \brief Move assignment operator of pipe class must be deleted per OpenCL C++ spec.
    ///
    pipe& operator=(pipe&&) = delete;

    /// \brief Address-of operator of pipe class must be deleted per OpenCL C++ spec.
    ///
    pipe* operator&() = delete;

    /// \brief Performs read on a pipe, returns true on success and false on failure
    ///
    __ALWAYS_INLINE bool read(T & ret) const __NOEXCEPT
    {
        return __spirv::__make_OpReadPipe_call<int>(_handle, (void *)&ret, static_cast<unsigned int>(sizeof(T)), static_cast<unsigned int>(alignof(T)));
    }

    /// \brief Reserves read on a pipe, returns valid reservation object if operation succeeded
    ///
    __ALWAYS_INLINE reservation<memory_scope::memory_scope_work_item> reserve(uint num_packets) const __NOEXCEPT
    {
        return{ _handle, __spirv::__make_OpReserveReadPipePackets_call<__global __spirv::OpTypeReserveId*>(_handle, num_packets, static_cast<unsigned int>(sizeof(T)), static_cast<unsigned int>(alignof(T))) };
    }

    /// \brief Reserves read on a pipe, returns valid reservation object if operation succeeded
    ///
    /// This operation has to be encountered by all items
    /// in a work-group with the same arguments otherwise the behavior is undefined
    __ALWAYS_INLINE reservation<memory_scope::memory_scope_work_group> work_group_reserve(uint num_packets) const __NOEXCEPT
    {
        return{ _handle, __spirv::__make_OpGroupReserveReadPipePackets_call<__global __spirv::OpTypeReserveId*>(memory_scope::memory_scope_work_group, _handle, num_packets, static_cast<unsigned int>(sizeof(T)), static_cast<unsigned int>(alignof(T))) };
    }

    /// \brief Reserves read on a pipe, returns valid reservation object if operation succeeded
    ///
    /// This operation has to be encountered by all items
    /// in a sub-group with the same arguments otherwise the behavior is undefined
    __ALWAYS_INLINE reservation<memory_scope::memory_scope_sub_group> sub_group_reserve(uint num_packets) const __NOEXCEPT
    {
        return{ _handle, __spirv::__make_OpGroupReserveReadPipePackets_call<__global __spirv::OpTypeReserveId*>(memory_scope::memory_scope_sub_group, _handle, num_packets, static_cast<unsigned int>(sizeof(T)), static_cast<unsigned int>(alignof(T))) };
    }

    /// \brief Returns number of packets that are currently stored in a pipe
    ///
    /// Please note that this value is already outdated at the point of return according to OCL C++ specification
    __ALWAYS_INLINE uint num_packets() const __NOEXCEPT
    {
        return __spirv::__make_OpGetNumPipePackets_call<unsigned int>(_handle, static_cast<unsigned int>(sizeof(T)), static_cast<unsigned int>(alignof(T)));
    }

    /// \brief Returns maximum number of packets that can be stored in a pipe
    ///
    __ALWAYS_INLINE uint max_packets() const __NOEXCEPT
    {
        return __spirv::__make_OpGetMaxPipePackets_call<unsigned int>(_handle, static_cast<unsigned int>(sizeof(T)), static_cast<unsigned int>(alignof(T)));
    }

protected:
    template<class P, size_t N>
    friend class pipe_storage;

    pipe(__global __spirv::OpTypePipe<__spirv::AccessQualifier::Read>* handle) : _handle(handle) { }

private:
    __global __spirv::OpTypePipe<__spirv::AccessQualifier::Read> * _handle;
};

/// \brief Class representing write only pipes
///
template <class T>
class pipe<T, pipe_access::write> : marker_type
{
public:
    static_assert(is_pod<T>::value, "Template parameter T in pipe does not satisfy POD type requirements.");

    typedef T element_type;
    static constexpr pipe_access access = pipe_access::write;

    /// \brief Class representing write only reservations
    ///
    template<memory_scope S>
    class reservation : marker_type
    {
    public:
        static_assert(S == memory_scope::memory_scope_work_item || S == memory_scope::memory_scope_work_group || S == memory_scope::memory_scope_sub_group, "Invalid memory scope.");

        /// \brief Default constructor of reservation class must be deleted per OpenCL C++ spec.
        ///
        reservation() = delete;

        /// \brief Copy constructor of reservation class must be defaulted per OpenCL C++ spec.
        ///
        reservation(const reservation&) = default;

        /// \brief Move constructor of reservation class must be defaulted per OpenCL C++ spec.
        ///
        reservation(reservation&&) = default;

        /// \brief Copy assignment operator of reservation class must be deleted per OpenCL C++ spec.
        reservation& operator=(const reservation&) = delete;

        /// \brief Move assignment operator of reservation class must be deleted per OpenCL C++ spec.
        ///
        reservation& operator=(reservation&&) = delete;

        /// \brief Address-of operator of reservation class must be deleted per OpenCL C++ spec.
        ///
        reservation* operator&() = delete;

        /// \brief Tests if reservation object is valid
        ///
        __ALWAYS_INLINE bool is_valid() const __NOEXCEPT
        {
            return __spirv::__make_OpIsValidReserveId_call<bool>(_reserve_id);
        }

        /// \brief Tests if reservation object is valid. This operator has the same behavior as is_valid.
        ///
        __ALWAYS_INLINE explicit operator bool() const __NOEXCEPT
        {
            return is_valid();
        }

        /// \brief Performs write packet specified by ref to the reserved area of the pipe referred to by index.
        ///
        __ALWAYS_INLINE bool write(uint index, const T& ref) __NOEXCEPT
        {
            return __spirv::__make_OpReservedWritePipe_call<int>(_pipe, _reserve_id, index, (void *)&ref, static_cast<unsigned int>(sizeof(T)), static_cast<unsigned int>(alignof(T)));
        }

        /// \brief Commits write associated with reservation object
        ///
        template<memory_scope K = S>
        __ALWAYS_INLINE enable_if_t<K == memory_scope::memory_scope_work_item> commit() __NOEXCEPT
        {
            __spirv::__make_OpCommitWritePipe_call<void>(_pipe, _reserve_id, static_cast<unsigned int>(sizeof(T)), static_cast<unsigned int>(alignof(T)));
        }

        /// \brief Commits write associated with reservation object returned by work_group_reserve and sub_group_reserve
        ///
        template<memory_scope K = S>
        __ALWAYS_INLINE enable_if_t<K != memory_scope::memory_scope_work_item> commit() __NOEXCEPT
        {
            __spirv::__make_OpGroupCommitWritePipe_call<void>(S, _pipe, _reserve_id, static_cast<unsigned int>(sizeof(T)), static_cast<unsigned int>(alignof(T)));
        }

    protected:
        friend reservation<memory_scope::memory_scope_work_item> pipe<T, access>::reserve(uint num_packets) __NOEXCEPT;
        friend reservation<memory_scope::memory_scope_work_group> pipe<T, access>::work_group_reserve(uint num_packets) __NOEXCEPT;
        friend reservation<memory_scope::memory_scope_sub_group> pipe<T, access>::sub_group_reserve(uint num_packets) __NOEXCEPT;

        reservation(__global __spirv::OpTypePipe<__spirv::AccessQualifier::Write>* p, __global __spirv::OpTypeReserveId* rid) : _pipe(p), _reserve_id(rid) {}

    private:
        __global __spirv::OpTypePipe<__spirv::AccessQualifier::Write>* _pipe;
        __global __spirv::OpTypeReserveId* _reserve_id;
    };

    /// \brief Default constructor of pipe class must be deleted per OpenCL C++ spec.
    ///
    pipe() = delete;

    /// \brief Copy constructor of pipe class must be defaulted per OpenCL C++ spec.
    ///
    pipe(const pipe&) = default;

    /// \brief Move constructor of pipe class must be defaulted per OpenCL C++ spec.
    ///
    pipe(pipe&&) = default;

    /// \brief Copy assignment operator of pipe class must be deleted per OpenCL C++ spec.
    ///
    pipe& operator=(const pipe&) = delete;

    /// \brief Move assignment operator of pipe class must be deleted per OpenCL C++ spec.
    ///
    pipe& operator=(pipe&&) = delete;

    /// \brief Address-of operator of pipe class must be deleted per OpenCL C++ spec.
    ///
    pipe* operator&() = delete;

    /// \brief Performs write on a pipe, returns true on success and false on failure
    ///
    __ALWAYS_INLINE bool write(const T & ret) const __NOEXCEPT
    {
        return __spirv::__make_OpWritePipe_call<int>(_handle, (void *)&ret, static_cast<unsigned int>(sizeof(T)), static_cast<unsigned int>(alignof(T)));
    }

    /// \brief Reserves write on a pipe, returns valid reservation object if operation succeeded
    ///
    __ALWAYS_INLINE reservation<memory_scope::memory_scope_work_item> reserve(uint num_packets) __NOEXCEPT
    {
        return{ _handle, __spirv::__make_OpReserveWritePipePackets_call<__global __spirv::OpTypeReserveId*>(_handle, num_packets, static_cast<unsigned int>(sizeof(T)), static_cast<unsigned int>(alignof(T))) };
    }

    /// \brief Reserves write on a pipe, returns valid reservation object if operation succeeded
    ///
    /// This operation has to be encountered by all items
    /// in a work-group with the same arguments otherwise the behavior is undefined
    __ALWAYS_INLINE reservation<memory_scope::memory_scope_work_group> work_group_reserve(uint num_packets) __NOEXCEPT
    {
        return{ _handle, __spirv::__make_OpGroupReserveWritePipePackets_call<__global __spirv::OpTypeReserveId*>(memory_scope::memory_scope_work_group, _handle, num_packets, static_cast<unsigned int>(sizeof(T)), static_cast<unsigned int>(alignof(T))) };
    }

    /// \brief Reserves write on a pipe, returns valid reservation object if operation succeeded
    ///
    /// This operation has to be encountered by all items
    /// in a subgroup with the same arguments otherwise the behavior is undefined
    __ALWAYS_INLINE reservation<memory_scope::memory_scope_sub_group> sub_group_reserve(uint num_packets) __NOEXCEPT
    {
        return{ _handle, __spirv::__make_OpGroupReserveWritePipePackets_call<__global __spirv::OpTypeReserveId*>(memory_scope::memory_scope_sub_group, _handle, num_packets, static_cast<unsigned int>(sizeof(T)), static_cast<unsigned int>(alignof(T))) };
    }

    /// \brief Returns number of packets that are currently stored in a pipe
    ///
    /// Please note that this value is already outdated at the point of return according to OCL C++ specification
    __ALWAYS_INLINE uint num_packets() const __NOEXCEPT
    {
        return __spirv::__make_OpGetNumPipePackets_call<unsigned int>(_handle, static_cast<unsigned int>(sizeof(T)), static_cast<unsigned int>(alignof(T)));
    }

    /// \brief Returns maximum number of packets that can be stored in a pipe
    ///
    __ALWAYS_INLINE uint max_packets() const __NOEXCEPT
    {
        return __spirv::__make_OpGetMaxPipePackets_call<unsigned int>(_handle, static_cast<unsigned int>(sizeof(T)), static_cast<unsigned int>(alignof(T)));
    }

protected:
    template<class P, size_t N>
    friend class pipe_storage;

    pipe(__global __spirv::OpTypePipe<__spirv::AccessQualifier::Write>* handle) : _handle(handle) { }

private:
    __global __spirv::OpTypePipe<__spirv::AccessQualifier::Write>* _handle;
};

/// \brief Constructs a read only or write only pipe from pipe_storage object.
///
template<pipe_access Access = pipe_access::read, class T, size_t N>
__ALWAYS_INLINE pipe<T, Access> make_pipe(pipe_storage<T, N>& ps) __NOEXCEPT
{
    return ps.template get<Access>();
}

}
