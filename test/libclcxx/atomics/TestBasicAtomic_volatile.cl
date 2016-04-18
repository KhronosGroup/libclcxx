// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -nobuiltininc -verify -O1 -o -
// expected-no-diagnostics

#include <opencl_work_item>
#include <opencl_atomic>
__kernel void find_targets(__global uint* image, uint target, __global volatile cl::atomic_uint *numTargetsFound, __global volatile cl::atomic_uint *targetLocations)
{
 size_t i = cl::get_global_id(0);
 uint index;
 if(image[i] == target) {
   index = cl::atomic_fetch_add_explicit(numTargetsFound, static_cast<uint>(1), cl::memory_order_relaxed, cl::memory_scope_device); 
   cl::atomic_exchange_explicit(&targetLocations[index], i, cl::memory_order_relaxed, cl::memory_scope_all_svm_devices); 
 }
}
