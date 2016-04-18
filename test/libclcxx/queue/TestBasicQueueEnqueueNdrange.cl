// RUN: %clang_cc1 %s -triple spir-unknown-unknown -emit-llvm -O0 -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_device_queue>

size_t n1 = 1;
size_t n2[2] = {1, 1};
size_t n3[3] = {1, 1, 1};

kernel void worker( cl::device_queue q )
{
    q.enqueue_kernel( cl::enqueue_policy::no_wait, cl::ndrange( n1 ), [](){} ); 
    q.enqueue_kernel( cl::enqueue_policy::no_wait, cl::ndrange( n1, n1 ), [](){} ); 
    q.enqueue_kernel( cl::enqueue_policy::no_wait, cl::ndrange( n1, n1, n1 ), [](){} ); 
    
    q.enqueue_kernel( cl::enqueue_policy::no_wait, cl::ndrange( n2 ), [](){} ); 
    q.enqueue_kernel( cl::enqueue_policy::no_wait, cl::ndrange( n2, n2 ), [](){} ); 
    q.enqueue_kernel( cl::enqueue_policy::no_wait, cl::ndrange( n2, n2, n2 ), [](){} ); 
    
    q.enqueue_kernel( cl::enqueue_policy::no_wait, cl::ndrange( n3 ), [](){} ); 
    q.enqueue_kernel( cl::enqueue_policy::no_wait, cl::ndrange( n3, n3 ), [](){} ); 
    q.enqueue_kernel( cl::enqueue_policy::no_wait, cl::ndrange( n3, n3, n3 ), [](){} ); 
}