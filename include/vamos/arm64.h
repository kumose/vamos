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
#ifndef VAMOS_ARM64_H
#define VAMOS_ARM64_H

#ifdef VAMOS_FALLBACK_H
#error "arm64.h must be included before fallback.h"
#endif

#include <vamos/portability.h>

#ifndef VAMOS_IMPLEMENTATION_ARM64
#define VAMOS_IMPLEMENTATION_ARM64 (VAMOS_IS_ARM64)
#endif
#if VAMOS_IMPLEMENTATION_ARM64 && VAMOS_IS_ARM64
#define VAMOS_CAN_ALWAYS_RUN_ARM64 1
#else
#define VAMOS_CAN_ALWAYS_RUN_ARM64 0
#endif

#include <vamos/internal/isadetection.h>

#if VAMOS_IMPLEMENTATION_ARM64

namespace vamos {
/**
 * Implementation for NEON (ARMv8).
 */
namespace arm64 {} // namespace arm64
} // namespace vamos

#include <vamos/arm64/implementation.h>

#include <vamos/arm64/begin.h>

  // Declarations
#include <vamos/arm64/intrinsics.h>
#include <vamos/arm64/bitmanipulation.h>
#include <vamos/arm64/simd.h>

#include <vamos/arm64/end.h>

#endif // VAMOS_IMPLEMENTATION_ARM64

#endif // VAMOS_ARM64_H
