// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_vec>
#include <opencl_relational>
using namespace cl;

kernel void worker()
{
    vec<float, 4> f4;
    float4 bi;
    float e;
    
    if (all(f4 == f4)) return; if (all(f4 == bi)) return; if (all(bi == f4)) return;
    if (all(f4 != f4)) return; if (all(f4 != bi)) return; if (all(bi != f4)) return;
    if (all(f4 > f4)) return; if (all(f4 > bi)) return; if (all(bi > f4)) return;
    if (all(f4 < f4)) return; if (all(f4 < bi)) return; if (all(bi < f4)) return;
    if (all(f4 >= f4)) return; if (all(f4 >= bi)) return; if (all(bi >= f4)) return;
    if (all(f4 <= f4)) return; if (all(f4 <= bi)) return; if (all(bi <= f4)) return;
    
    {
        auto r0 = f4 + f4;
        auto r1 = f4 + bi;
        auto r2 = bi + f4;
        auto r3 = f4 + e;
        auto r4 = e + f4;
    }
    {
        auto r0 = f4 - f4;
        auto r1 = f4 - bi;
        auto r2 = bi - f4;
        auto r3 = f4 - e;
        auto r4 = e - f4;
    }
    {
        auto r0 = f4 * f4;
        auto r1 = f4 * bi;
        auto r2 = bi * f4;
        auto r3 = f4 * e;
        auto r4 = e * f4;
    }
    {
        auto r0 = f4 / f4;
        auto r1 = f4 / bi;
        auto r2 = bi / f4;
        auto r3 = f4 / e;
        auto r4 = e / f4;
    }
}