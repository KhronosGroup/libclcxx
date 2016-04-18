// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -nobuiltininc -O0 -o -

#include <opencl_vector_load_store>
using namespace cl;

kernel void worker()
{
    //expected-error@+2 {{no matching function for call to 'vstore'}}
    //expected-note@__ocl_type_traits_type_generators.h:* {{disabled by 'enable_if'}}
    vstore(12, 0, (int*)nullptr);
    
    //expected-error@+3 {{no matching function for call to 'vstore'}}
    //expected-note@__ocl_type_traits_type_generators.h:* {{disabled by 'enable_if'}}
    struct Test { int a; };
    vstore(Test{ 1 }, 0, (Test*)nullptr);
}
