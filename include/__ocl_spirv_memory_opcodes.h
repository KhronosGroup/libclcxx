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

namespace cl
{

namespace __spirv
{
/// \brief Enumerable describing SPIR-V storage class
///
enum class StorageClass
{
    UniformConstant = 0,
    Input = 1,
    Uniform = 2,
    Output = 3,
    WorkgroupLocal = 4,
    WorkgroupGlobal = 5,
    PrivateGlobal = 6,
    Function = 7,
    Generic = 8,
    PushConstant = 9,
    AtomicCounter = 10,
    Image = 11,
};


/// \brief Forward declaration to OpGenericCastToPtrExplicit_ToGlobal SPIR-V function
///
template<class T>
__ALWAYS_INLINE static __global T* __make_OpGenericCastToPtrExplicit_ToGlobal_call(__generic T* ptr) __NOEXCEPT
{
    extern __global T*  OpGenericCastToPtrExplicit_ToGlobal(__generic T* ptr, StorageClass sc) __NOEXCEPT;
    return OpGenericCastToPtrExplicit_ToGlobal(ptr, StorageClass::WorkgroupGlobal);
}

/// \brief Forward declaration to OpGenericCastToPtrExplicit_ToLocal SPIR-V function
///
template<class T>
__ALWAYS_INLINE static __local T* __make_OpGenericCastToPtrExplicit_ToLocal_call(__generic T* ptr) __NOEXCEPT
{
    extern __local T*  OpGenericCastToPtrExplicit_ToLocal(__generic T* ptr, StorageClass sc) __NOEXCEPT;
    return OpGenericCastToPtrExplicit_ToLocal(ptr, StorageClass::WorkgroupLocal);
}

/// \brief Forward declaration to __make_GenericCastToPtrExplicit_ToPrivate_call SPIR-V function
///
template<class T>
__ALWAYS_INLINE static __private T* __make_GenericCastToPtrExplicit_ToPrivate_call(__generic T* ptr) __NOEXCEPT
{
    extern __private T*  OpGenericCastToPtrExplicit_ToPrivate(__generic T* ptr, StorageClass sc) __NOEXCEPT;
    return OpGenericCastToPtrExplicit_ToPrivate(ptr, StorageClass::Function);
}

} // namespace __spirv

} // namespace cl
