// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -O0 -o /dev/null
// expected-no-diagnostics


#include <opencl_memory>

kernel void worker()
{
  cl::mem_fence f0 = cl::mem_fence::local | cl::mem_fence::global;
  cl::mem_fence f1;
  if((f0 & cl::mem_fence::local) == cl::mem_fence::local) { }
  if((f0 & ~cl::mem_fence::local) == ~cl::mem_fence::local) { }
  if((f0 ^ f1) == cl::mem_fence::local) { }
}