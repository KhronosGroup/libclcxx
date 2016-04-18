// RUN: %clang_cc1 %s -triple spir-unknown-unknown -emit-llvm -O0 -cl-std=c++ -fsyntax-only -pedantic -verify

#include <opencl_device_queue>

kernel void worker( cl::device_queue q )
{
    struct X {};
    // expected-note@__ocl_device_queue.h:* {{in instantiation}}
    // expected-note@+2 {{in instantiation}}
    // expected-error@__ocl_device_queue.h:* {{Function passed to enqueue_kernel could not be called with deduced arguments. Type mismatch, ambiguity overloads or invalid parameters count.}}
    q.enqueue_kernel( cl::enqueue_policy::no_wait, cl::ndrange( 1 ), [](int a){}, 1, 2 );

    // expected-note@__ocl_device_queue.h:* {{in instantiation}}
    // expected-note@+2 {{in instantiation}}
    // expected-error@__ocl_device_queue.h:* {{local_ptr<T> cannot be passed directly to enqueue_kernel, use local_ptr<T>::size_type instead.}}
    q.enqueue_kernel( cl::enqueue_policy::no_wait, cl::ndrange( 1 ), [](cl::local_ptr<int> a){}, cl::local_ptr<int>{ } );

    // expected-note@__ocl_device_queue.h:* {{in instantiation}}
    // expected-note@+2 {{in instantiation}}
    // expected-error@__ocl_device_queue.h:* {{Function passed to enqueue_kernel could not be called with deduced arguments. Type mismatch, ambiguity overloads or invalid parameters count.}}
    q.enqueue_kernel( cl::enqueue_policy::no_wait, cl::ndrange( 1 ), [](char* a){}, 'a' );
}