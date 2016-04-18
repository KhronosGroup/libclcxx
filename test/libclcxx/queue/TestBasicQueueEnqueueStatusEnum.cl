// RUN: %clang_cc1 %s -triple spir-unknown-unknown -emit-llvm -O0 -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_device_queue>

kernel void worker()
{
    cl::enqueue_status a;

    a = cl::enqueue_status::success;
    a = cl::enqueue_status::failure;
    a = cl::enqueue_status::invalid_queue;
    a = cl::enqueue_status::invalid_ndrange;
    a = cl::enqueue_status::invalid_event_wait_list;
    a = cl::enqueue_status::queue_full;
    a = cl::enqueue_status::invalid_arg_size;
    a = cl::enqueue_status::event_allocation_failure;
    a = cl::enqueue_status::out_of_resources;
}
