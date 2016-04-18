// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -cl-fp64-enable -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_memory>
#include <opencl_array>
using namespace cl;

kernel void worker()
{
    static_assert(is_same<iterator_traits<local<array<int,10>>::iterator>::iterator_category, random_access_iterator_tag>::value, "array iterator should be RandomAccessIterator");
}