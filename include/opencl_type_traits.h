#pragma OPENCL EXTENSION __cl_clang_function_pointers : enable
#pragma OPENCL EXTENSION __cl_clang_variadic_functions : enable
#include <type_traits>
#pragma OPENCL EXTENSION __cl_clang_function_pointers : disable
#pragma OPENCL EXTENSION __cl_clang_variadic_functions : disable

template<typename T>
struct is_signed : public std::false_type {};

template<>
struct is_signed<int2> : public std::true_type {};
template<>
struct is_signed<int3> : public std::true_type {};
template<>
struct is_signed<int4> : public std::true_type {};
template<>
struct is_signed<int8> : public std::true_type {};
template<>
struct is_signed<int16> : public std::true_type {};

template<>
struct is_signed<char2> : public std::true_type {};
template<>
struct is_signed<char3> : public std::true_type {};
template<>
struct is_signed<char4> : public std::true_type {};
template<>
struct is_signed<char8> : public std::true_type {};
template<>
struct is_signed<char16> : public std::true_type {};

template<>
struct is_signed<short2> : public std::true_type {};
template<>
struct is_signed<short3> : public std::true_type {};
template<>
struct is_signed<short4> : public std::true_type {};
template<>
struct is_signed<short8> : public std::true_type {};
template<>
struct is_signed<short16> : public std::true_type {};

template<>
struct is_signed<long2> : public std::true_type {};
template<>
struct is_signed<long3> : public std::true_type {};
template<>
struct is_signed<long4> : public std::true_type {};
template<>
struct is_signed<long8> : public std::true_type {};
template<>
struct is_signed<long16> : public std::true_type {};

template<>
struct is_signed<float2> : public std::true_type {};
template<>
struct is_signed<float3> : public std::true_type {};
template<>
struct is_signed<float4> : public std::true_type {};
template<>
struct is_signed<float8> : public std::true_type {};
template<>
struct is_signed<float16> : public std::true_type {};

template<>
struct is_signed<double2> : public std::true_type {};
template<>
struct is_signed<double3> : public std::true_type {};
template<>
struct is_signed<double4> : public std::true_type {};
template<>
struct is_signed<double8> : public std::true_type {};
template<>
struct is_signed<double16> : public std::true_type {};


template<typename T>
struct is_unsigned : public std::false_type {};

template<>
struct is_unsigned<uint2> : public std::true_type {};
template<>
struct is_unsigned<uint3> : public std::true_type {};
template<>
struct is_unsigned<uint4> : public std::true_type {};
template<>
struct is_unsigned<uint8> : public std::true_type {};
template<>
struct is_unsigned<uint16> : public std::true_type {};

template<>
struct is_unsigned<uchar2> : public std::true_type {};
template<>
struct is_unsigned<uchar3> : public std::true_type {};
template<>
struct is_unsigned<uchar4> : public std::true_type {};
template<>
struct is_unsigned<uchar8> : public std::true_type {};
template<>
struct is_unsigned<uchar16> : public std::true_type {};

template<>
struct is_unsigned<ushort2> : public std::true_type {};
template<>
struct is_unsigned<ushort3> : public std::true_type {};
template<>
struct is_unsigned<ushort4> : public std::true_type {};
template<>
struct is_unsigned<ushort8> : public std::true_type {};
template<>
struct is_unsigned<ushort16> : public std::true_type {};

template<>
struct is_unsigned<ulong2> : public std::true_type {};
template<>
struct is_unsigned<ulong3> : public std::true_type {};
template<>
struct is_unsigned<ulong4> : public std::true_type {};
template<>
struct is_unsigned<ulong8> : public std::true_type {};
template<>
struct is_unsigned<ulong16> : public std::true_type {};


template<typename T>
struct make_signed {typedef T type;};

template<>
struct make_signed<uint2> {typedef int2 type;};
template<>
struct make_signed<uint3> {typedef int3 type;};
template<>
struct make_signed<uint4> {typedef int4 type;};
template<>
struct make_signed<uint8> {typedef int8 type;};
template<>
struct make_signed<uint16> {typedef int16 type;};

template<>
struct make_signed<uchar2> {typedef char2 type;};
template<>
struct make_signed<uchar3> {typedef char3 type;};
template<>
struct make_signed<uchar4> {typedef char4 type;};
template<>
struct make_signed<uchar8> {typedef char8 type;};
template<>
struct make_signed<uchar16> {typedef char16 type;};

template<>
struct make_signed<ushort2> {typedef short2 type;};
template<>
struct make_signed<ushort3> {typedef short3 type;};
template<>
struct make_signed<ushort4> {typedef short4 type;};
template<>
struct make_signed<ushort8> {typedef short8 type;};
template<>
struct make_signed<ushort16> {typedef short16 type;};

template<>
struct make_signed<ulong2> {typedef long2 type;};
template<>
struct make_signed<ulong3> {typedef long3 type;};
template<>
struct make_signed<ulong4> {typedef long4 type;};
template<>
struct make_signed<ulong8> {typedef long8 type;};
template<>
struct make_signed<ulong16> {typedef long16 type;};


template<typename T>
struct make_unsigned {typedef T type;};

template<>
struct make_unsigned<int2> {typedef uint2 type;};
template<>
struct make_unsigned<int3> {typedef uint3 type;};
template<>
struct make_unsigned<int4> {typedef uint4 type;};
template<>
struct make_unsigned<int8> {typedef uint8 type;};
template<>
struct make_unsigned<int16> {typedef uint16 type;};

template<>
struct make_unsigned<char2> {typedef uchar2 type;};
template<>
struct make_unsigned<char3> {typedef uchar3 type;};
template<>
struct make_unsigned<char4> {typedef uchar4 type;};
template<>
struct make_unsigned<char8> {typedef uchar8 type;};
template<>
struct make_unsigned<char16> {typedef uchar16 type;};

template<>
struct make_unsigned<short2> {typedef ushort2 type;};
template<>
struct make_unsigned<short3> {typedef ushort3 type;};
template<>
struct make_unsigned<short4> {typedef ushort4 type;};
template<>
struct make_unsigned<short8> {typedef ushort8 type;};
template<>
struct make_unsigned<short16> {typedef ushort16 type;};

template<>
struct make_unsigned<long2> {typedef ulong2 type;};
template<>
struct make_unsigned<long3> {typedef ulong3 type;};
template<>
struct make_unsigned<long4> {typedef ulong4 type;};
template<>
struct make_unsigned<long8> {typedef ulong8 type;};
template<>
struct make_unsigned<long16> {typedef ulong16 type;};
