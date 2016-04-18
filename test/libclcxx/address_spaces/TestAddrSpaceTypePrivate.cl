// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -O0 -o /dev/null
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -O3 -o /dev/null
// expected-no-diagnostics

#include <opencl_memory>

void test0(cl::private_ptr<int> arg) {
  cl::priv<int> var1 = { 1 };
  int &ref1 = var1;
  
  const cl::priv<int> var2 = { 5 };
  const int *ptrvar2 = &var2;
  const int &ref2 = var2;

  int val = var2;
  var1 = 2;
  var1 += 3;
  var1 -= 3;
  var1 /= 1;
  var1 *= 5;
  var1 = var2 + 1;
  var1 = var2 - 1;
  var1 = var2 / 2;
  var1 = var2 * 2;
  
  int* ptr1 = &var1;
  *ptr1 = 3;
  
  cl::private_ptr<int> ptr2 = var1.ptr();
  *ptr2 = 4;
  
  cl::private_ptr<const int> ptr8 = var2.ptr();
}

//////////////////////////////////////////////
struct TestClass10 {
  TestClass10(cl::private_ptr<int> &arg): _m(arg) { }
  cl::private_ptr<int> &get() { return _m; }
  
  cl::private_ptr<int> _m;
};

void test1(cl::private_ptr<int> arg) {
  cl::priv<int> var0 = { 1 };
  int* ptr0 = &var0;
  int& ref0 = var0;
  
  cl::priv<int> var1 = { 1 };
  const int* ptr1 = &var1;
  const int& ref1 = var1;

  cl::priv<TestClass10> obj0(arg);
  TestClass10* ptr2 = &obj0;
  TestClass10& ref2 = obj0;
  cl::private_ptr<TestClass10> gptr2 = obj0.ptr();
  cl::private_ptr<int> gcptr20 = obj0.get();
  cl::private_ptr<int> gcptr21 = gptr2->get();
  
  const cl::priv<TestClass10> var2 = { obj0 };
  const TestClass10* ptr3 = &var2;
  const TestClass10& ref3 = var2;
  cl::private_ptr<const TestClass10> gptr3 = var2.ptr();
}

//////////////////////////////////////////////
kernel void test2() {
    static_assert(cl::is_private<cl::remove_reference_t<cl::private_ptr<int>::reference>>::value, "value pointed by private_ptr should be in private address space");
}
