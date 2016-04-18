//
// Copyright (c) 2015-2016 The Khronos Group Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and/or associated documentation files (the
// "Materials"), to deal in the Materials without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Materials, and to
// permit persons to whom the Materials are furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Materials.
//
// THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
//

#pragma once
#define REGION 1

/* Macro names and corresponding values defined by OpenCL */
/* Math constants for each floating-point precision       */


#if REGION | Integer_values
#define CHAR_BIT         8
#define SCHAR_MAX        127
#define SCHAR_MIN        (-127-1)
#define CHAR_MAX         SCHAR_MAX
#define CHAR_MIN         SCHAR_MIN
#define UCHAR_MAX        255
#define SHRT_MAX         32767
#define SHRT_MIN         (-32767-1)
#define USHRT_MAX        65535
#define INT_MAX          2147483647
#define INT_MIN          (-2147483647-1)
#define UINT_MAX         0xffffffffU
#define LONG_MAX         0x7fffffffffffffffL
#define LONG_MIN         (-0x7fffffffffffffffL-1)
#define ULONG_MAX        ((ulong) 0xFFFFFFFFFFFFFFFFULL)
#endif

#if REGION | Float_values
#define FLT_DIG          6
#define FLT_MANT_DIG     24
#define FLT_MAX_10_EXP   +38
#define FLT_MAX_EXP      +128
#define FLT_MIN_10_EXP   -37
#define FLT_MIN_EXP      -125
#define FLT_RADIX        2
#define FLT_MAX          0x1.fffffep127f
#define FLT_MIN          0x1.0p-126f
#define FLT_EPSILON      0x1.0p-23f
#define FLT_DENORM_MIN   1.4013e-045

#endif

#if REGION | Double_fp64_values
#ifdef cl_khr_fp64
#define DBL_DIG          15
#define DBL_MANT_DIG     53
#define DBL_MAX_10_EXP   +308
#define DBL_MAX_EXP      +1024
#define DBL_MIN_10_EXP   -307
#define DBL_MIN_EXP      -1021
#define DBL_RADIX        2
#define DBL_MAX          0x1.fffffffffffffp1023
#define DBL_MIN          0x1.0p-1022
#define DBL_EPSILON      0x1.0p-52
#define DBL_DENORM_MIN   4.94066e-324

#endif
#endif

#if REGION | Half_fp16_values
#ifdef cl_khr_fp16
#define HALF_DIG 		3
#define HALF_MANT_DIG	11
#define HALF_MAX_10_EXP +4
#define HALF_MAX_EXP	+16
#define HALF_MIN_10_EXP -4
#define HALF_MIN_EXP	-13
#define HALF_RADIX	    2
#define HALF_MAX		0x1.ffcp15h
#define HALF_MIN		0x1.0p-14h
#define HALF_EPSILON	0x1.0p-10h
#define HALF_DENORM_MIN 5.96046e-8

#endif
#endif

#undef REGION