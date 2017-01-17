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

#include <__ocl_config.h>
#include <__ocl_atomic_enum.h>
#include <__ocl_atomic_traits.h>

namespace cl
{

namespace __spirv
{

extern auto OpAtomicFlagTestAndSet(int* Pointer, memory_scope Scope, memory_order Semantics) -> bool;
extern auto OpAtomicFlagClear(int* Pointer, memory_scope Scope, memory_order Semantics) -> void;

extern auto OpMemoryBarrier(memory_scope Scope, memory_order Semantics) -> void;

extern auto OpAtomicLoad(int* Pointer, memory_scope Scope, memory_order Semantics) -> int;
extern auto OpAtomicLoad(unsigned int* Pointer, memory_scope Scope, memory_order Semantics) -> unsigned int;
extern auto OpAtomicLoad(float* Pointer, memory_scope Scope, memory_order Semantics) -> float;

extern auto OpAtomicStore(int* Pointer, memory_scope Scope, memory_order Semantics, int Value) -> void;
extern auto OpAtomicStore(unsigned int* Pointer, memory_scope Scope, memory_order Semantics, unsigned int Value) -> void;
extern auto OpAtomicStore(float* Pointer, memory_scope Scope, memory_order Semantics, float Value) -> void;

extern auto OpAtomicExchange(int* Pointer, memory_scope Scope, memory_order Semantics, int Value) -> int;
extern auto OpAtomicExchange(unsigned int* Pointer, memory_scope Scope, memory_order Semantics, unsigned int Value) -> unsigned int;
extern auto OpAtomicExchange(float* Pointer, memory_scope Scope, memory_order Semantics, float Value) -> float;

extern auto OpAtomicCompareExchange(int* Pointer, memory_scope Scope, memory_order Equal, memory_order Unequal, int Value, int Comparator) -> int;
extern auto OpAtomicCompareExchange(unsigned int* Pointer, memory_scope Scope, memory_order Equal, memory_order Unequal, unsigned int Value, unsigned int Comparator) -> unsigned int;

extern auto OpAtomicCompareExchangeWeak(int* Pointer, memory_scope Scope, memory_order Equal, memory_order Unequal, int Value, int Comparator) -> int;
extern auto OpAtomicCompareExchangeWeak(unsigned int* Pointer, memory_scope Scope, memory_order Equal, memory_order Unequal, unsigned int Value, unsigned int Comparator) -> unsigned int;

extern auto OpAtomicIAdd(int* Pointer, memory_scope Scope, memory_order Semantics, int Value) -> int;
extern auto OpAtomicIAdd(unsigned int* Pointer, memory_scope Scope, memory_order Semantics, unsigned int Value) -> unsigned int;

extern auto OpAtomicISub(int* Pointer, memory_scope Scope, memory_order Semantics, int Value) -> int;
extern auto OpAtomicISub(unsigned int* Pointer, memory_scope Scope, memory_order Semantics, unsigned int Value) -> unsigned int;

extern auto OpAtomicSMin(int* Pointer, memory_scope Scope, memory_order Semantics, int Value) -> int;
extern auto OpAtomicUMin(unsigned int* Pointer, memory_scope Scope, memory_order Semantics, unsigned int Value) -> unsigned int;

extern auto OpAtomicSMax(int* Pointer, memory_scope Scope, memory_order Semantics, int Value) -> int;
extern auto OpAtomicUMax(unsigned int* Pointer, memory_scope Scope, memory_order Semantics, unsigned int Value) -> unsigned int;

extern auto OpAtomicAnd(int* Pointer, memory_scope Scope, memory_order Semantics, int Value) -> int;
extern auto OpAtomicAnd(unsigned int* Pointer, memory_scope Scope, memory_order Semantics, unsigned int Value) -> unsigned int;

extern auto OpAtomicOr(int* Pointer, memory_scope Scope, memory_order Semantics, int Value) -> int;
extern auto OpAtomicOr(unsigned int* Pointer, memory_scope Scope, memory_order Semantics, unsigned int Value) -> unsigned int;

extern auto OpAtomicXor(int* Pointer, memory_scope Scope, memory_order Semantics, int Value) -> int;
extern auto OpAtomicXor(unsigned int* Pointer, memory_scope Scope, memory_order Semantics, unsigned int Value) -> unsigned int;

#if (__INTPTR_WIDTH__ == 32) || (defined(cl_khr_int64_base_atomics) && defined(cl_khr_int64_extended_atomics))
extern auto OpAtomicLoad(intptr_t* Pointer, memory_scope Scope, memory_order Semantics) -> intptr_t;
extern auto OpAtomicLoad(uintptr_t* Pointer, memory_scope Scope, memory_order Semantics) -> uintptr_t;
extern auto OpAtomicLoad(size_t* Pointer, memory_scope Scope, memory_order Semantics) -> size_t;
extern auto OpAtomicLoad(ptrdiff_t* Pointer, memory_scope Scope, memory_order Semantics) -> ptrdiff_t;

extern auto OpAtomicStore(intptr_t* Pointer, memory_scope Scope, memory_order Semantics, intptr_t Value) -> void;
extern auto OpAtomicStore(uintptr_t* Pointer, memory_scope Scope, memory_order Semantics, uintptr_t Value) -> void;
extern auto OpAtomicStore(size_t* Pointer, memory_scope Scope, memory_order Semantics, size_t Value) -> void;
extern auto OpAtomicStore(ptrdiff_t* Pointer, memory_scope Scope, memory_order Semantics, ptrdiff_t Value) -> void;

extern auto OpAtomicExchange(intptr_t* Pointer, memory_scope Scope, memory_order Semantics, intptr_t Value) -> intptr_t;
extern auto OpAtomicExchange(uintptr_t* Pointer, memory_scope Scope, memory_order Semantics, uintptr_t Value) -> uintptr_t;
extern auto OpAtomicExchange(size_t* Pointer, memory_scope Scope, memory_order Semantics, size_t Value) -> size_t;
extern auto OpAtomicExchange(ptrdiff_t* Pointer, memory_scope Scope, memory_order Semantics, ptrdiff_t Value) -> ptrdiff_t;

extern auto OpAtomicCompareExchange(intptr_t* Pointer, memory_scope Scope, memory_order Equal, memory_order Unequal, intptr_t Value, intptr_t Comparator) -> intptr_t;
extern auto OpAtomicCompareExchange(uintptr_t* Pointer, memory_scope Scope, memory_order Equal, memory_order Unequal, uintptr_t Value, uintptr_t Comparator) -> uintptr_t;
extern auto OpAtomicCompareExchange(size_t* Pointer, memory_scope Scope, memory_order Equal, memory_order Unequal, size_t Value, size_t Comparator) -> size_t;
extern auto OpAtomicCompareExchange(ptrdiff_t* Pointer, memory_scope Scope, memory_order Equal, memory_order Unequal, ptrdiff_t Value, ptrdiff_t Comparator) -> ptrdiff_t;

extern auto OpAtomicCompareExchangeWeak(intptr_t* Pointer, memory_scope Scope, memory_order Equal, memory_order Unequal, intptr_t Value, intptr_t Comparator) -> intptr_t;
extern auto OpAtomicCompareExchangeWeak(uintptr_t* Pointer, memory_scope Scope, memory_order Equal, memory_order Unequal, uintptr_t Value, uintptr_t Comparator) -> uintptr_t;
extern auto OpAtomicCompareExchangeWeak(size_t* Pointer, memory_scope Scope, memory_order Equal, memory_order Unequal, size_t Value, size_t Comparator) -> size_t;
extern auto OpAtomicCompareExchangeWeak(ptrdiff_t* Pointer, memory_scope Scope, memory_order Equal, memory_order Unequal, ptrdiff_t Value, ptrdiff_t Comparator) -> ptrdiff_t;

extern auto OpAtomicIAdd(intptr_t* Pointer, memory_scope Scope, memory_order Semantics, intptr_t Value) -> intptr_t;
extern auto OpAtomicIAdd(uintptr_t* Pointer, memory_scope Scope, memory_order Semantics, uintptr_t Value) -> uintptr_t;
extern auto OpAtomicIAdd(size_t* Pointer, memory_scope Scope, memory_order Semantics, size_t Value) -> size_t;
extern auto OpAtomicIAdd(ptrdiff_t* Pointer, memory_scope Scope, memory_order Semantics, ptrdiff_t Value) -> ptrdiff_t;

extern auto OpAtomicISub(intptr_t* Pointer, memory_scope Scope, memory_order Semantics, intptr_t Value) -> intptr_t;
extern auto OpAtomicISub(uintptr_t* Pointer, memory_scope Scope, memory_order Semantics, uintptr_t Value) -> uintptr_t;
extern auto OpAtomicISub(size_t* Pointer, memory_scope Scope, memory_order Semantics, size_t Value) -> size_t;
extern auto OpAtomicISub(ptrdiff_t* Pointer, memory_scope Scope, memory_order Semantics, ptrdiff_t Value) -> ptrdiff_t;

extern auto OpAtomicSMin(intptr_t* Pointer, memory_scope Scope, memory_order Semantics, intptr_t Value) -> intptr_t;
extern auto OpAtomicUMin(uintptr_t* Pointer, memory_scope Scope, memory_order Semantics, uintptr_t Value) -> uintptr_t;
extern auto OpAtomicUMin(size_t* Pointer, memory_scope Scope, memory_order Semantics, size_t Value) -> size_t;
extern auto OpAtomicSMin(ptrdiff_t* Pointer, memory_scope Scope, memory_order Semantics, ptrdiff_t Value) -> ptrdiff_t;

extern auto OpAtomicSMax(intptr_t* Pointer, memory_scope Scope, memory_order Semantics, intptr_t Value) -> intptr_t;
extern auto OpAtomicUMax(uintptr_t* Pointer, memory_scope Scope, memory_order Semantics, uintptr_t Value) -> uintptr_t;
extern auto OpAtomicUMax(size_t* Pointer, memory_scope Scope, memory_order Semantics, size_t Value) -> size_t;
extern auto OpAtomicSMax(ptrdiff_t* Pointer, memory_scope Scope, memory_order Semantics, ptrdiff_t Value) -> ptrdiff_t;

extern auto OpAtomicAnd(intptr_t* Pointer, memory_scope Scope, memory_order Semantics, intptr_t Value) -> intptr_t;
extern auto OpAtomicAnd(uintptr_t* Pointer, memory_scope Scope, memory_order Semantics, uintptr_t Value) -> uintptr_t;
extern auto OpAtomicAnd(size_t* Pointer, memory_scope Scope, memory_order Semantics, size_t Value) -> size_t;
extern auto OpAtomicAnd(ptrdiff_t* Pointer, memory_scope Scope, memory_order Semantics, ptrdiff_t Value) -> ptrdiff_t;

extern auto OpAtomicOr(intptr_t* Pointer, memory_scope Scope, memory_order Semantics, intptr_t Value) -> intptr_t;
extern auto OpAtomicOr(uintptr_t* Pointer, memory_scope Scope, memory_order Semantics, uintptr_t Value) -> uintptr_t;
extern auto OpAtomicOr(size_t* Pointer, memory_scope Scope, memory_order Semantics, size_t Value) -> size_t;
extern auto OpAtomicOr(ptrdiff_t* Pointer, memory_scope Scope, memory_order Semantics, ptrdiff_t Value) -> ptrdiff_t;

extern auto OpAtomicXor(intptr_t* Pointer, memory_scope Scope, memory_order Semantics, intptr_t Value) -> intptr_t;
extern auto OpAtomicXor(uintptr_t* Pointer, memory_scope Scope, memory_order Semantics, uintptr_t Value) -> uintptr_t;
extern auto OpAtomicXor(size_t* Pointer, memory_scope Scope, memory_order Semantics, size_t Value) -> size_t;
extern auto OpAtomicXor(ptrdiff_t* Pointer, memory_scope Scope, memory_order Semantics, ptrdiff_t Value) -> ptrdiff_t;
#endif

#if defined(cl_khr_int64_base_atomics) && defined(cl_khr_int64_extended_atomics)
extern auto OpAtomicLoad(long* Pointer, memory_scope Scope, memory_order Semantics) -> long;
extern auto OpAtomicLoad(unsigned long* Pointer, memory_scope Scope, memory_order Semantics) -> unsigned long;

extern auto OpAtomicStore(long* Pointer, memory_scope Scope, memory_order Semantics, long Value) -> void;
extern auto OpAtomicStore(unsigned long* Pointer, memory_scope Scope, memory_order Semantics, unsigned long Value) -> void;

extern auto OpAtomicExchange(long* Pointer, memory_scope Scope, memory_order Semantics, long Value) -> long;
extern auto OpAtomicExchange(unsigned long* Pointer, memory_scope Scope, memory_order Semantics, unsigned long Value) -> unsigned long;

extern auto OpAtomicCompareExchange(long* Pointer, memory_scope Scope, memory_order Equal, memory_order Unequal, long Value, long Comparator) -> long;
extern auto OpAtomicCompareExchange(unsigned long* Pointer, memory_scope Scope, memory_order Equal, memory_order Unequal, unsigned long Value, unsigned long Comparator) -> unsigned long;

extern auto OpAtomicCompareExchangeWeak(long* Pointer, memory_scope Scope, memory_order Equal, memory_order Unequal, long Value, long Comparator) -> long;
extern auto OpAtomicCompareExchangeWeak(unsigned long* Pointer, memory_scope Scope, memory_order Equal, memory_order Unequal, unsigned long Value, unsigned long Comparator) -> unsigned long;

extern auto OpAtomicIAdd(long* Pointer, memory_scope Scope, memory_order Semantics, long Value) -> long;
extern auto OpAtomicIAdd(unsigned long* Pointer, memory_scope Scope, memory_order Semantics, unsigned long Value) -> unsigned long;

extern auto OpAtomicISub(long* Pointer, memory_scope Scope, memory_order Semantics, long Value) -> long;
extern auto OpAtomicISub(unsigned long* Pointer, memory_scope Scope, memory_order Semantics, unsigned long Value) -> unsigned long;

extern auto OpAtomicSMin(long* Pointer, memory_scope Scope, memory_order Semantics, long Value) -> long;
extern auto OpAtomicUMin(unsigned long* Pointer, memory_scope Scope, memory_order Semantics, unsigned long Value) -> unsigned long;

extern auto OpAtomicSMax(long* Pointer, memory_scope Scope, memory_order Semantics, long Value) -> long;
extern auto OpAtomicUMax(unsigned long* Pointer, memory_scope Scope, memory_order Semantics, unsigned long Value) -> unsigned long;

extern auto OpAtomicAnd(long* Pointer, memory_scope Scope, memory_order Semantics, long Value) -> long;
extern auto OpAtomicAnd(unsigned long* Pointer, memory_scope Scope, memory_order Semantics, unsigned long Value) -> unsigned long;

extern auto OpAtomicOr(long* Pointer, memory_scope Scope, memory_order Semantics, long Value) -> long;
extern auto OpAtomicOr(unsigned long* Pointer, memory_scope Scope, memory_order Semantics, unsigned long Value) -> unsigned long;

extern auto OpAtomicXor(long* Pointer, memory_scope Scope, memory_order Semantics, long Value) -> long;
extern auto OpAtomicXor(unsigned long* Pointer, memory_scope Scope, memory_order Semantics, unsigned long Value) -> unsigned long;

#if defined(cl_khr_fp64)
extern auto OpAtomicLoad(double* Pointer, memory_scope Scope, memory_order Semantics) -> double;
extern auto OpAtomicStore(double* Pointer, memory_scope Scope, memory_order Semantics, double Value) -> void;
extern auto OpAtomicExchange(double* Pointer, memory_scope Scope, memory_order Semantics, double Value) -> double;
#endif

#endif

}

}
