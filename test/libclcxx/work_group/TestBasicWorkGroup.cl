// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify
// expected-no-diagnostics

#include <opencl_work_group>
using namespace cl;

kernel void worker()
{
    work_group_all(true);
    work_group_any(false);
    
    work_group_broadcast(int { 1 }, size_t{ 0 });
    work_group_broadcast(uint { 1 }, size_t{ 0 });
    work_group_broadcast(long { 1 }, size_t{ 0 });
    work_group_broadcast(ulong { 1 }, size_t{ 0 });
    work_group_broadcast(float { 1 }, size_t{ 0 });
#ifdef cl_khr_fp16
    work_group_broadcast(half { 1 }, size_t{ 0 });
#endif
#ifdef cl_khr_fp64
    work_group_broadcast(double { 1 }, size_t{ 0 });
#endif

    work_group_broadcast(int { 1 }, size_t{ 0 }, size_t{ 0 });
    work_group_broadcast(uint { 1 }, size_t{ 0 }, size_t{ 0 });
    work_group_broadcast(long { 1 }, size_t{ 0 }, size_t{ 0 });
    work_group_broadcast(ulong { 1 }, size_t{ 0 }, size_t{ 0 });
    work_group_broadcast(float { 1 }, size_t{ 0 }, size_t{ 0 });
#ifdef cl_khr_fp16
    work_group_broadcast(half { 1 }, size_t{ 0 }, size_t{ 0 });
#endif
#ifdef cl_khr_fp64
    work_group_broadcast(double { 1 }, size_t{ 0 }, size_t{ 0 });
#endif

    work_group_broadcast(int { 1 }, size_t{ 0 }, size_t{ 0 }, size_t{ 0 });
    work_group_broadcast(uint { 1 }, size_t{ 0 }, size_t{ 0 }, size_t{ 0 });
    work_group_broadcast(long { 1 }, size_t{ 0 }, size_t{ 0 }, size_t{ 0 });
    work_group_broadcast(ulong { 1 }, size_t{ 0 }, size_t{ 0 }, size_t{ 0 });
    work_group_broadcast(float { 1 }, size_t{ 0 }, size_t{ 0 }, size_t{ 0 });
#ifdef cl_khr_fp16
    work_group_broadcast(half { 1 }, size_t{ 0 }, size_t{ 0 }, size_t{ 0 });
#endif
#ifdef cl_khr_fp64
    work_group_broadcast(double { 1 }, size_t{ 0 }, size_t{ 0 }, size_t{ 0 });
#endif

    work_group_reduce<work_group_op::add>(int { 1 });
    work_group_scan_inclusive<work_group_op::min>(float { 1 });
    work_group_scan_exclusive<work_group_op::max>(ulong { 1 });
}