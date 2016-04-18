// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -O0 -o /dev/null
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -O3 -o /dev/null
// expected-no-diagnostics

#include <opencl_memory>

cl::global<int> gvar;

kernel void test0(cl::global_ptr<int> arg) {
  static cl::global<int> var1 = { 1 };
  int &ref1 = var1;
  
  static const cl::global<int> var2 = { 5 };
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
  
  cl::global_ptr<int> ptr2 = var1.ptr();
  *ptr2 = 4;
  
  cl::global_ptr<const int> ptr8 = var2.ptr();
}

//////////////////////////////////////////////
struct TestClass10 {
  TestClass10(cl::global_ptr<int> &arg): _m(arg) { }
  cl::global_ptr<int> &get() { return _m; }
  
  cl::global_ptr<int> _m;
};

kernel void test1(cl::global_ptr<int> arg) {
  static cl::global<int> var0 = { 1 };
  int* ptr0 = &var0;
  int& ref0 = var0;
  
  static cl::global<int> var1 = { 1 };
  const int* ptr1 = &var1;
  const int& ref1 = var1;

  static cl::global<TestClass10> obj0(arg);
  TestClass10* ptr2 = &obj0;
  TestClass10& ref2 = obj0;
  cl::global_ptr<TestClass10> gptr2 = obj0.ptr();
  cl::global_ptr<int> gcptr20 = obj0.get();
  cl::global_ptr<int> gcptr21 = gptr2->get();
  
  TestClass10 val = obj0;
  
  static const cl::global<TestClass10> var2 = { obj0 };
  const TestClass10* ptr3 = &var2;
  const TestClass10& ref3 = var2;
  cl::global_ptr<const TestClass10> gptr3 = var2.ptr();
}

//////////////////////////////////////////////
kernel void test2(cl::global<int> &arg0, cl::global<int> *arg1) {
  arg0 = 2;
  arg0 += 3;
  arg0 -= 3;
  arg0 /= 1;
  arg0 *= 5;
  arg0 = arg0 + 1;
  arg0 = arg0 - 1;
  arg0 = arg0 / 2;
  arg0 = arg0 * 2;
  
  *arg1 = 2;
  *arg1 += 3;
  *arg1 -= 3;
  *arg1 /= 1;
  *arg1 *= 5;
  *arg1 = *arg1 + 1;
  *arg1 = *arg1 - 1;
  *arg1 = *arg1 / 2;
  *arg1 = *arg1 * 2;
}

//////////////////////////////////////////////
kernel void test3() {
    static_assert(cl::is_global<cl::remove_reference_t<cl::global_ptr<int>::reference>>::value, "value pointed by global_ptr should be in global address space");
}

//////////////////////////////////////////////
struct TestClass11
{
    static cl::global<int> _m;
	int get() { return _m; };
};

kernel void test4() {
	TestClass11 obj;
	int val1 = obj.get();
}
