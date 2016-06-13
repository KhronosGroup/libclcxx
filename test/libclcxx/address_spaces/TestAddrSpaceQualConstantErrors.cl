// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify

#include <opencl_memory>

cl::constant<int> globalVar; //expected-error{{default initialization of an object in constant address space}}*
//expected-note@TestAddrSpaceQualConstantErrors.cl:* {{add an explicit initializer to initialize 'globalVar'}}*

class ConstantClassMembers {
public:
  ConstantClassMembers() = default;
  ~ConstantClassMembers() = default;

  cl::constant<int> a; // expected-error{{field may not be qualified with an address space}}
};

int * func2(cl::constant<int> var) { // expected-error{{parameter may not be qualified with an address space}}
  return &var;
}

cl::constant<int> func3() { // expected-error{{return value cannot be qualified with address space}}*
  cl::constant<int> a = { 1 };
  return a; //expected-error{{no matching constructor for initialization of}}*
  //expected-note@__ocl_data.h:* 0+ {{candidate constructor not viable}}
  //expected-note@__ocl_data.h:* 0+ {{candidate constructor}}
}