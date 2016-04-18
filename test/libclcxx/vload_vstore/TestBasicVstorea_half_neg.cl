// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -nobuiltininc -O0 -o -

#include <opencl_vector_load_store>
using namespace cl;

kernel void worker()
{
    //expected-error@+2 {{no matching function for call to 'vstorea_half'}}
    //expected-note@__ocl_type_traits_type_generators.h:* {{disabled by 'enable_if'}}
    vstorea_half(int3{ 0, 0, 0 }, 0, (half*)nullptr);
}
