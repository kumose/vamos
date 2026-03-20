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
#ifndef VAMOS_LASX_H
#define VAMOS_LASX_H

#ifdef VAMOS_FALLBACK_H
#error "lasx.h must be included before fallback.h"
#endif

#include <vamos/portability.h>

#ifndef VAMOS_IMPLEMENTATION_LASX
#define VAMOS_IMPLEMENTATION_LASX (VAMOS_IS_LASX)
#endif
#if VAMOS_IMPLEMENTATION_LASX && VAMOS_IS_LASX
#define VAMOS_CAN_ALWAYS_RUN_LASX 1
#else
#define VAMOS_CAN_ALWAYS_RUN_LASX 0
#endif

#define VAMOS_CAN_ALWAYS_RUN_FALLBACK (VAMOS_IMPLEMENTATION_FALLBACK)

#include <vamos/internal/isadetection.h>

#if VAMOS_IMPLEMENTATION_LASX

namespace vamos {
/**
 * Implementation for LoongArch ASX.
 */
namespace lasx {} // namespace lasx
} // namespace vamos

#include <vamos/lasx/implementation.h>

#include <vamos/lasx/begin.h>

  // Declarations
#include <vamos/lasx/intrinsics.h>
#include <vamos/lasx/bitmanipulation.h>
#include <vamos/lasx/simd.h>

#include <vamos/lasx/end.h>

#endif // VAMOS_IMPLEMENTATION_LASX

#endif // VAMOS_LASX_H
