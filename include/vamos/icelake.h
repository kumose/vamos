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
