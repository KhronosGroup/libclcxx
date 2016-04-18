// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_limits>
using namespace cl;


kernel void worker()
{
    static_assert(numeric_limits<int>::max() == 2147483647, "<int>::max returns incorrect value");
    static_assert(numeric_limits<int>::min() == (-2147483647-1), "<int>::min returns incorrect value");

    static_assert(numeric_limits<int>::is_signed, "int should be signed");
    static_assert(numeric_limits<int2>::is_signed, "int2 should be signed");
    
    static_assert(!numeric_limits<uint>::is_signed, "uint should be unsigned");
    static_assert(!numeric_limits<uint2>::is_signed, "uint2 should be unsigned");

    static_assert(numeric_limits<char>::is_signed, "char should be signed");
    static_assert(numeric_limits<char2>::is_signed, "char2 should be signed");

    static_assert(!numeric_limits<uchar>::is_signed, "uchar should be unsigned");
    static_assert(!numeric_limits<uchar2>::is_signed, "uchar2 should be unsigned");

    static_assert(numeric_limits<short>::is_signed, "short should be signed");
    static_assert(numeric_limits<short2>::is_signed, "short2 should be signed");

    static_assert(!numeric_limits<ushort>::is_signed, "ushort should be unsigned");
    static_assert(!numeric_limits<ushort2>::is_signed, "ushort2 should be unsigned");

    static_assert(numeric_limits<long>::is_signed, "long should be signed");
    static_assert(numeric_limits<long2>::is_signed, "long2 should be signed");

    static_assert(!numeric_limits<ulong>::is_signed, "ulong should be unsigned");
    static_assert(!numeric_limits<ulong2>::is_signed, "ulong2 should be unsigned");
    
    static_assert(numeric_limits<bool>::is_scalar == false, "Bool is nor scalar or a vector");
    static_assert(numeric_limits<bool>::is_vector == false, "Bool is nor scalar or a vector");

    static_assert(numeric_limits<int>::is_scalar == true,   "<int> should return is_scalar = true");
    static_assert(numeric_limits<int>::is_vector == false,  "<int> should return is_vector = false");
    
    static_assert(numeric_limits<int2>::is_scalar == false,   "<int2> should return is_scalar = false");
    static_assert(numeric_limits<int2>::is_vector == true,  "<int2> should return is_vector = true");

    numeric_limits<int>::min();
    numeric_limits<int>::max();
    numeric_limits<int>::lowest();
    numeric_limits<char>::min();
    numeric_limits<char>::max();
    numeric_limits<char>::lowest();
    numeric_limits<short>::min();
    numeric_limits<short>::max();
    numeric_limits<short>::lowest();
    numeric_limits<long>::min();
    numeric_limits<long>::max();
    numeric_limits<long>::lowest();
    numeric_limits<uint>::min();
    numeric_limits<uint>::max();
    numeric_limits<uint>::lowest();
    numeric_limits<uchar>::min();
    numeric_limits<uchar>::max();
    numeric_limits<uchar>::lowest();
    numeric_limits<ushort>::min();
    numeric_limits<ushort>::max();
    numeric_limits<ushort>::lowest();
    numeric_limits<ulong>::min();
    numeric_limits<ulong>::max();
    numeric_limits<ulong>::lowest();
    numeric_limits<int4>::min();
    numeric_limits<int4>::max();
    numeric_limits<int4>::lowest();
    numeric_limits<char4>::min();
    numeric_limits<char4>::max();
    numeric_limits<char4>::lowest();
    numeric_limits<short4>::min();
    numeric_limits<short4>::max();
    numeric_limits<short4>::lowest();
    numeric_limits<long4>::min();
    numeric_limits<long4>::max();
    numeric_limits<long4>::lowest();
    numeric_limits<uint4>::min();
    numeric_limits<uint4>::max();
    numeric_limits<uint4>::lowest();
    numeric_limits<uchar4>::min();
    numeric_limits<uchar4>::max();
    numeric_limits<uchar4>::lowest();
    numeric_limits<ushort4>::min();
    numeric_limits<ushort4>::max();
    numeric_limits<ushort4>::lowest();
    numeric_limits<ulong4>::min();
    numeric_limits<ulong4>::max();
    numeric_limits<ulong4>::lowest();

    static_assert(numeric_limits<uint>::min() == 0,     "<uint>::min should equal 0");
    static_assert(numeric_limits<uchar>::min() == 0,    "<uchar>::min should equal 0");
    static_assert(numeric_limits<ulong>::min() == 0,    "<ulong>::min should equal 0");
    static_assert(numeric_limits<ushort>::min() == 0,   "<ushort>::min should equal 0");
}
