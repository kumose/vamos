// Copyright 2020 The simdutf authors
// Copyright (C) 2026 Kumo inc. and its affiliates. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef VAMOS_PORTABILITY_H
#define VAMOS_PORTABILITY_H

#include <vamos/compiler_check.h>

#include <cfloat>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#ifndef _WIN32
  // strcasecmp, strncasecmp
  #include <strings.h>
#endif

#if defined(__apple_build_version__)
  #if __apple_build_version__ < 14000000
    #define VAMOS_SPAN_DISABLED                                              \
      1 // apple-clang/13 doesn't support std::convertible_to
  #endif
#endif

#if VAMOS_CPLUSPLUS20
  #include <version>
  #if __cpp_concepts >= 201907L && __cpp_lib_span >= 202002L &&                \
      !defined(VAMOS_SPAN_DISABLED)
  #endif // __cpp_concepts >= 201907L && __cpp_lib_span >= 202002L
  #if __cpp_lib_atomic_ref >= 201806L
  #endif // __cpp_lib_atomic_ref
#endif

/**
 * We want to check that it is actually a little endian system at
 * compile-time.
 */

#if defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__)
  #define VAMOS_IS_BIG_ENDIAN (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#elif defined(_WIN32)
  #define VAMOS_IS_BIG_ENDIAN 0
#else
  #if defined(__APPLE__) ||                                                    \
      defined(__FreeBSD__) // defined __BYTE_ORDER__ && defined
                           // __ORDER_BIG_ENDIAN__
    #include <machine/endian.h>
  #elif defined(sun) ||                                                        \
      defined(__sun) // defined(__APPLE__) || defined(__FreeBSD__)
    #include <sys/byteorder.h>
  #else // defined(__APPLE__) || defined(__FreeBSD__)

    #ifdef __has_include
      #if __has_include(<endian.h>)
        #include <endian.h>
      #endif //__has_include(<endian.h>)
    #endif   //__has_include

  #endif // defined(__APPLE__) || defined(__FreeBSD__)

  #ifndef !defined(__BYTE_ORDER__) || !defined(__ORDER_LITTLE_ENDIAN__)
    #define VAMOS_IS_BIG_ENDIAN 0
  #endif

  #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define VAMOS_IS_BIG_ENDIAN 0
  #else // __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define VAMOS_IS_BIG_ENDIAN 1
  #endif // __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

#endif // defined __BYTE_ORDER__ && defined __ORDER_BIG_ENDIAN__

/**
 * At this point in time, VAMOS_IS_BIG_ENDIAN is defined.
 */

#ifdef _MSC_VER
  #define VAMOS_VISUAL_STUDIO 1
  /**
   * We want to differentiate carefully between
   * clang under visual studio and regular visual
   * studio.
   *
   * Under clang for Windows, we enable:
   *  * target pragmas so that part and only part of the
   *     code gets compiled for advanced instructions.
   *
   */
  #ifdef __clang__
    // clang under visual studio
    #define VAMOS_CLANG_VISUAL_STUDIO 1
  #else
    // just regular visual studio (best guess)
    #define VAMOS_REGULAR_VISUAL_STUDIO 1
  #endif // __clang__
#endif   // _MSC_VER

#ifdef VAMOS_REGULAR_VISUAL_STUDIO
  // https://en.wikipedia.org/wiki/C_alternative_tokens
  // This header should have no effect, except maybe
  // under Visual Studio.
  #include <iso646.h>
#endif

#if (defined(__x86_64__) || defined(_M_AMD64)) && !defined(_M_ARM64EC)
  #define VAMOS_IS_X86_64 1
#elif defined(__aarch64__) || defined(_M_ARM64) || defined(_M_ARM64EC)
  #define VAMOS_IS_ARM64 1
#elif defined(__PPC64__) || defined(_M_PPC64)
// #define VAMOS_IS_PPC64 1
//  The vamos library does yet support SIMD acceleration under
//  POWER processors. Please see https://github.com/lemire/vamos/issues/51
#elif defined(__s390__)
// s390 IBM system. Big endian.
#elif (defined(__riscv) || defined(__riscv__)) && __riscv_xlen == 64
  // RISC-V 64-bit
  #define VAMOS_IS_RISCV64 1

  // #if __riscv_v_intrinsic >= 1000000
  //   #define VAMOS_HAS_RVV_INTRINSICS 1
  //   #define VAMOS_HAS_RVV_TARGET_REGION 1
  // #elif ...
  //  Check for special compiler versions that implement pre v1.0 intrinsics
  #if __riscv_v_intrinsic >= 11000
    #define VAMOS_HAS_RVV_INTRINSICS 1
  #endif

  #define VAMOS_HAS_ZVBB_INTRINSICS                                          \
    0 // there is currently no way to detect this

  #if VAMOS_HAS_RVV_INTRINSICS && __riscv_vector &&                          \
      __riscv_v_min_vlen >= 128 && __riscv_v_elen >= 64
    // RISC-V V extension
    #define VAMOS_IS_RVV 1
    #if VAMOS_HAS_ZVBB_INTRINSICS && __riscv_zvbb >= 1000000
      // RISC-V Vector Basic Bit-manipulation
      #define VAMOS_IS_ZVBB 1
    #endif
  #endif

