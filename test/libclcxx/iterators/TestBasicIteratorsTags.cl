// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -cl-fp64-enable -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_memory>
#include <opencl_array>
using namespace cl;

template<class T>
struct __test_vector : public array<T, 10> { };

kernel void worker()
{
    static_assert(is_same<back_insert_iterator<__test_vector<int>>::iterator_category, output_iterator_tag>::value, "back_insert_iterator should be OutputIterator");
    static_assert(is_same<front_insert_iterator<__test_vector<int>>::iterator_category, output_iterator_tag>::value, "front_insert_iterator should be OutputIterator");
    static_assert(is_same<insert_iterator<__test_vector<int>>::iterator_category, output_iterator_tag>::value, "insert_iterator should be OutputIterator");
    static_assert(is_same<move_iterator<__test_vector<int>::iterator>::iterator_category, bidirectional_iterator_tag>::value || is_same<move_iterator<__test_vector<int>::iterator>::iterator_category, random_access_iterator_tag>::value, "move_iterator should be BidirectionalIterator or RandomAccessIterator");
    static_assert(is_same<reverse_iterator<__test_vector<int>::iterator>::iterator_category, bidirectional_iterator_tag>::value || is_same<reverse_iterator<__test_vector<int>::iterator>::iterator_category, random_access_iterator_tag>::value, "reverse_iterator should be BidirectionalIterator or RandomAccessIterator");
}