// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -O0 -o /dev/null
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -O3 -o /dev/null
// expected-no-diagnostics

#include <opencl_memory>
#include <opencl_array>

kernel void test0()
{
  cl::array<int, 10> arr0;
  for(auto it = arr0.begin(); it != arr0.end(); ++it)
    *it = 0;
  
  for(auto it = arr0.rbegin(); it != arr0.rend(); ++it)
    *it = 0;
  
  for(auto it = arr0.cbegin(); it != arr0.cend(); ++it)
    int val = *it;
	
  for(auto it = arr0.crbegin(); it != arr0.crend(); ++it)
    int val = *it;
   
  if(arr0.size() > 5) { }
  if(arr0.max_size() > 5) { }
  if(arr0.empty()) { }
  
  arr0[0] = 1;
  arr0.front() = 1;
  arr0.back() = 1;
  
  *(arr0.data()) = 1;
  
  size_t size = cl::tuple_size<cl::array<int, 10>>::value;
  cl::tuple_element<0, cl::array<int, 10>>::type val2 = arr0[0];
  
  int& ref = cl::get<0>(arr0);
  int ref2 = cl::get<0>(cl::array<int, 10>{1});
}

kernel void test1()
{
  const cl::array<int, 10> arr0 = { 0 };
  for(auto it = arr0.begin(); it != arr0.end(); ++it)
    int val = *it;
  
  for(auto it = arr0.rbegin(); it != arr0.rend(); ++it)
    int val = *it;
  
  for(auto it = arr0.cbegin(); it != arr0.cend(); ++it)
    int val = *it;
	
  for(auto it = arr0.crbegin(); it != arr0.crend(); ++it)
    int val = *it;
   
  if(arr0.size() > 5) { }
  if(arr0.max_size() > 5) { }
  if(arr0.empty()) { }
  
  const int &ref3 = arr0[0];
  const int &ref4 = arr0.front();
  const int &ref5 = arr0.back();
  
  int val3 = *(arr0.data());
  
  size_t size = cl::tuple_size<cl::array<int, 10>>::value;
  cl::tuple_element<0, cl::array<int, 10>>::type val2 = arr0[0];
  
  const int& ref = cl::get<0>(arr0);
}

kernel void test2(cl::global<cl::array<int, 10>> &arr0)
{
  for(auto it = arr0.begin(); it != arr0.end(); ++it)
    *it = 0;
  
  for(auto it = arr0.rbegin(); it != arr0.rend(); ++it)
    *it = 0;
  
  for(auto it = arr0.cbegin(); it != arr0.cend(); ++it)
    int val = *it;
	
  for(auto it = arr0.crbegin(); it != arr0.crend(); ++it)
    int val = *it;
   
  if(arr0.size() > 5) { }
  if(arr0.max_size() > 5) { }
  if(arr0.empty()) { }
  
  arr0[0] = 1;
  arr0.front() = 1;
  arr0.back() = 1;
  
  *(arr0.data()) = 1;
  
  size_t size = cl::tuple_size<cl::array<int, 10>>::value;
  cl::tuple_element<0, cl::array<int, 10>>::type val2 = arr0[0];
  
  int& ref = cl::get<0>(arr0);
}

kernel void test3(cl::global<cl::array<int, 10>> *arr0)
{
  for(auto it = arr0->begin(); it != arr0->end(); ++it)
    *it = 0;
  
  for(auto it = arr0->rbegin(); it != arr0->rend(); ++it)
    *it = 0;
  
  for(auto it = arr0->cbegin(); it != arr0->cend(); ++it)
    int val = *it;
	
  for(auto it = arr0->crbegin(); it != arr0->crend(); ++it)
    int val = *it;
   
  if(arr0->size() > 5) { }
  if(arr0->max_size() > 5) { }
  if(arr0->empty()) { }
  
  (*arr0)[0] = 1;
  arr0->front() = 1;
  arr0->back() = 1;
  
  *(arr0->data()) = 1;
  
  size_t size = cl::tuple_size<cl::array<int, 10>>::value;
  cl::tuple_element<0, cl::array<int, 10>>::type val2 = (*arr0)[0];
  
  int& ref = cl::get<0>(*arr0);
}

cl::array<int, 10> garr;

kernel void test4()
{
  for(auto it = garr.begin(); it != garr.end(); ++it)
    *it = 0;
  
  for(auto it = garr.rbegin(); it != garr.rend(); ++it)
    *it = 0;
  
  for(auto it = garr.cbegin(); it != garr.cend(); ++it)
    int val = *it;
	
  for(auto it = garr.crbegin(); it != garr.crend(); ++it)
    int val = *it;
   
  if(garr.size() > 5) { }
  if(garr.max_size() > 5) { }
  if(garr.empty()) { }
  
  garr[0] = 1;
  garr.front() = 1;
  garr.back() = 1;
  
  *(garr.data()) = 1;
  
  size_t size = cl::tuple_size<cl::array<int, 10>>::value;
  cl::tuple_element<0, cl::array<int, 10>>::type val2 = garr[0];
  
  int& ref = cl::get<0>(garr);
  int ref2 = cl::get<0>(cl::array<int, 10>{1});
}

kernel void test5()
{
  cl::local<cl::array<int, 10>> arr0;
  for(auto it = arr0.begin(); it != arr0.end(); ++it)
    *it = 0;
  
  for(auto it = arr0.rbegin(); it != arr0.rend(); ++it)
    *it = 0;
  
  for(auto it = arr0.cbegin(); it != arr0.cend(); ++it)
    int val = *it;
	
  for(auto it = arr0.crbegin(); it != arr0.crend(); ++it)
    int val = *it;
   
  if(arr0.size() > 5) { }
  if(arr0.max_size() > 5) { }
  if(arr0.empty()) { }
  
  arr0[0] = 1;
  arr0.front() = 1;
  arr0.back() = 1;
  
  *(arr0.data()) = 1;
  
  size_t size = cl::tuple_size<cl::array<int, 10>>::value;
  cl::tuple_element<0, cl::array<int, 10>>::type val2 = arr0[0];
  
  int& ref = cl::get<0>(arr0);
}

kernel void test6()
{
  cl::priv<cl::array<int, 10>> arr0;
  for(auto it = arr0.begin(); it != arr0.end(); ++it)
    *it = 0;
  
  for(auto it = arr0.rbegin(); it != arr0.rend(); ++it)
    *it = 0;
  
  for(auto it = arr0.cbegin(); it != arr0.cend(); ++it)
    int val = *it;
	
  for(auto it = arr0.crbegin(); it != arr0.crend(); ++it)
    int val = *it;
   
  if(arr0.size() > 5) { }
  if(arr0.max_size() > 5) { }
  if(arr0.empty()) { }
  
  arr0[0] = 1;
  arr0.front() = 1;
  arr0.back() = 1;
  
  *(arr0.data()) = 1;
  
  size_t size = cl::tuple_size<cl::array<int, 10>>::value;
  cl::tuple_element<0, cl::array<int, 10>>::type val2 = arr0[0];
  
  int& ref = cl::get<0>(arr0);
}
