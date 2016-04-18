// RUN: %clang_cc1 %s -triple spir-unknown-unknown -emit-llvm -O0 -cl-std=c++ -fsyntax-only -pedantic -verify

#include <opencl_device_queue>

kernel void worker( cl::device_queue q )
{
    size_t n1 = 1;
    size_t n2[] = {1, 1};
    size_t n3[] = {1, 1, 1, 1};
    
    // expected-note@__ocl_device_queue.h:* 1+ {{candidate}}
    // expected-note@+2 {{in instantiation}}
    // expected-error@__ocl_device_queue.h:* {{static_assert failed "Invalid dimension"}}
    q.enqueue_kernel( cl::enqueue_policy::no_wait, cl::ndrange( n3 ), [](){} );
    
    // expected-error@+1 {{no matching constructor for initialization of 'cl::ndrange'}}
    q.enqueue_kernel( cl::enqueue_policy::no_wait, cl::ndrange( n1, n2 ), [](){} );
    
    // expected-error@+1 {{no matching constructor for initialization of 'cl::ndrange'}}
    q.enqueue_kernel( cl::enqueue_policy::no_wait, cl::ndrange( n1, n1, n2 ), [](){} );
    
    // expected-error@+1 {{no matching constructor for initialization of 'cl::ndrange'}}
    q.enqueue_kernel( cl::enqueue_policy::no_wait, cl::ndrange( n2, n3 ), [](){} );
    
    // expected-error@+1 {{no matching constructor for initialization of 'cl::ndrange'}}
    q.enqueue_kernel( cl::enqueue_policy::no_wait, cl::ndrange( n2, n2, n1 ), [](){} );
}