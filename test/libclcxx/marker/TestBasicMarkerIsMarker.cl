// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_image>
#include <opencl_pipe>

using namespace cl;

kernel void worker(image1d<float4, image_access::write> image,
                   pipe<int4, cl::pipe_access::read> _pipe)
{
    static_assert(is_marker_type<image1d<float4, image_access::write>>::value, "images should be marker types");
    static_assert(is_marker_type<pipe<int4, pipe_access::read>>::value, "pipes should be marker types");
}
