// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -nobuiltininc -O0 -o -

#include <opencl_vector_load_store>
using namespace cl;

kernel void worker()
{    
    //expected-error@+2 {{no matching function for call to 'vload_half'}}
    //expected-note@__ocl_type_traits_type_generators.h:* 2 {{disabled by 'enable_if'}}
    vload_half<5>(0, (const half*)nullptr);
}
