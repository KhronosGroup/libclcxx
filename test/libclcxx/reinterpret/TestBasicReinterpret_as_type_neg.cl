// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -emit-llvm -O0 -o -

#include <opencl_reinterpret>
using namespace cl;

struct Test
{
    float8 data;
};

kernel void worker()
{
    int8 tmp;
    
    as_type<void>(tmp); 
    //expected-error@__ocl_reinterpret.h:* {{static_assert failed "void type is not valid destination/source type for reinterpreting data with as_type operator."}}
    //expected-error@__ocl_reinterpret.h:* {{invalid application of 'sizeof' to an incomplete type 'void'}}
    //expected-note@15 {{in instantiation of function template specialization 'cl::as_type}}
    
    auto r2 = as_type<bool8>(tmp);
    //expected-error@__ocl_reinterpret.h:* {{static_assert failed "bool type is not valid destination/source type for reinterpreting data with as_type operator."}}
    //expected-error@__ocl_reinterpret.h:* {{static_assert failed "It is an error to use the as_type<T> operator to reinterpret data to a type of a different number of bytes."}}
    //expected-note@20 {{in instantiation of function template specialization 'cl::as_type}}

    auto r3 = as_type<short4>(tmp);
    //expected-error@__ocl_reinterpret.h:* {{static_assert failed "It is an error to use the as_type<T> operator to reinterpret data to a type of a different number of bytes."}}
    //expected-note@25 {{in instantiation of function template specialization 'cl::as_type}}

    tmp = as_type<int8>(void); 
    //expected-error@29{{expected '(' for function-style cast or type construction}}
    
    tmp = as_type<int8>(bool8{ false });
    //expected-error@__ocl_reinterpret.h:* {{static_assert failed "bool type is not valid destination/source type for reinterpreting data with as_type operator."}}
    //expected-error@__ocl_reinterpret.h:* {{static_assert failed "It is an error to use the as_type<T> operator to reinterpret data to a type of a different number of bytes."}}
    //expected-note@32 {{in instantiation of function template specialization 'cl::as_type}}

    tmp = as_type<int8>(short4{ 0 });
    //expected-error@__ocl_reinterpret.h:* {{static_assert failed "It is an error to use the as_type<T> operator to reinterpret data to a type of a different number of bytes."}}
    //expected-note@37 {{in instantiation of function template specialization 'cl::as_type}}
    
    auto r4 = as_type<Test>(tmp);
    //expected-error@__ocl_reinterpret.h:* {{static_assert failed "as_type operator may be used only for reinterpreting data from/to builtin scalar or vector types (except void and bool)."}}
    //expected-note@41 {{in instantiation of function template specialization 'cl::as_type}}
   
    tmp = as_type<int8>(Test{ 0 });
    //expected-error@__ocl_reinterpret.h:* {{static_assert failed "as_type operator may be used only for reinterpreting data from/to builtin scalar or vector types (except void and bool)."}}
    //expected-note@45 {{in instantiation of function template specialization 'cl::as_type}}

    //expected-note@__ocl_reinterpret.h:* 0+ {{in instantiation}}
}
