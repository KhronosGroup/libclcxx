// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_memory>
#include <opencl_array>
using namespace cl;

template<class T>
struct __test_vector : public array<T, 10>
{
    void push_back(T t);
};

kernel void worker()
{
    __test_vector<int> v;

    back_insert_iterator<decltype(v)> iter(v);
    for(int i = 0 ; i < 10 ; i++) {
        iter = i;
    }

    auto _back_inserter = back_inserter(v);
}