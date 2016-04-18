// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -O0 -emit-llvm -o -o /dev/null

#include <opencl_pipe>

cl::pipe<int4> p1; //expected-error{{call to deleted constructor of}}*
//expected-note@__ocl_pipes.h:* {{'pipe' has been explicitly marked deleted here}}*
cl::pipe<int4, cl::pipe_access::write> p2; //expected-error{{call to deleted constructor of}}*
//expected-note@__ocl_pipes.h:* {{'pipe' has been explicitly marked deleted here}}*

struct S
{
  S() { };
};
  
kernel void worker()
{
  cl::pipe<int4> p3; //expected-error{{call to deleted constructor of}}*
  //expected-note@__ocl_pipes.h:* {{'pipe' has been explicitly marked deleted here}}*
  cl::pipe<int4, cl::pipe_access::write> p4; //expected-error{{call to deleted constructor of}}*
  //expected-note@__ocl_pipes.h:* {{'pipe' has been explicitly marked deleted here}}*
  cl::pipe_storage<int, 10> pp1; //expected-error{{no matching constructor for initialization of 'cl::pipe_storage<int, 10>'}}
  // expected-note@__ocl_pipes.h:* {{candidate constructor}}*
  // expected-note@__ocl_pipes.h:* {{candidate constructor}}*
  // expected-note@__ocl_pipes.h:* {{candidate constructor}}*
  
  cl::pipe<int3>::reservation<cl::memory_scope::memory_scope_all_svm_devices> r1; //expected-note{{in instantiation}}*
  // expected-error@__ocl_pipes.h:* {{static_assert failed "Invalid memory scope."}}*
  
  cl::pipe<int3, cl::pipe_access::write>::reservation<cl::memory_scope::memory_scope_all_svm_devices> r2; //expected-note{{in instantiation}}*
  // expected-error@__ocl_pipes.h:* {{static_assert failed "Invalid memory scope."}}*
  cl::pipe<int3>::reservation<cl::memory_scope::memory_scope_work_group> r3; //expected-error{{call to deleted constructor of}}*
  //expected-note@__ocl_pipes.h:* {{'reservation' has been explicitly marked deleted here}}*
  cl::pipe<int3, cl::pipe_access::write>::reservation<cl::memory_scope::memory_scope_work_group> r4; //expected-error{{call to deleted constructor of}}*
  //expected-note@__ocl_pipes.h:* {{'reservation' has been explicitly marked deleted here}}*
}

kernel void worker2(cl::pipe<S> p) { } //expected-note{{in instantiation}}*
// expected-error@__ocl_pipes.h:* {{static_assert failed "Template parameter T in pipe does not satisfy POD type requirements."}}*

kernel void worker2(cl::pipe<S, cl::pipe_access::write> p) { } //expected-note{{in instantiation}}*
// expected-error@__ocl_pipes.h:* {{static_assert failed "Template parameter T in pipe does not satisfy POD type requirements."}}*