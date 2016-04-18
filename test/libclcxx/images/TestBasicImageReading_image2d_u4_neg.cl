// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#define cl_khr_mipmap_image 1
#include <opencl_image>
using namespace cl; 

kernel void worker(image2d<uint4, image_access::read> _d2u4r, image2d<uint4, image_access::write> _d2u4w, image2d<uint4, image_access::read_write> _d2u4rw, image2d<uint4, image_access::sample> _d2u4s)
{     float4 _d2u4r_rf4f1 = _d2u4r.read(float{0});      //BAD INOUT TYPE
    float4 _d2u4r_rf4f1l = _d2u4r.read(float{0}, 2);  //BAD INOUT TYPE
    uint4 _d2u4r_ru4f2 = _d2u4r.read(float2{0, 0});      //BAD COORDS TYPE
    uint4 _d2u4r_ru4f2l = _d2u4r.read(float2{0, 0}, 2);  //BAD COORDS TYPE
    float4 _d2u4w_rf4f1 = _d2u4w.read(float{0});      //BAD QUALIFIER
    float4 _d2u4w_rf4f1l = _d2u4w.read(float{0}, 2);  //BAD QUALIFIER
    float4 _d2u4rw_rf4f1 = _d2u4rw.read(float{0});      //BAD INOUT TYPE
    float4 _d2u4rw_rf4f1l = _d2u4rw.read(float{0}, 2);  //BAD INOUT TYPE
    uint4 _d2u4rw_ru4f2 = _d2u4rw.read(float2{0, 0});      //BAD COORDS TYPE
    uint4 _d2u4rw_ru4f2l = _d2u4rw.read(float2{0, 0}, 2);  //BAD COORDS TYPE
    float4 _d2u4s_rf4f1 = _d2u4s.read(float{0});      //BAD QUALIFIER
    float4 _d2u4s_rf4f1l = _d2u4s.read(float{0}, 2);  //BAD QUALIFIER
}
