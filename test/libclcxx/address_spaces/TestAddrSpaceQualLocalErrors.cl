// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify

#include <opencl_memory>

class LocalClassMembers {
public:
  LocalClassMembers() = default;
  ~LocalClassMembers() = default;

  cl::local<int> a; // expected-error{{field may not be qualified with an address space}}
};

struct LocalStructMembers {
  cl::local<int> a; // expected-error{{field may not be qualified with an address space}}
};

int * func2(cl::local<int> var) { // expected-error{{parameter may not be qualified with an address space}}
  return &var;
}

cl::local<int> func3() { // expected-error{{return value cannot be qualified with address space}}*
  cl::local<int> a; // expected-error{{variable declaration with local storage (local address space) is only allowed at program scope, at kernel scope or as a static data member}}
  return a;
}
