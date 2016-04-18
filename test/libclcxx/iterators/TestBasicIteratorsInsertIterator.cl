// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -cl-fp64-enable -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_memory>
#include <opencl_array>
using namespace cl;

template<class T>
struct test_vector : public local<array<T, 10>>
{
    using iterator = typename array<T, 10>::iterator;
    using value_type = typename array<T, 10>::value_type;
    using const_iterator = typename array<T, 10>::const_iterator;
    iterator insert(const_iterator it, value_type t);
    //iterator begin();
};

kernel void worker(test_vector<int> c)
{
    // TODO : some address space problems with begin() - in local_array there are multiple overloads for address spaces, which are no longer needed 
    // TODO : rewrite this test/__ocl_array.h after merging iterators
    // insert_iterator<decltype(c)> insert_it (c, c.begin());
    // for(int i = 0 ; i < 10 ; i++) {
        // insert_it = i;
    // }

    // auto _inserter = inserter(c, c.begin());
}
