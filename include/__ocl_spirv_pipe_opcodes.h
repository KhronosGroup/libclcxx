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
#include <__ocl_pipes_enums.h>
#include <__ocl_atomic_enum.h>
#include <__ocl_spirv_access_opcodes.h>
#include <__ocl_functions_macros.h>

namespace cl
{
namespace __spirv
{
/// \brief Opaque type representing reservations of operations in queues
///
class OpTypeReserveId;

/// \brief Opaque type representing read or write only pipes
///
template <AccessQualifier Access>
class OpTypePipe;

/// \brief Opaque type representing pipe storages
///
struct OpTypePipeStorage;

/// \brief Opaque type representing pipe storages
///
struct OpConstantPipeStorage
{
    constexpr OpConstantPipeStorage(int PacketSize, int PacketAlignment, int Capacity): _PacketSize(PacketSize), _PacketAlignment(PacketAlignment), _Capacity(Capacity) { }

    int _PacketSize;
    int _PacketAlignment;
    int _Capacity;
};

MAKE_SPIRV_CALLABLE(OpGroupCommitReadPipe)
MAKE_SPIRV_CALLABLE(OpGroupCommitWritePipe)
MAKE_SPIRV_CALLABLE(OpCommitReadPipe)
MAKE_SPIRV_CALLABLE(OpCommitWritePipe)
MAKE_SPIRV_CALLABLE(OpReserveReadPipePackets)
MAKE_SPIRV_CALLABLE(OpReserveWritePipePackets)
MAKE_SPIRV_CALLABLE(OpGroupReserveReadPipePackets)
MAKE_SPIRV_CALLABLE(OpGroupReserveWritePipePackets)
MAKE_SPIRV_CALLABLE(OpReadPipe)
MAKE_SPIRV_CALLABLE(OpWritePipe)
MAKE_SPIRV_CALLABLE(OpReservedReadPipe)
MAKE_SPIRV_CALLABLE(OpReservedWritePipe)
MAKE_SPIRV_CALLABLE(OpGetNumPipePackets)
MAKE_SPIRV_CALLABLE(OpGetMaxPipePackets)
MAKE_SPIRV_CALLABLE(OpIsValidReserveId)

extern __global OpTypePipe<AccessQualifier::Read>* OpCreatePipeFromPipeStorage_read(__global const OpTypePipeStorage* pipe_storage) __NOEXCEPT;
extern __global OpTypePipe<AccessQualifier::Write>* OpCreatePipeFromPipeStorage_write(__global const OpTypePipeStorage* pipe_storage) __NOEXCEPT;

}

}