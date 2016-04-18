// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_vector_utility>
#include <opencl_range>
#include <opencl_memory>
using namespace cl;

kernel void worker()
{
    int8 v_i8;
    auto iter_begin = begin(v_i8);
    auto iter_end = end(v_i8);
    
    iter_begin = iter_end;

    int a = 0;
    a = *iter_begin;
    a = iter_begin[0];
    
    iter_begin++;
    iter_begin+=1;
    iter_begin = iter_begin + 1;
    
    iter_begin--;
    iter_begin-=1;
    iter_begin = iter_begin - 1;
    
    bool compare = false;
    compare = iter_begin == iter_end ? true : false;
    compare = iter_begin != iter_end ? true : false;
    compare = iter_begin < iter_end ? true : false;
    compare = iter_begin <= iter_end ? true : false;
    compare = iter_begin > iter_end ? true : false;
    compare = iter_begin >= iter_end ? true : false;
}
