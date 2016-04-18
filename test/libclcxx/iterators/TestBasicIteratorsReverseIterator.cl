// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_memory>
#include <opencl_array>
using namespace cl;

kernel void worker()
{
    local<array<int, 10>> arr;
    reverse_iterator<decltype(arr)::iterator> iter_begin = arr.rbegin();
    reverse_iterator<decltype(arr)::iterator> iter_end = arr.rend();
    
    iter_begin = iter_end;
    auto iter_base = iter_begin.base();
    
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