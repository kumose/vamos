// Copyright (C) 2024 Kumo inc.
// Author: Jeff.li lijippy@163.com
// All rights reserved.
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
#ifndef VAMOS_ICELAKE_H
#define VAMOS_ICELAKE_H

#include <vamos/portability.h>

#ifdef __has_include
// How do we detect that a compiler supports vbmi2?
// For sure if the following header is found, we are ok?
#if __has_include(<avx512vbmi2intrin.h>)
#define VAMOS_COMPILER_SUPPORTS_VBMI2 1
#endif
#endif

#ifdef _MSC_VER
#if _MSC_VER >= 1930
// Visual Studio 2022 and up support VBMI2 under x64 even if the header
// avx512vbmi2intrin.h is not found.
// Visual Studio 2019 technically supports VBMI2, but the implementation
// might be unreliable. Search for visualstudio2019icelakeissue in our
// tests.
#define VAMOS_COMPILER_SUPPORTS_VBMI2 1
#endif
#endif

// We allow icelake on x64 as long as the compiler is known to support VBMI2.
#ifndef VAMOS_IMPLEMENTATION_ICELAKE
#define VAMOS_IMPLEMENTATION_ICELAKE                                       \
    ((VAMOS_IS_X86_64) && (VAMOS_COMPILER_SUPPORTS_VBMI2))
#endif

// To see why  (__BMI__) && (__LZCNT__) are not part of this next line, see
// https://github.com/vamos/vamos/issues/1247
#if ((VAMOS_IMPLEMENTATION_ICELAKE) && (VAMOS_IS_X86_64) && (__AVX2__) && \
     (VAMOS_HAS_AVX512F && VAMOS_HAS_AVX512DQ && VAMOS_HAS_AVX512VL && \
      VAMOS_HAS_AVX512VBMI2) && \
     (!VAMOS_IS_32BITS))
#define VAMOS_CAN_ALWAYS_RUN_ICELAKE 1
#else
#define VAMOS_CAN_ALWAYS_RUN_ICELAKE 0
#endif

#if VAMOS_IMPLEMENTATION_ICELAKE
#if VAMOS_CAN_ALWAYS_RUN_ICELAKE
#define VAMOS_TARGET_ICELAKE
#else
#define VAMOS_TARGET_ICELAKE                                             \
      VAMOS_TARGET_REGION(                                                   \
          "avx512f,avx512dq,avx512cd,avx512bw,avx512vbmi,avx512vbmi2,"         \
          "avx512vl,avx2,bmi,bmi2,pclmul,lzcnt,popcnt,avx512vpopcntdq")
#endif

namespace vamos {
    namespace icelake {} // namespace icelake
} // namespace vamos

//
// These two need to be included outside VAMOS_TARGET_REGION
//
#include <vamos/icelake/intrinsics.h>
#include <vamos/icelake/implementation.h>

//
// The rest need to be inside the region
//
#include <vamos/icelake/begin.h>
// Declarations
#include <vamos/icelake/bitmanipulation.h>
#include <vamos/icelake/end.h>

#endif // VAMOS_IMPLEMENTATION_ICELAKE
#endif // VAMOS_ICELAKE_H
