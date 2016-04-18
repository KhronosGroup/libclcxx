// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL:*

#include <opencl_image>
#include <opencl_pipe>

using namespace cl;

struct A { };

kernel void worker()
{
    static_assert(!is_marker_type<A>::value, "is_marker is passing for structs not inheriting marker_type");
}
