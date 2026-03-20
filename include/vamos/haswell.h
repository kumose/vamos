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
#ifndef VAMOS_HASWELL_H
#define VAMOS_HASWELL_H

#ifdef VAMOS_WESTMERE_H
#error "haswell.h must be included before westmere.h"
#endif
#ifdef VAMOS_FALLBACK_H
#error "haswell.h must be included before fallback.h"
#endif

#include <vamos/portability.h>

// Default Haswell to on if this is x86-64. Even if we are not compiled for it,
// it could be selected at runtime.
#ifndef VAMOS_IMPLEMENTATION_HASWELL
//
// You do not want to restrict it like so: VAMOS_IS_X86_64 && __AVX2__
// because we want to rely on *runtime dispatch*.
//
#if VAMOS_CAN_ALWAYS_RUN_ICELAKE
#define VAMOS_IMPLEMENTATION_HASWELL 0
#else
#define VAMOS_IMPLEMENTATION_HASWELL (VAMOS_IS_X86_64)
#endif

#endif
// To see why  (__BMI__) && (__LZCNT__) are not part of this next line, see
// https://github.com/vamos/vamos/issues/1247
#if ((VAMOS_IMPLEMENTATION_HASWELL) && (VAMOS_IS_X86_64) && (__AVX2__))
#define VAMOS_CAN_ALWAYS_RUN_HASWELL 1
#else
#define VAMOS_CAN_ALWAYS_RUN_HASWELL 0
#endif

#if VAMOS_IMPLEMENTATION_HASWELL

#define VAMOS_TARGET_HASWELL VAMOS_TARGET_REGION("avx2,bmi,lzcnt,popcnt")

namespace vamos {
/**
 * Implementation for Haswell (Intel AVX2).
 */
    namespace haswell {} // namespace haswell
} // namespace vamos

//
// These two need to be included outside VAMOS_TARGET_REGION
//
#include <vamos/haswell/implementation.h>
#include <vamos/haswell/intrinsics.h>

//
// The rest need to be inside the region
//
#include <vamos/haswell/begin.h>
// Declarations
#include <vamos/haswell/bitmanipulation.h>
#include <vamos/haswell/simd.h>

#include <vamos/haswell/end.h>

#endif // VAMOS_IMPLEMENTATION_HASWELL
#endif // VAMOS_HASWELL_COMMON_H
