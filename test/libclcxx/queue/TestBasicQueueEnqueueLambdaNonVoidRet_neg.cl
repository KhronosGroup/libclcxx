// RUN: %clang_cc1 %s -triple spir-unknown-unknown -emit-llvm -O0 -cl-std=c++ -fsyntax-only -pedantic -verify

#include <opencl_device_queue>

using namespace cl;

kernel void worker(device_queue q, const ndrange range) {
    auto lambda_int = [](int x)->int { return 1;};

    cl::event waitlist[2];
    cl::event *event_ret;

    int x;

    // expected-note@+2 {{in instantiation}}
    // expected-error@__ocl_device_queue.h:* {{Invocation of enqueued function with deduced arguments does not return void!}}
    q.enqueue_kernel(cl::enqueue_policy::no_wait, 2, waitlist, event_ret, range, lambda_int, x);
}
