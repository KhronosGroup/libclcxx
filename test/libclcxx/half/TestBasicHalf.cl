// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -pedantic -O0 -Wall -Wno-unused-variable -verify -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -pedantic -O0 -Wall -Wno-unused-variable -verify -emit-llvm -o - -cl-fp16-enable
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -pedantic -O0 -Wall -Wno-unused-variable -verify -emit-llvm -o - -cl-fp64-enable
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -pedantic -O0 -Wall -Wno-unused-variable -verify -emit-llvm -o - -cl-fp64-enable
// expected-no-diagnostics

#pragma OPENCL EXTENSION cl_khr_fp16: disable
#pragma OPENCL EXTENSION cl_khr_fp64: disable

#ifdef cl_khr_fp16
    #pragma OPENCL EXTENSION cl_khr_fp16: enable
#endif

#ifdef cl_khr_fp64
    #pragma OPENCL EXTENSION cl_khr_fp64: enable
#endif

#include <opencl_half>

kernel void worker(half arg0, cl::fp16 arg1)
{
  half h0 = 0.0h;
  float f0 = 0.0f;
  cl::fp16 v0;
  cl::fp16 v1(v0);
  cl::fp16 v2{cl::fp16(h0)};
  v2 = v0;
  v2 = {cl::fp16(h0)};
  
  cl::fp16 v3(h0);
  v3 = h0;
  half h1 = v3;
  v3++;
  ++v3;
  v3--;
  --v3;
  v3+=v1;
  v3-=v1;
  v3*=v1;
  v3/=v1;
  if(v0) { }
  if(!v0) { }
  if(v3 == v1) { }
  if(v3 != v1) { }
  if(v3 < v1) { }
  if(v3 > v1) { }
  if(v3 <= v1) { }
  if(v3 >= v1) { }
  v3 = v3 + v1;
  v3 = v3 - v1;
  v3 = v3 * v1;
  v3 = v3 / v1;
  
  cl::fp16 v4(f0);
  v4 = f0;
  float f1 = v4;
  
#ifdef cl_khr_fp64
  double d0 = 0.0;
  cl::fp16 v5(d0);
  v5 = d0;
  double d1 = v5;
#endif

  
}
