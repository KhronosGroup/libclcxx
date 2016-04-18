// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#define cl_khr_mipmap_image 1
#include <opencl_image>
using namespace cl; 

kernel void worker(image3d<float4, image_access::read> _d3f4r, image3d<float4, image_access::write> _d3f4w, image3d<float4, image_access::read_write> _d3f4rw, image3d<float4, image_access::sample> _d3f4s)
{     float4 _d3f4r_rf4f2 = _d3f4r.read(float2{0, 0});      //BAD COORDS TYPE
    float4 _d3f4r_rf4f2l = _d3f4r.read(float2{0, 0}, 2);  //BAD COORDS TYPE
    int4 _d3f4r_ri4f1 = _d3f4r.read(float{0});      //BAD INOUT TYPE
    int4 _d3f4r_ri4f1l = _d3f4r.read(float{0}, 2);  //BAD INOUT TYPE
    float4 _d3f4w_rf4f1 = _d3f4w.read(float{0});      //BAD QUALIFIER
    float4 _d3f4w_rf4f1l = _d3f4w.read(float{0}, 2);  //BAD QUALIFIER
    float4 _d3f4rw_rf4f2 = _d3f4rw.read(float2{0, 0});      //BAD COORDS TYPE
    float4 _d3f4rw_rf4f2l = _d3f4rw.read(float2{0, 0}, 2);  //BAD COORDS TYPE
    int4 _d3f4rw_ri4f1 = _d3f4rw.read(float{0});      //BAD INOUT TYPE
    int4 _d3f4rw_ri4f1l = _d3f4rw.read(float{0}, 2);  //BAD INOUT TYPE
    float4 _d3f4s_rf4f1 = _d3f4s.read(float{0});      //BAD QUALIFIER
    float4 _d3f4s_rf4f1l = _d3f4s.read(float{0}, 2);  //BAD QUALIFIER
}
