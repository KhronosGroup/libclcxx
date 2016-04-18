// RUN: %clang_cc1 %s -triple spir-unknown-unknown -emit-llvm -O0 -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_device_queue>
using namespace cl;

global<uint> value;

kernel void worker()
{
    event e;
    e = make_user_event();
    
    e.retain();
    e.release();
    
    if (e.is_valid())
        e.set_status(event_status::complete);
    else
        e.set_status(event_status::error);
    
    if (e)
        e.profiling_info(event_profiling_info::exec_time, value.ptr());
}
