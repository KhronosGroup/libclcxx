// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#include <opencl_image>
using namespace cl; 

kernel void worker(image1d<float4, image_access::read> _d1f4r, image1d<float4, image_access::write> _d1f4w, image1d<float4, image_access::read_write> _d1f4rw, image1d<float4, image_access::sample> _d1f4s, image1d<int4, image_access::read> _d1i4r, image1d<int4, image_access::write> _d1i4w, image1d<int4, image_access::read_write> _d1i4rw, image1d<int4, image_access::sample> _d1i4s, image1d<uint4, image_access::read> _d1u4r, image1d<uint4, image_access::write> _d1u4w, image1d<uint4, image_access::read_write> _d1u4rw, image1d<uint4, image_access::sample> _d1u4s, image2d<float4, image_access::read> _d2f4r, image2d<float4, image_access::write> _d2f4w, image2d<float4, image_access::read_write> _d2f4rw, image2d<float4, image_access::sample> _d2f4s, image2d<int4, image_access::read> _d2i4r, image2d<int4, image_access::write> _d2i4w, image2d<int4, image_access::read_write> _d2i4rw, image2d<int4, image_access::sample> _d2i4s, image2d<uint4, image_access::read> _d2u4r, image2d<uint4, image_access::write> _d2u4w, image2d<uint4, image_access::read_write> _d2u4rw, image2d<uint4, image_access::sample> _d2u4s, image3d<float4, image_access::read> _d3f4r, image3d<float4, image_access::write> _d3f4w, image3d<float4, image_access::read_write> _d3f4rw, image3d<float4, image_access::sample> _d3f4s, image3d<int4, image_access::read> _d3i4r, image3d<int4, image_access::write> _d3i4w, image3d<int4, image_access::read_write> _d3i4rw, image3d<int4, image_access::sample> _d3i4s, image3d<uint4, image_access::read> _d3u4r, image3d<uint4, image_access::write> _d3u4w, image3d<uint4, image_access::read_write> _d3u4rw, image3d<uint4, image_access::sample> _d3u4s, image2d_depth<float, image_access::read> _d2df1r, image2d_depth<float, image_access::write> _d2df1w, image2d_depth<float, image_access::read_write> _d2df1rw, image2d_depth<float, image_access::sample> _d2df1s)
{     int _d1f4r_as = _d1f4r.array_size();
    int _d1f4w_as = _d1f4w.array_size();
    int _d1f4rw_as = _d1f4rw.array_size();
    int _d1f4s_as = _d1f4s.array_size();
    int _d1i4r_as = _d1i4r.array_size();
    int _d1i4w_as = _d1i4w.array_size();
    int _d1i4rw_as = _d1i4rw.array_size();
    int _d1i4s_as = _d1i4s.array_size();
    int _d1u4r_as = _d1u4r.array_size();
    int _d1u4w_as = _d1u4w.array_size();
    int _d1u4rw_as = _d1u4rw.array_size();
    int _d1u4s_as = _d1u4s.array_size();
    int _d2f4r_as = _d2f4r.array_size();
    int _d2f4w_as = _d2f4w.array_size();
    int _d2f4rw_as = _d2f4rw.array_size();
    int _d2f4s_as = _d2f4s.array_size();
    int _d2i4r_as = _d2i4r.array_size();
    int _d2i4w_as = _d2i4w.array_size();
    int _d2i4rw_as = _d2i4rw.array_size();
    int _d2i4s_as = _d2i4s.array_size();
    int _d2u4r_as = _d2u4r.array_size();
    int _d2u4w_as = _d2u4w.array_size();
    int _d2u4rw_as = _d2u4rw.array_size();
    int _d2u4s_as = _d2u4s.array_size();
    int _d3f4r_as = _d3f4r.array_size();
    int _d3f4w_as = _d3f4w.array_size();
    int _d3f4rw_as = _d3f4rw.array_size();
    int _d3f4s_as = _d3f4s.array_size();
    int _d3i4r_as = _d3i4r.array_size();
    int _d3i4w_as = _d3i4w.array_size();
    int _d3i4rw_as = _d3i4rw.array_size();
    int _d3i4s_as = _d3i4s.array_size();
    int _d3u4r_as = _d3u4r.array_size();
    int _d3u4w_as = _d3u4w.array_size();
    int _d3u4rw_as = _d3u4rw.array_size();
    int _d3u4s_as = _d3u4s.array_size();
    int _d2df1r_as = _d2df1r.array_size();
    int _d2df1w_as = _d2df1w.array_size();
    int _d2df1rw_as = _d2df1rw.array_size();
    int _d2df1s_as = _d2df1s.array_size();
}
