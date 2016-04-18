// RUN: %clang_cc1 %s -triple spir-unknown-unknown -emit-llvm -O0 -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_device_queue>
using namespace cl;

kernel void worker( )
{
    auto lambda = [](int a, local_ptr<float> ptr) { };
    
    auto test1 = get_kernel_work_group_size(lambda, 1, local_ptr<float>::size_type{ 1 });
    auto test2 = get_kernel_preferred_work_group_size_multiple(lambda, 1, local_ptr<float>::size_type{ 1 });
    auto test3 = get_kernel_sub_group_count_for_ndrange(ndrange{ 1 }, lambda, 1, local_ptr<float>::size_type{ 1 });
    auto test4 = get_kernel_max_sub_group_size_for_ndrange(ndrange{ 1 }, lambda, 1, local_ptr<float>::size_type{ 1 });
    auto test5 = get_kernel_local_size_for_sub_group_count(1, lambda, 1, local_ptr<float>::size_type{ 1 });
    auto test6 = get_kernel_max_num_sub_groups(lambda, 1, local_ptr<float>::size_type{ 1 });
}
