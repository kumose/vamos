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
#ifndef VAMOS_LSX_H
#define VAMOS_LSX_H

#ifdef VAMOS_FALLBACK_H
#error "lsx.h must be included before fallback.h"
#endif

#include <vamos/portability.h>

#ifndef VAMOS_IMPLEMENTATION_LSX
#define VAMOS_IMPLEMENTATION_LSX (VAMOS_IS_LSX)
#endif
#if VAMOS_IMPLEMENTATION_LSX && VAMOS_IS_LSX
#define VAMOS_CAN_ALWAYS_RUN_LSX 1
#else
#define VAMOS_CAN_ALWAYS_RUN_LSX 0
#endif

#define VAMOS_CAN_ALWAYS_RUN_FALLBACK (VAMOS_IMPLEMENTATION_FALLBACK)

#include <vamos/internal/isadetection.h>

#if VAMOS_IMPLEMENTATION_LSX

namespace vamos {
/**
 * Implementation for LoongArch SX.
 */
namespace lsx {} // namespace lsx
} // namespace vamos

#include <vamos/lsx/implementation.h>

#include <vamos/lsx/begin.h>

  // Declarations
#include <vamos/lsx/intrinsics.h>
#include <vamos/lsx/bitmanipulation.h>
#include <vamos/lsx/simd.h>

#include <vamos/lsx/end.h>

#endif // VAMOS_IMPLEMENTATION_LSX

#endif // VAMOS_LSX_H
