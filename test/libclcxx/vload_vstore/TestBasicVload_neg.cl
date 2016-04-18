// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -nobuiltininc -O0 -o -

#include <opencl_vector_load_store>
using namespace cl;

kernel void worker()
{
    //expected-error@+3 {{no matching function for call to 'vload'}}
    //expected-note@__ocl_type_traits_type_generators.h:* {{disabled by 'enable_if'}}
    //expected-note@opencl_vector_load_store:* {{candidate template ignored}}
    vload<1>(0, (float*)nullptr);
    
    //expected-error@+3 {{no matching function for call to 'vload'}}
    //expected-note@__ocl_type_traits_type_generators.h:* {{disabled by 'enable_if'}}
    //expected-note@opencl_vector_load_store:* {{candidate template ignored}}
    vload<5>(0, (float*)nullptr);
}
