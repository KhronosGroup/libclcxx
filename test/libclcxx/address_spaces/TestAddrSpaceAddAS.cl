// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_type_traits>
#include <__ocl_type_traits_address_spaces.h>
#include <__ocl_memory.h>
using namespace cl;

__global int var_global;

kernel void worker() 
{
    add_local_t<remove_as_t<int>> var_local;
    static_assert(is_local<decltype(var_local)>::value, "Adding local space address to variable failed");
    
    add_private_t<remove_as_t<int>> var_priv;
    static_assert(is_private<decltype(var_priv)>::value, "Adding private space address to variable failed");
    
    add_constant_t<remove_as_t<int>> var_const = 10;
    static_assert(is_constant<decltype(var_const)>::value, "Adding constant space address to variable failed");
}