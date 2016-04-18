// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#define cl_khr_mipmap_image_write 1
#include <opencl_image>
using namespace cl; 

kernel void worker(image2d_array<float4, image_access::read> _d2af4r, image2d_array<float4, image_access::write> _d2af4w, image2d_array<float4, image_access::read_write> _d2af4rw, image2d_array<float4, image_access::sample> _d2af4s)
{     _d2af4r.write(float{0}, float4{0, 0, 0, 0});       //BAD QUALIFIER
    _d2af4r.write(float{0}, float4{0, 0, 0, 0}, 2);    //BAD QUALIFIER
    _d2af4w.write(float2{0, 0}, float4{0, 0, 0, 0});       //BAD COORDS TYPE
    _d2af4w.write(float2{0, 0}, float4{0, 0, 0, 0}, 2);    //BAD COORDS TYPE
    _d2af4w.write(float{0}, int4{0, 0, 0, 0});       //BAD INOUT TYPE
    _d2af4w.write(float{0}, int4{0, 0, 0, 0}, 2);    //BAD INOUT TYPE
    _d2af4rw.write(float2{0, 0}, float4{0, 0, 0, 0});       //BAD COORDS TYPE
    _d2af4rw.write(float2{0, 0}, float4{0, 0, 0, 0}, 2);    //BAD COORDS TYPE
    _d2af4rw.write(float{0}, int4{0, 0, 0, 0});       //BAD INOUT TYPE
    _d2af4rw.write(float{0}, int4{0, 0, 0, 0}, 2);    //BAD INOUT TYPE
    _d2af4s.write(float{0}, float4{0, 0, 0, 0});       //BAD QUALIFIER
    _d2af4s.write(float{0}, float4{0, 0, 0, 0}, 2);    //BAD QUALIFIER
}
