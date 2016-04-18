// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#include <opencl_image>
using namespace cl; 

kernel void worker(image3d<uint4, image_access::read> _d3u4r, image3d<uint4, image_access::write> _d3u4w, image3d<uint4, image_access::read_write> _d3u4rw, image3d<uint4, image_access::sample> _d3u4s)
{     _d3u4r.write(float{0}, float4{0, 0, 0, 0});       //BAD QUALIFIER
    _d3u4r.write(float{0}, float4{0, 0, 0, 0}, 2);    //BAD QUALIFIER
    _d3u4w.write(float{0}, float4{0, 0, 0, 0});       //BAD INOUT TYPE
    _d3u4w.write(float{0}, float4{0, 0, 0, 0}, 2);    //BAD INOUT TYPE
    _d3u4w.write(float2{0, 0}, uint4{0, 0, 0, 0});       //BAD COORDS TYPE
    _d3u4w.write(float2{0, 0}, uint4{0, 0, 0, 0}, 2);    //BAD COORDS TYPE
    _d3u4rw.write(float{0}, float4{0, 0, 0, 0});       //BAD INOUT TYPE
    _d3u4rw.write(float{0}, float4{0, 0, 0, 0}, 2);    //BAD INOUT TYPE
    _d3u4rw.write(float2{0, 0}, uint4{0, 0, 0, 0});       //BAD COORDS TYPE
    _d3u4rw.write(float2{0, 0}, uint4{0, 0, 0, 0}, 2);    //BAD COORDS TYPE
    _d3u4s.write(float{0}, float4{0, 0, 0, 0});       //BAD QUALIFIER
    _d3u4s.write(float{0}, float4{0, 0, 0, 0}, 2);    //BAD QUALIFIER
}
