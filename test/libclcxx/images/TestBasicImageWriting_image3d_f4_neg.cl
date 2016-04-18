// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#define cl_khr_mipmap_image_write 1
#include <opencl_image>
using namespace cl; 

kernel void worker(image3d<float4, image_access::read> _d3f4r, image3d<float4, image_access::write> _d3f4w, image3d<float4, image_access::read_write> _d3f4rw, image3d<float4, image_access::sample> _d3f4s)
{     _d3f4r.write(float{0}, float4{0, 0, 0, 0});       //BAD QUALIFIER
    _d3f4r.write(float{0}, float4{0, 0, 0, 0}, 2);    //BAD QUALIFIER
    _d3f4w.write(float2{0, 0}, float4{0, 0, 0, 0});       //BAD COORDS TYPE
    _d3f4w.write(float2{0, 0}, float4{0, 0, 0, 0}, 2);    //BAD COORDS TYPE
    _d3f4w.write(float{0}, int4{0, 0, 0, 0});       //BAD INOUT TYPE
    _d3f4w.write(float{0}, int4{0, 0, 0, 0}, 2);    //BAD INOUT TYPE
    _d3f4rw.write(float2{0, 0}, float4{0, 0, 0, 0});       //BAD COORDS TYPE
    _d3f4rw.write(float2{0, 0}, float4{0, 0, 0, 0}, 2);    //BAD COORDS TYPE
    _d3f4rw.write(float{0}, int4{0, 0, 0, 0});       //BAD INOUT TYPE
    _d3f4rw.write(float{0}, int4{0, 0, 0, 0}, 2);    //BAD INOUT TYPE
    _d3f4s.write(float{0}, float4{0, 0, 0, 0});       //BAD QUALIFIER
    _d3f4s.write(float{0}, float4{0, 0, 0, 0}, 2);    //BAD QUALIFIER
}
