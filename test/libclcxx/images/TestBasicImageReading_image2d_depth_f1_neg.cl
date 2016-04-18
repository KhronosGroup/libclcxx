// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#define cl_khr_mipmap_image 1
#include <opencl_image>
using namespace cl; 

kernel void worker(image2d_depth<float, image_access::read> _d2df1r, image2d_depth<float, image_access::write> _d2df1w, image2d_depth<float, image_access::read_write> _d2df1rw, image2d_depth<float, image_access::sample> _d2df1s)
{     float4 _d2df1r_rf4f2 = _d2df1r.read(float2{0, 0});      //BAD COORDS TYPE
    float4 _d2df1r_rf4f2l = _d2df1r.read(float2{0, 0}, 2);  //BAD COORDS TYPE
    float4 _d2df1w_rf4f1 = _d2df1w.read(float{0});      //BAD QUALIFIER
    float4 _d2df1w_rf4f1l = _d2df1w.read(float{0}, 2);  //BAD QUALIFIER
    float4 _d2df1rw_rf4f2 = _d2df1rw.read(float2{0, 0});      //BAD COORDS TYPE
    float4 _d2df1rw_rf4f2l = _d2df1rw.read(float2{0, 0}, 2);  //BAD COORDS TYPE
    float4 _d2df1s_rf4f1 = _d2df1s.read(float{0});      //BAD QUALIFIER
    float4 _d2df1s_rf4f1l = _d2df1s.read(float{0}, 2);  //BAD QUALIFIER
}
