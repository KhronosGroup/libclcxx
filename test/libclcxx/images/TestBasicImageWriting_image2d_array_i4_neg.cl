// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#define cl_khr_mipmap_image_write 1
#include <opencl_image>
using namespace cl; 

kernel void worker(image2d_array<int4, image_access::read> _d2ai4r, image2d_array<int4, image_access::write> _d2ai4w, image2d_array<int4, image_access::read_write> _d2ai4rw, image2d_array<int4, image_access::sample> _d2ai4s)
{     _d2ai4r.write(float{0}, float4{0, 0, 0, 0});       //BAD QUALIFIER
    _d2ai4r.write(float{0}, float4{0, 0, 0, 0}, 2);    //BAD QUALIFIER
    _d2ai4w.write(float{0}, float4{0, 0, 0, 0});       //BAD INOUT TYPE
    _d2ai4w.write(float{0}, float4{0, 0, 0, 0}, 2);    //BAD INOUT TYPE
    _d2ai4w.write(float2{0, 0}, int4{0, 0, 0, 0});       //BAD COORDS TYPE
    _d2ai4w.write(float2{0, 0}, int4{0, 0, 0, 0}, 2);    //BAD COORDS TYPE
    _d2ai4rw.write(float{0}, float4{0, 0, 0, 0});       //BAD INOUT TYPE
    _d2ai4rw.write(float{0}, float4{0, 0, 0, 0}, 2);    //BAD INOUT TYPE
    _d2ai4rw.write(float2{0, 0}, int4{0, 0, 0, 0});       //BAD COORDS TYPE
    _d2ai4rw.write(float2{0, 0}, int4{0, 0, 0, 0}, 2);    //BAD COORDS TYPE
    _d2ai4s.write(float{0}, float4{0, 0, 0, 0});       //BAD QUALIFIER
    _d2ai4s.write(float{0}, float4{0, 0, 0, 0}, 2);    //BAD QUALIFIER
}
