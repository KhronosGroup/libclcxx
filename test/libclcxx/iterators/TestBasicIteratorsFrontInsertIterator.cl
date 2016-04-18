// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_memory>
#include <opencl_array>
using namespace cl;

template<class T>
struct test_vector : public local<array<T, 10>>
{
    void push_front(T t);
};

kernel void worker()
{
    test_vector<int> v;
    front_insert_iterator<decltype(v)> iter(v);
    for(int i = 0 ; i < 10 ; i++) {
        iter = i;
    }

    auto _front_inserter = front_inserter(v);
}