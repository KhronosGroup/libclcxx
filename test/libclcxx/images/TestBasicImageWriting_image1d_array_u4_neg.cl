// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#define cl_khr_mipmap_image_write 1
#include <opencl_image>
using namespace cl; 

kernel void worker(image1d_array<uint4, image_access::read> _d1au4r, image1d_array<uint4, image_access::write> _d1au4w, image1d_array<uint4, image_access::read_write> _d1au4rw, image1d_array<uint4, image_access::sample> _d1au4s)
{     _d1au4r.write(float{0}, float4{0, 0, 0, 0});       //BAD QUALIFIER
    _d1au4r.write(float{0}, float4{0, 0, 0, 0}, 2);    //BAD QUALIFIER
    _d1au4w.write(float{0}, float4{0, 0, 0, 0});       //BAD INOUT TYPE
    _d1au4w.write(float{0}, float4{0, 0, 0, 0}, 2);    //BAD INOUT TYPE
    _d1au4w.write(float2{0, 0}, uint4{0, 0, 0, 0});       //BAD COORDS TYPE
    _d1au4w.write(float2{0, 0}, uint4{0, 0, 0, 0}, 2);    //BAD COORDS TYPE
    _d1au4rw.write(float{0}, float4{0, 0, 0, 0});       //BAD INOUT TYPE
    _d1au4rw.write(float{0}, float4{0, 0, 0, 0}, 2);    //BAD INOUT TYPE
    _d1au4rw.write(float2{0, 0}, uint4{0, 0, 0, 0});       //BAD COORDS TYPE
    _d1au4rw.write(float2{0, 0}, uint4{0, 0, 0, 0}, 2);    //BAD COORDS TYPE
    _d1au4s.write(float{0}, float4{0, 0, 0, 0});       //BAD QUALIFIER
    _d1au4s.write(float{0}, float4{0, 0, 0, 0}, 2);    //BAD QUALIFIER
}
