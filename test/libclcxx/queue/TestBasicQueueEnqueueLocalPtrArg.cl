// RUN: %clang_cc1 %s -triple spir-unknown-unknown -emit-llvm -O0 -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_device_queue>
#include <opencl_memory>

using namespace cl;

kernel void worker(device_queue q, const ndrange range) {
    auto lambda = [](local_ptr<int> a) { *a = 10; };

    cl::event waitlist[2];
    cl::event *event_ret;

    q.enqueue_kernel(cl::enqueue_policy::no_wait, 2, waitlist, event_ret, range, lambda, local_ptr<int>::size_type{1});
    q.enqueue_kernel(cl::enqueue_policy::no_wait, range, lambda, local_ptr<int>::size_type{1});

    q.enqueue_kernel(cl::enqueue_policy::no_wait, range, [](local_ptr<int>, local_ptr<float4>){}, local_ptr<int>::size_type{1}, local_ptr<float4>::size_type{1});
    q.enqueue_kernel(cl::enqueue_policy::no_wait, 2, waitlist, event_ret, range, [](local_ptr<int>, local_ptr<float4>){}, local_ptr<int>::size_type{1}, local_ptr<float4>::size_type{1});
}