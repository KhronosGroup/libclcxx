// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#define cl_khr_mipmap_image 1
#include <opencl_image>
using namespace cl; 

kernel void worker(image2d<int4, image_access::read> _d2i4r, image2d<int4, image_access::write> _d2i4w, image2d<int4, image_access::read_write> _d2i4rw, image2d<int4, image_access::sample> _d2i4s)
{     float4 _d2i4r_rf4f1 = _d2i4r.read(float{0});      //BAD INOUT TYPE
    float4 _d2i4r_rf4f1l = _d2i4r.read(float{0}, 2);  //BAD INOUT TYPE
    int4 _d2i4r_ri4f2 = _d2i4r.read(float2{0, 0});      //BAD COORDS TYPE
    int4 _d2i4r_ri4f2l = _d2i4r.read(float2{0, 0}, 2);  //BAD COORDS TYPE
    float4 _d2i4w_rf4f1 = _d2i4w.read(float{0});      //BAD QUALIFIER
    float4 _d2i4w_rf4f1l = _d2i4w.read(float{0}, 2);  //BAD QUALIFIER
    float4 _d2i4rw_rf4f1 = _d2i4rw.read(float{0});      //BAD INOUT TYPE
    float4 _d2i4rw_rf4f1l = _d2i4rw.read(float{0}, 2);  //BAD INOUT TYPE
    int4 _d2i4rw_ri4f2 = _d2i4rw.read(float2{0, 0});      //BAD COORDS TYPE
    int4 _d2i4rw_ri4f2l = _d2i4rw.read(float2{0, 0}, 2);  //BAD COORDS TYPE
    float4 _d2i4s_rf4f1 = _d2i4s.read(float{0});      //BAD QUALIFIER
    float4 _d2i4s_rf4f1l = _d2i4s.read(float{0}, 2);  //BAD QUALIFIER
}
