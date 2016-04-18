// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -cl-fp64-enable -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_memory>
#include <opencl_iterator>
using namespace cl;

template<typename T>
struct valid_iterator 
{
    using difference_type = ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = random_access_iterator_tag;
};

//it will catch this specialization : struct iterator_traits<Iterator, true>
template<typename T>
struct derived_iterator : iterator_traits<valid_iterator<T>> { };

//it will catch this specialization : struct iterator_traits<T*, false>
template<typename T>
struct empty_iterator : iterator_traits<T>
{
    using difference_type = typename iterator_traits<T>::difference_type;
    using value_type = typename iterator_traits<T>::value_type;
    using pointer = typename iterator_traits<T>::pointer;
    using reference = typename iterator_traits<T>::reference;
    using iterator_category = typename iterator_traits<T>::iterator_category;
};

kernel void worker()
{
    derived_iterator<int> d_it;

    static_assert(is_same<empty_iterator<int*>::difference_type, ptrdiff_t>::value, "iterator::difference_type is not matching ptrdiff_t");
    static_assert(is_same<empty_iterator<int*>::value_type, int>::value, "iterator::value_type should return pointer base type");
    static_assert(is_same<empty_iterator<int*>::pointer, int*>::value, "iterator::pointer type should be the same as template parameter");
    static_assert(is_same<empty_iterator<int*>::reference, int&>::value, "iterator::reference is not matching referenced type from template parameter");
    static_assert(is_same<empty_iterator<int*>::iterator_category, random_access_iterator_tag>::value, "iterator::iterator_category should be equal to random_access_iterator_tag");
}