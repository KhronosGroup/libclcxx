// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify

#include <opencl_memory>

cl::priv<int> g; // expected-error{{program scope variables must reside global, local or constant address space}}

class PrivateClassMembers {
public:
  PrivateClassMembers() = default;
  ~PrivateClassMembers() = default;

  cl::priv<int> a; // expected-error{{field may not be qualified with an address space}}
};

int * func2(cl::priv<int> var) { // expected-error{{parameter may not be qualified with an address space}}
  return &var;
}

template <typename _A, typename _B>
struct is_same { enum { value = false }; };

template <typename _A>
struct is_same<_A, _A> { enum { value = true }; };
