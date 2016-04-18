// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#define cl_khr_mipmap_image 1
#include <opencl_image>
using namespace cl; 

kernel void worker(image1d<uint4, image_access::read> _d1u4r, image1d<uint4, image_access::write> _d1u4w, image1d<uint4, image_access::read_write> _d1u4rw, image1d<uint4, image_access::sample> _d1u4s)
{     float4 _d1u4r_rf4f1 = _d1u4r.read(float{0});      //BAD INOUT TYPE
    float4 _d1u4r_rf4f1l = _d1u4r.read(float{0}, 2);  //BAD INOUT TYPE
    uint4 _d1u4r_ru4f2 = _d1u4r.read(float2{0, 0});      //BAD COORDS TYPE
    uint4 _d1u4r_ru4f2l = _d1u4r.read(float2{0, 0}, 2);  //BAD COORDS TYPE
    float4 _d1u4w_rf4f1 = _d1u4w.read(float{0});      //BAD QUALIFIER
    float4 _d1u4w_rf4f1l = _d1u4w.read(float{0}, 2);  //BAD QUALIFIER
    float4 _d1u4rw_rf4f1 = _d1u4rw.read(float{0});      //BAD INOUT TYPE
    float4 _d1u4rw_rf4f1l = _d1u4rw.read(float{0}, 2);  //BAD INOUT TYPE
    uint4 _d1u4rw_ru4f2 = _d1u4rw.read(float2{0, 0});      //BAD COORDS TYPE
    uint4 _d1u4rw_ru4f2l = _d1u4rw.read(float2{0, 0}, 2);  //BAD COORDS TYPE
    float4 _d1u4s_rf4f1 = _d1u4s.read(float{0});      //BAD QUALIFIER
    float4 _d1u4s_rf4f1l = _d1u4s.read(float{0}, 2);  //BAD QUALIFIER
}
