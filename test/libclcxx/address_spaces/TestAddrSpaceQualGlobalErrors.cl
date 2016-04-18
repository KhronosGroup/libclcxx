// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify

#include <opencl_memory>

class GlobalClassMembers {
public:
  GlobalClassMembers() = default;
  ~GlobalClassMembers() = default;

  cl::global<int> a; // expected-error{{field may not be qualified with an address space}}
};

struct GlobalStructMembers {
  cl::global<int> a; // expected-error{{field may not be qualified with an address space}}
};

int * func2(cl::global<int> var) { // expected-error{{parameter may not be qualified with an address space}}
  return &var;
}

cl::global<int> func3() { // expected-error{{return value cannot be qualified with address space}}*
  static cl::global<int> a = { 1 };
  return a;
}


template <typename _A, typename _B>
struct is_same { enum { value = false }; };

template <typename _A>
struct is_same<_A, _A> { enum { value = true }; };

cl::constant_ptr<int> constantPtr;
cl::global_ptr<int> globalPtr;
cl::local_ptr<int> localPtr;
static_assert(is_same<decltype(constantPtr), decltype(globalPtr)>::value, ""); // expected-error{{static_assert failed ""}}
static_assert(is_same<decltype(localPtr), decltype(globalPtr)>::value, ""); // expected-error{{static_assert failed ""}}

kernel void worker() {
  cl::global<int> globalVar0; // expected-error{{automatic variable qualified with an address space}}
}