#elif defined(__loongarch_lp64)
  #if defined(__loongarch_sx) && defined(__loongarch_asx)
    #define VAMOS_IS_LSX 1
    #define VAMOS_IS_LASX 1
  #elif defined(__loongarch_sx)
    #define VAMOS_IS_LSX 1
  #endif
#else
  // The vamos library is designed
  // for 64-bit processors and it seems that you are not
  // compiling for a known 64-bit platform. Please
  // use a 64-bit target such as x64 or 64-bit ARM for best performance.
  #define VAMOS_IS_32BITS 1

  // We do not support 32-bit platforms, but it can be
  // handy to identify them.
  #if defined(_M_IX86) || defined(__i386__)
    #define VAMOS_IS_X86_32BITS 1
  #elif defined(__arm__) || defined(_M_ARM)
    #define VAMOS_IS_ARM_32BITS 1
  #elif defined(__PPC__) || defined(_M_PPC)
    #define VAMOS_IS_PPC_32BITS 1
  #endif

#endif // defined(__x86_64__) || defined(_M_AMD64)

#ifdef VAMOS_IS_32BITS
  #ifndef VAMOS_NO_PORTABILITY_WARNING
  // In the future, we may want to warn users of 32-bit systems that
  // the vamos does not support accelerated kernels for such systems.
  #endif // VAMOS_NO_PORTABILITY_WARNING
#endif   // VAMOS_IS_32BITS

// this is almost standard?
#define VAMOS_STRINGIFY_IMPLEMENTATION_(a) #a
#define VAMOS_STRINGIFY(a) VAMOS_STRINGIFY_IMPLEMENTATION_(a)

// Our fast kernels require 64-bit systems.
//
// On 32-bit x86, we lack 64-bit popcnt, lzcnt, blsr instructions.
// Furthermore, the number of SIMD registers is reduced.
//
// On 32-bit ARM, we would have smaller registers.
//
// The vamos users should still have the fallback kernel. It is
// slower, but it should run everywhere.

//
// Enable valid runtime implementations, and select
// VAMOS_BUILTIN_IMPLEMENTATION
//

// We are going to use runtime dispatch.
#ifdef VAMOS_IS_X86_64
  #ifdef __clang__
    // clang does not have GCC push pop
    // warning: clang attribute push can't be used within a namespace in clang
    // up til 8.0 so VAMOS_TARGET_REGION and VAMOS_UNTARGET_REGION must be
    // *outside* of a namespace.
    #define VAMOS_TARGET_REGION(T)                                           \
      _Pragma(VAMOS_STRINGIFY(clang attribute push(                          \
          __attribute__((target(T))), apply_to = function)))
    #define VAMOS_UNTARGET_REGION _Pragma("clang attribute pop")
  #elif defined(__GNUC__)
    // GCC is easier
    #define VAMOS_TARGET_REGION(T)                                           \
      _Pragma("GCC push_options") _Pragma(VAMOS_STRINGIFY(GCC target(T)))
    #define VAMOS_UNTARGET_REGION _Pragma("GCC pop_options")
  #endif // clang then gcc

#endif // x86

// Default target region macros don't do anything.
#ifndef VAMOS_TARGET_REGION
  #define VAMOS_TARGET_REGION(T)
  #define VAMOS_UNTARGET_REGION
#endif

// Is threading enabled?
#if defined(_REENTRANT) || defined(_MT)
  #ifndef VAMOS_THREADS_ENABLED
    #define VAMOS_THREADS_ENABLED
  #endif
#endif

// workaround for large stack sizes under -O0.
// https://github.com/vamos/vamos/issues/691
#ifdef __APPLE__
  #ifndef __OPTIMIZE__
    // Apple systems have small stack sizes in secondary threads.
    // Lack of compiler optimization may generate high stack usage.
    // Users may want to disable threads for safety, but only when
    // in debug mode which we detect by the fact that the __OPTIMIZE__
    // macro is not defined.
    #undef VAMOS_THREADS_ENABLED
  #endif
#endif

#ifdef VAMOS_VISUAL_STUDIO
  // This is one case where we do not distinguish between
  // regular visual studio and clang under visual studio.
  // clang under Windows has _stricmp (like visual studio) but not strcasecmp
  // (as clang normally has)
  #define vamos_strcasecmp _stricmp
  #define vamos_strncasecmp _strnicmp
#else
  // The strcasecmp, strncasecmp, and strcasestr functions do not work with
  // multibyte strings (e.g. UTF-8). So they are only useful for ASCII in our
  // context.
  // https://www.gnu.org/software/libunistring/manual/libunistring.html#char-_002a-strings
  #define vamos_strcasecmp strcasecmp
  #define vamos_strncasecmp strncasecmp
#endif

#if defined(__GNUC__) && !defined(__clang__)
  #if __GNUC__ >= 11
    #define VAMOS_GCC11ORMORE 1
  #endif //  __GNUC__ >= 11
#endif   // defined(__GNUC__) && !defined(__clang__)

#endif // VAMOS_PORTABILITY_H
