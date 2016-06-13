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

#define Region true

/// \brief Set of macros used to define builtin swizzles
///
#if Region | Predefined_swizzles

/// \brief emits four channel swizzle using given channels and enumerable for channel numbers
#define EMIT4(C0,C1,C2,C3) \
    __ALWAYS_INLINE auto C0##C1##C2##C3()       { return cl::swizzle<static_cast<size_t>(channel::C0), static_cast<size_t>(channel::C1), static_cast<size_t>(channel::C2), static_cast<size_t>(channel::C3)>(static_cast<CRTP&>(*this)); } \
    __ALWAYS_INLINE auto C0##C1##C2##C3() const { return cl::swizzle<static_cast<size_t>(channel::C0), static_cast<size_t>(channel::C1), static_cast<size_t>(channel::C2), static_cast<size_t>(channel::C3)>(static_cast<CRTP const&>(*this)); }

/// \brief emits three channel swizzle using given channels and enumerable for channel numbers
#define EMIT3(C0,C1,C2) \
    __ALWAYS_INLINE auto C0##C1##C2()       { return cl::swizzle<static_cast<size_t>(channel::C0), static_cast<size_t>(channel::C1), static_cast<size_t>(channel::C2)>(static_cast<CRTP&>(*this)); } \
    __ALWAYS_INLINE auto C0##C1##C2() const { return cl::swizzle<static_cast<size_t>(channel::C0), static_cast<size_t>(channel::C1), static_cast<size_t>(channel::C2)>(static_cast<CRTP const&>(*this)); }

/// \brief emits two channel swizzle using given channels and enumerable for channel numbers
#define EMIT2(C0,C1) \
    __ALWAYS_INLINE auto C0##C1()       { return cl::swizzle<static_cast<size_t>(channel::C0), static_cast<size_t>(channel::C1)>(static_cast<CRTP&>(*this)); } \
    __ALWAYS_INLINE auto C0##C1() const { return cl::swizzle<static_cast<size_t>(channel::C0), static_cast<size_t>(channel::C1)>(static_cast<CRTP const&>(*this)); }

/// \brief emits one channel swizzle using given channels and enumerable for channel numbers
#define EMIT1(C0) \
    __ALWAYS_INLINE auto C0()       { return cl::swizzle<static_cast<size_t>(channel::C0)>(static_cast<CRTP&>(*this)); } \
    __ALWAYS_INLINE auto C0() const { return cl::swizzle<static_cast<size_t>(channel::C0)>(static_cast<CRTP const&>(*this)); }

/// Macros are called in a tree like pattern starting from COMB_RPT4LVL1 down to COMB_RPT4LVL4 generating:
/// 4 swizzles of length 1
/// 16 swizzles of length 2
/// 64 swizzles of length 3
/// 256 swizzles of length 4
/// This macros are used to generate vector methods that resemble builtin vector swizzles eg.
/// vector_swizzle<0,1,2,3> rgba( );
#if Region | Combinations_of_four

/// \brief emits one three channel combination with repetitions of swizzles and four four element channel combinations with repetitions
///
/// takes four channels C0 to C3 and sequence S0,S1,S2
/// to build swizzle S0,S1,S2 and four swizzles prefixed with S0,S1,S2 ending with channels from C0 to C3
#define COMB_RPT4LVL4(C0,C1,C2,C3,S0,S1,S2) \
    EMIT3(S0,S1,S2) \
    EMIT4(S0,S1,S2,C0) \
    EMIT4(S0,S1,S2,C1) \
    EMIT4(S0,S1,S2,C2) \
    EMIT4(S0,S1,S2,C3)

/// \brief emits one two channel combination with repetitions of swizzles and four three element sequences of swizzles
///
/// takes four channels C0 to C3 and sequence S0,S1
/// to build swizzle S0,S1 and invokes COMB_RPT4LVL4 four times with sequences prefixed with S0,S1 ending with channels from C0 to C3
#define COMB_RPT4LVL3(C0,C1,C2,C3,S0,S1) \
    EMIT2(S0,S1) \
    COMB_RPT4LVL4(C0,C1,C2,C3,S0,S1,C0) \
    COMB_RPT4LVL4(C0,C1,C2,C3,S0,S1,C1) \
    COMB_RPT4LVL4(C0,C1,C2,C3,S0,S1,C2) \
    COMB_RPT4LVL4(C0,C1,C2,C3,S0,S1,C3)

