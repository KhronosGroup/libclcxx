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
#include <opencl_type_traits>

namespace cl
{

namespace __spirv
{

enum MemorySemantics
{
    None                   = 0x0,
    Acquire                = 0x2,
    Release                = 0x4,
    AcquireRelease         = 0x8,
    SequentiallyConsistent = 0x10,
    UniformMemory          = 0x40,
    SubgroupMemory         = 0x80,
    WorkgroupMemory        = 0x100,
    CrossWorkgroupMemory   = 0x200,
    AtomicCounterMemory    = 0x400,
    ImageMemory            = 0x800,
};

enum MemoryScope
{
    CrossDevice = 0,
    Device      = 1,
    Workgroup   = 2,
    Subgroup    = 3,
    Invocation  = 4,
};

/// \brief Forward declaration to OpGenericPtrMemSemantics SPIR-V function
extern int OpGenericPtrMemSemantics(const volatile __generic void *ptr) __NOEXCEPT;

}

/// \brief Enumerable describing memory order of the atomic operations
///
enum memory_order
{
    memory_order_relaxed = __spirv::MemorySemantics::None,
    memory_order_seq_cst = __spirv::MemorySemantics::SequentiallyConsistent,
    memory_order_acquire = __spirv::MemorySemantics::Acquire,
    memory_order_release = __spirv::MemorySemantics::Release,
    memory_order_acq_rel = __spirv::MemorySemantics::AcquireRelease
};

/// \brief Enumerable describing memory scope of the atomic operations
///
enum memory_scope
{
    memory_scope_all_svm_devices = __spirv::MemoryScope::CrossDevice,
    memory_scope_device          = __spirv::MemoryScope::Device,
    memory_scope_work_group      = __spirv::MemoryScope::Workgroup,
    memory_scope_sub_group       = __spirv::MemoryScope::Subgroup,
    memory_scope_work_item       = __spirv::MemoryScope::Invocation
};

/// \brief enumberable decribing type of memory that memory fence is used on
///
enum class mem_fence
{
    global = __spirv::MemorySemantics::CrossWorkgroupMemory,
    local  = __spirv::MemorySemantics::WorkgroupMemory,
    image  = __spirv::MemorySemantics::ImageMemory
};

/// \brief Bitwise NOT operator for mem_fence enum
///
__ALWAYS_INLINE mem_fence operator~(mem_fence flags)
{
    return static_cast<mem_fence>(~static_cast<underlying_type_t<mem_fence>>(flags));
}

/// \brief Bitwise AND operator for mem_fence enum
///
__ALWAYS_INLINE mem_fence operator&(mem_fence lhs, mem_fence rhs)
{
    return static_cast<mem_fence>(static_cast<underlying_type_t<mem_fence>>(lhs) & static_cast<underlying_type_t<mem_fence>>(rhs));
}

/// \brief Bitwise OR operator for mem_fence enum
///
__ALWAYS_INLINE mem_fence operator|(mem_fence lhs, mem_fence rhs)
{
    return static_cast<mem_fence>(static_cast<underlying_type_t<mem_fence>>(lhs) | static_cast<underlying_type_t<mem_fence>>(rhs));
}

/// \brief Bitwise XOR operator for mem_fence enum
///
__ALWAYS_INLINE mem_fence operator^(mem_fence lhs, mem_fence rhs)
{
    return static_cast<mem_fence>(static_cast<underlying_type_t<mem_fence>>(lhs) ^ static_cast<underlying_type_t<mem_fence>>(rhs));
}

/// \brief Returns the mem_fence value for a given const generic ptr.
///
template<class T>
__ALWAYS_INLINE mem_fence get_mem_fence(const volatile T *ptr)
{
    return static_cast<mem_fence>(__spirv::OpGenericPtrMemSemantics(ptr));
}

}
