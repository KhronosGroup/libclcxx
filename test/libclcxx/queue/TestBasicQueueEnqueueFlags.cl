// RUN: %clang_cc1 %s -triple spir-unknown-unknown -emit-llvm -O0 -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_device_queue>

kernel void worker( cl::device_queue q )
{
    q.enqueue_kernel( cl::enqueue_policy::no_wait, cl::ndrange( 1 ), [](){} );
    q.enqueue_kernel( cl::enqueue_policy::wait_kernel, cl::ndrange( 1 ), [](){} );
    q.enqueue_kernel( cl::enqueue_policy::wait_work_group, cl::ndrange( 1 ), [](){} );
}
