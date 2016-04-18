// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#define cl_khr_mipmap_image 1
#include <opencl_image>
using namespace cl; 

kernel void worker(image1d<float4, image_access::read> _d1f4r, image1d<float4, image_access::write> _d1f4w, image1d<float4, image_access::read_write> _d1f4rw, image1d<float4, image_access::sample> _d1f4s)
{     float4 _d1f4r_rf4f2 = _d1f4r.read(float2{0, 0});      //BAD COORDS TYPE
    float4 _d1f4r_rf4f2l = _d1f4r.read(float2{0, 0}, 2);  //BAD COORDS TYPE
    int4 _d1f4r_ri4f1 = _d1f4r.read(float{0});      //BAD INOUT TYPE
    int4 _d1f4r_ri4f1l = _d1f4r.read(float{0}, 2);  //BAD INOUT TYPE
    float4 _d1f4w_rf4f1 = _d1f4w.read(float{0});      //BAD QUALIFIER
    float4 _d1f4w_rf4f1l = _d1f4w.read(float{0}, 2);  //BAD QUALIFIER
    float4 _d1f4rw_rf4f2 = _d1f4rw.read(float2{0, 0});      //BAD COORDS TYPE
    float4 _d1f4rw_rf4f2l = _d1f4rw.read(float2{0, 0}, 2);  //BAD COORDS TYPE
    int4 _d1f4rw_ri4f1 = _d1f4rw.read(float{0});      //BAD INOUT TYPE
    int4 _d1f4rw_ri4f1l = _d1f4rw.read(float{0}, 2);  //BAD INOUT TYPE
    float4 _d1f4s_rf4f1 = _d1f4s.read(float{0});      //BAD QUALIFIER
    float4 _d1f4s_rf4f1l = _d1f4s.read(float{0}, 2);  //BAD QUALIFIER
}
