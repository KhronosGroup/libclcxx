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

/// \brief Enum containing possible return values from enqueue function
///
enum class enqueue_status : int
{
    success = 0,
    failure = -101,
    invalid_queue = -102,
    invalid_ndrange = -160,
    invalid_event_wait_list = -57,
    queue_full = -161,
    invalid_arg_size = -51,
    event_allocation_failure = -100,
    out_of_resources = -5
};

/// \brief Enum representing flags used to specify start time of enqueue kernels
///
enum class enqueue_policy : int
{
    no_wait = 0,
    wait_kernel = 1,
    wait_work_group = 2
};

enum class event_status : int
{
    submitted,
    complete,
    error
};

enum class event_profiling_info : int
{
    exec_time
};

class ndrange;

namespace __spirv
{
/// \brief Forward declaration of SPIRV Queue type
///
class OpTypeQueue;

/// \brief Forward declaration of SPIRV DeviceEvent type
///
class OpTypeDeviceEvent;

/// \brief SPIRV opcode used for enqueueing markers
///
extern enqueue_status OpEnqueueMarker( __global OpTypeQueue * queue,
                                       uint num_events,
                                       __global const OpTypeDeviceEvent * const * wait_events,
                                       __global OpTypeDeviceEvent ** ret_event );

/// \brief SPIRV opcode used for enqueueing kernels
///
template <typename... LocalPtrs, typename... LocalPtrsSizes>
extern enqueue_status OpEnqueueKernel( __global OpTypeQueue * queue,
                                       int flags,
                                       const ndrange& nd,
                                       uint num_events,
                                       const OpTypeDeviceEvent * const * wait_events,
                                       __global OpTypeDeviceEvent ** ret_event,
                                       void (&invoke)(__private void*, LocalPtrs...),
                                       __private void* data,
                                       uint data_size,
                                       uint data_align,
                                       LocalPtrsSizes... );


template <typename... LocalPtrs>
extern int OpGetKernelNDrangeSubGroupCount( const ndrange &nd,
                                            void (&invoke)(__private void*, LocalPtrs...),
                                            __private void* data,
                                            uint data_size,
                                            uint data_align );

template <typename... LocalPtrs>
extern int OpGetKernelNDrangeMaxSubGroupSize( const ndrange &nd,
                                              void (&invoke)(__private void*, LocalPtrs...),
                                              __private void* data,
                                              uint data_size,
                                              uint data_align );

template <typename... LocalPtrs>
extern int OpGetKernelWorkGroupSize( void (&invoke)(__private void*, LocalPtrs...),
                                     __private void* data,
                                     uint data_size,
                                     uint data_align );

template <typename... LocalPtrs>
extern int OpGetKernelPreferredWorkGroupSizeMultiple( void (&invoke)(__private void*, LocalPtrs...),
                                                      __private void* data,
                                                      uint data_size,
                                                      uint data_align );

template <typename... LocalPtrs>
extern int OpGetKernelLocalSizeForSubgroupCount( int subgroup_count,
                                                 void (&invoke)(__private void*, LocalPtrs...),
                                                 __private void* data,
                                                 uint data_size,
                                                 uint data_align );

template <typename... LocalPtrs>
extern int OpGetKernelMaxNumSubgroups( void (&invoke)(__private void*, LocalPtrs...),
                                       __private void* data,
                                       uint data_size,
                                       uint data_align );


extern void OpRetainEvent( __global OpTypeDeviceEvent * event );
extern void OpReleaseEvent( __global OpTypeDeviceEvent * event );
extern __global OpTypeDeviceEvent* OpCreateUserEvent();
extern bool OpIsValidEvent( __global const OpTypeDeviceEvent * event );
extern void OpSetUserEventStatus( __global OpTypeDeviceEvent * event, int status );
extern void OpCaptureEventProfilingInfo( __global OpTypeDeviceEvent * event, int profiling_info, __global int8* value );

extern __global OpTypeQueue* OpGetDefaultQueue();

#undef _VALIDATE_INVOKE
#undef _VALIDATE_ENQUEUE

} //end namespace spirv
} //end namespace cl
