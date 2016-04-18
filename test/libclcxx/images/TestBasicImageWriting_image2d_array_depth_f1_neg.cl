// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#define cl_khr_mipmap_image_write 1
#include <opencl_image>
using namespace cl; 

kernel void worker(image2d_array_depth<float, image_access::read> _d2adf1r, image2d_array_depth<float, image_access::write> _d2adf1w, image2d_array_depth<float, image_access::read_write> _d2adf1rw, image2d_array_depth<float, image_access::sample> _d2adf1s)
{     _d2adf1r.write(float{0}, float4{0, 0, 0, 0});       //BAD QUALIFIER
    _d2adf1r.write(float{0}, float4{0, 0, 0, 0}, 2);    //BAD QUALIFIER
    _d2adf1w.write(float{0}, float4{0, 0, 0, 0});       //BAD INOUT TYPE
    _d2adf1w.write(float{0}, float4{0, 0, 0, 0}, 2);    //BAD INOUT TYPE
    _d2adf1w.write(float2{0, 0}, 0);       //BAD COORDS TYPE
    _d2adf1w.write(float2{0, 0}, 0, 2);    //BAD COORDS TYPE
    _d2adf1rw.write(float{0}, float4{0, 0, 0, 0});       //BAD INOUT TYPE
    _d2adf1rw.write(float{0}, float4{0, 0, 0, 0}, 2);    //BAD INOUT TYPE
    _d2adf1rw.write(float2{0, 0}, 0);       //BAD COORDS TYPE
    _d2adf1rw.write(float2{0, 0}, 0, 2);    //BAD COORDS TYPE
    _d2adf1s.write(float{0}, float4{0, 0, 0, 0});       //BAD QUALIFIER
    _d2adf1s.write(float{0}, float4{0, 0, 0, 0}, 2);    //BAD QUALIFIER
}
