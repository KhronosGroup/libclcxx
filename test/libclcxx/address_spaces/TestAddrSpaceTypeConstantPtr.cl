// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -O0 -o /dev/null
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -O3 -o /dev/null
// expected-no-diagnostics

#include <opencl_memory>

namespace test1
{
cl::constant_ptr<int> testFunc0(cl::constant_ptr<int> *arg) { return *arg; }
cl::constant_ptr<int> testFunc1(cl::constant_ptr<int> &arg) { return arg; }
cl::constant_ptr<int> testFunc2(cl::constant_ptr<int> arg) { return arg; }
cl::constant_ptr<int>* testFunc3(cl::constant_ptr<int> &arg) { return &arg; }
cl::constant_ptr<int>& testFunc4(cl::constant_ptr<int> &arg) { return arg; }
cl::constant_ptr<int> testFunc5(cl::constant_ptr<int> &arg) { return {}; }
cl::constant_ptr<int> testFunc6(cl::constant_ptr<int> &arg) { return cl::constant_ptr<int>(arg.get()); }
cl::constant_ptr<int> testFunc7(cl::constant_ptr<int> &arg) { return { arg }; }
cl::constant_ptr<int> testFunc8(cl::constant_ptr<int> &arg) { return { nullptr }; }

kernel void test1(cl::constant_ptr<int> arg0) {
  cl::constant_ptr<int> ptr0 = testFunc0(&arg0);
  cl::constant_ptr<int> ptr1 = testFunc1(arg0);
  cl::constant_ptr<int> ptr2 = testFunc2(arg0);
  cl::constant_ptr<int> *ptr3 = testFunc3(arg0);
  cl::constant_ptr<int> &ptr4 = testFunc4(arg0);
  cl::constant_ptr<int> ptr5 = testFunc5(arg0);
  cl::constant_ptr<int> ptr6 = testFunc6(arg0);
  cl::constant_ptr<int> ptr7 = testFunc7(arg0);
  cl::constant_ptr<int> ptr8 = testFunc8(arg0);
  
  cl::constant_ptr<int>::pointer p0 = arg0.get();
  __constant int* p1 = arg0.get();
  
  ptr0 = arg0;
  ptr0 = cl::constant_ptr<int>();
  ptr0 = arg0.get();
  ptr0 = nullptr;
  ptr0.swap(ptr1);
  
  __constant int& val = *ptr1;
  if(arg0) { }
  
  ptr0.release();
  ptr0.reset();
  ptr0.reset(arg0.get());
  ptr0++;
  ++ptr0;
  ptr0--;
  --ptr0;
  ptr0 += 10;
  ptr0 -= 20;
  
  if(arg0 == ptr0) { }
  if(arg0 != ptr0) { }
  if(arg0 < ptr0) { }
  if(arg0 > ptr0) { }
  if(arg0 <= ptr0) { }
  if(arg0 >= ptr0) { }
  
  if(arg0 == nullptr) { }
  if(arg0 != nullptr) { }
  if(arg0 < nullptr) { }
  if(arg0 > nullptr) { }
  if(arg0 <= nullptr) { }
  if(arg0 >= nullptr) { }
  
  if(nullptr == ptr0) { }
  if(nullptr != ptr0) { }
  if(nullptr < ptr0) { }
  if(nullptr > ptr0) { }
  if(nullptr <= ptr0) { }
  if(nullptr >= ptr0) { }
  
  cl::swap(ptr0, ptr1);
}

}

namespace test2
{
cl::constant_ptr<int[]> testFunc0(cl::constant_ptr<int[]> *arg) { return *arg; }
cl::constant_ptr<int[]> testFunc1(cl::constant_ptr<int[]> &arg) { return arg; }
cl::constant_ptr<int[]> testFunc2(cl::constant_ptr<int[]> arg) { return arg; }
cl::constant_ptr<int[]>* testFunc3(cl::constant_ptr<int[]> &arg) { return &arg; }
cl::constant_ptr<int[]>& testFunc4(cl::constant_ptr<int[]> &arg) { return arg; }
cl::constant_ptr<int[]> testFunc5(cl::constant_ptr<int[]> &arg) { return {}; }
cl::constant_ptr<int[]> testFunc6(cl::constant_ptr<int[]> &arg) { return cl::constant_ptr<int[]>(arg.get()); }
cl::constant_ptr<int[]> testFunc7(cl::constant_ptr<int[]> &arg) { return { arg }; }
cl::constant_ptr<int[]> testFunc8(cl::constant_ptr<int[]> &arg) { return { nullptr }; }

kernel void test2(cl::constant_ptr<int[]> arg0) {
  cl::constant_ptr<int[]> ptr0 = testFunc0(&arg0);
  cl::constant_ptr<int[]> ptr1 = testFunc1(arg0);
  cl::constant_ptr<int[]> ptr2 = testFunc2(arg0);
  cl::constant_ptr<int[]> *ptr3 = testFunc3(arg0);
  cl::constant_ptr<int[]> &ptr4 = testFunc4(arg0);
  cl::constant_ptr<int[]> ptr5 = testFunc5(arg0);
  cl::constant_ptr<int[]> ptr6 = testFunc6(arg0);
  cl::constant_ptr<int[]> ptr7 = testFunc7(arg0);
  cl::constant_ptr<int[]> ptr8 = testFunc8(arg0);
  
  cl::constant_ptr<int>::pointer p0 = arg0.get();
  
  ptr0 = arg0;
  ptr0 = cl::constant_ptr<int[]>();
  ptr0 = arg0.get();
  ptr0 = nullptr;
  ptr0.swap(ptr1);
  
  __constant int& val = ptr1[0];
  if(arg0) { }
  
  ptr0.release();
  ptr0.reset();
  ptr0.reset(arg0.get());
  ptr0++;
  ++ptr0;
  ptr0--;
  --ptr0;
  ptr0 += 10;
  ptr0 -= 20;
  
  if(arg0 == ptr0) { }
  if(arg0 != ptr0) { }
  if(arg0 < ptr0) { }
  if(arg0 > ptr0) { }
  if(arg0 <= ptr0) { }
  if(arg0 >= ptr0) { }
  
  if(arg0 == nullptr) { }
  if(arg0 != nullptr) { }
  if(arg0 < nullptr) { }
  if(arg0 > nullptr) { }
  if(arg0 <= nullptr) { }
  if(arg0 >= nullptr) { }
  
  if(nullptr == ptr0) { }
  if(nullptr != ptr0) { }
  if(nullptr < ptr0) { }
  if(nullptr > ptr0) { }
  if(nullptr <= ptr0) { }
  if(nullptr >= ptr0) { }
  
  cl::swap(ptr0, ptr1);
}

}