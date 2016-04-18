// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -O0 -o /dev/null
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -O3 -o /dev/null
// expected-no-diagnostics

#include <opencl_memory>

cl::constant<int> gvar = { 1 };

kernel void test0(cl::constant_ptr<int> arg) {
  static cl::constant<int> var1 = { 1 };
  
  static const cl::constant<int> var2 = { 5 };
  cl::constant_ptr<const int> ptrvar2 = &var2;
  
  int val = var2;
  
  cl::constant_ptr<int> ptr1 = &var1;
  cl::constant_ptr<int> ptr2 = var1.ptr();
  cl::constant_ptr<const int> ptr8 = var2.ptr();
}

//////////////////////////////////////////////
kernel void test1(cl::constant<int> &arg0, cl::constant<int> *arg1) {
  int val0 = arg0;
  int val1 = *arg1;
}

//////////////////////////////////////////////
kernel void test2() {
    static_assert(cl::is_constant<cl::remove_reference_t<cl::constant_ptr<int>::reference>>::value, "value pointed by constant_ptr should be in constant address space");
}

//////////////////////////////////////////////
struct TestClass11
{
    static cl::constant<int> _m;
	int get() { return _m; };
};

kernel void test3() {
	TestClass11 obj;
	int val1 = obj.get();
}

/////////////////////////////////////////////
struct S
{
  int a;
  int b;
};

cl::constant<S> gvar2 { 1, 1 };
cl::constant<int[2]> gvar3 { 1, 1 };

kernel void test4() {
  int val0 = gvar2.ptr()->a;
  int val1 = gvar2.ptr()->b;
  int val2 = gvar3[0];
}