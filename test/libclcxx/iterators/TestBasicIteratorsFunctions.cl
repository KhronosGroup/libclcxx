// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -cl-fp64-enable -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_memory>
#include <opencl_array>
using namespace cl;

kernel void worker()
{
    array<int,3> arr {1,2,3};
    reverse_iterator<decltype(arr)::iterator> iter_begin = arr.rbegin();
    reverse_iterator<decltype(arr)::iterator> iter_end = arr.rend();
    advance(iter_begin, 1);
    distance(iter_begin, iter_end);
    next(iter_begin, 1);
    prev(iter_end, 1);
}