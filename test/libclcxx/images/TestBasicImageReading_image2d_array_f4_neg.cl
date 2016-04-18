// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#define cl_khr_mipmap_image 1
#include <opencl_image>
using namespace cl; 

kernel void worker(image2d_array<float4, image_access::read> _d2af4r, image2d_array<float4, image_access::write> _d2af4w, image2d_array<float4, image_access::read_write> _d2af4rw, image2d_array<float4, image_access::sample> _d2af4s)
{     float4 _d2af4r_rf4f2 = _d2af4r.read(float2{0, 0});      //BAD COORDS TYPE
    float4 _d2af4r_rf4f2l = _d2af4r.read(float2{0, 0}, 2);  //BAD COORDS TYPE
    int4 _d2af4r_ri4f1 = _d2af4r.read(float{0});      //BAD INOUT TYPE
    int4 _d2af4r_ri4f1l = _d2af4r.read(float{0}, 2);  //BAD INOUT TYPE
    float4 _d2af4w_rf4f1 = _d2af4w.read(float{0});      //BAD QUALIFIER
    float4 _d2af4w_rf4f1l = _d2af4w.read(float{0}, 2);  //BAD QUALIFIER
    float4 _d2af4rw_rf4f2 = _d2af4rw.read(float2{0, 0});      //BAD COORDS TYPE
    float4 _d2af4rw_rf4f2l = _d2af4rw.read(float2{0, 0}, 2);  //BAD COORDS TYPE
    int4 _d2af4rw_ri4f1 = _d2af4rw.read(float{0});      //BAD INOUT TYPE
    int4 _d2af4rw_ri4f1l = _d2af4rw.read(float{0}, 2);  //BAD INOUT TYPE
    float4 _d2af4s_rf4f1 = _d2af4s.read(float{0});      //BAD QUALIFIER
    float4 _d2af4s_rf4f1l = _d2af4s.read(float{0}, 2);  //BAD QUALIFIER
}