/// \brief emits one two one channel combination with repetitions of swizzles and four two element sequences of swizzles
///
/// takes four channels C0 to C3 and sequence S0
/// to build swizzle S0 and invokes COMB_RPT4LVL3 four times with sequences prefixed with S0 ending with channels from C0 to C3
#define COMB_RPT4LVL2(C0,C1,C2,C3,S0) \
    EMIT1(S0) \
    COMB_RPT4LVL3(C0,C1,C2,C3,S0,C0) \
    COMB_RPT4LVL3(C0,C1,C2,C3,S0,C1) \
    COMB_RPT4LVL3(C0,C1,C2,C3,S0,C2) \
    COMB_RPT4LVL3(C0,C1,C2,C3,S0,C3)

/// \brief emits four one element sequences of swizzles
///
/// takes four channels C0 to C3
/// calling COMB_RPT4LVL2 four times with prefix sequences C0,C1,C2 and C3
#define COMB_RPT4LVL1(C0,C1,C2,C3) \
    COMB_RPT4LVL2(C0,C1,C2,C3,C0) \
    COMB_RPT4LVL2(C0,C1,C2,C3,C1) \
    COMB_RPT4LVL2(C0,C1,C2,C3,C2) \
    COMB_RPT4LVL2(C0,C1,C2,C3,C3)

#endif // Combinations_of_four

/// Macros are called in a tree like pattern starting from COMB_RPT3LVL1 down to COMB_RPT3LVL3 generating:
/// 3 swizzles of length 1
/// 9 swizzles of length 2
/// 27 swizzles of length 3
/// This macros are used to generate vector methods that resemble builtin vector swizzles eg.
/// vector_swizzle<0,1,2> rgb( );
#if Region | Combinations_of_three

/// \brief emits one two channel combination with repetitions of swizzles and three three element channel combinations with repetitions
///
/// takes three channels C0 to C2 and sequence S0,S1,S2
/// to build swizzle S0,S1 and three swizzles prefixed with S0,S1 ending with channels from C0 to C2
#define COMB_RPT3LVL3(C0,C1,C2,S0,S1) \
    EMIT2(S0,S1) \
    EMIT3(S0,S1,C0) \
    EMIT3(S0,S1,C1) \
    EMIT3(S0,S1,C2)

/// \brief emits one one channel combination with repetitions of swizzles and three two element sequences of swizzles
///
/// takes three channels C0 to C2 and sequence S0
/// to build swizzle S0 and invokes COMB_RPT3LVL3 three times with sequences prefixed with S0 ending with channels from C0 to C2
#define COMB_RPT3LVL2(C0,C1,C2,S0) \
    EMIT1(S0) \
    COMB_RPT3LVL3(C0,C1,C2,S0,C0) \
    COMB_RPT3LVL3(C0,C1,C2,S0,C1) \
    COMB_RPT3LVL3(C0,C1,C2,S0,C2)

/// \brief emits three one element sequences of swizzles
///
/// takes three channels C0 to C2
/// invokes COMB_RPT3LVL2 three times with prefix sequences C0, C1 and C2
#define COMB_RPT3LVL1(C0,C1,C2) \
    COMB_RPT3LVL2(C0,C1,C2,C0) \
    COMB_RPT3LVL2(C0,C1,C2,C1) \
    COMB_RPT3LVL2(C0,C1,C2,C2)

#endif // Combinations_of_three

#if Region | Combinations_of_two
/// \brief emits all two and one element swizzles
///
/// takes two channels C0 and C1
#define COMB_RPT2LVL1(C0,C1) \
    EMIT1(C0) \
    EMIT1(C1) \
    EMIT2(C0,C0) \
    EMIT2(C0,C1) \
    EMIT2(C1,C0) \
    EMIT2(C1,C1)

#endif // Combinations_of_two

#endif // Predefined swizzles

#undef Region
