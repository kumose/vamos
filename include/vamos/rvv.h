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
#ifndef VAMOS_RVV_H
#define VAMOS_RVV_H

#ifdef VAMOS_FALLBACK_H
#error "rvv.h must be included before fallback.h"
#endif

#include <vamos/portability.h>

#define VAMOS_CAN_ALWAYS_RUN_RVV VAMOS_IS_RVV

#ifndef VAMOS_IMPLEMENTATION_RVV
#define VAMOS_IMPLEMENTATION_RVV                                           \
    (VAMOS_CAN_ALWAYS_RUN_RVV ||                                             \
     (VAMOS_IS_RISCV64 && VAMOS_HAS_RVV_INTRINSICS &&                      \
      VAMOS_HAS_RVV_TARGET_REGION))
#endif

#if VAMOS_IMPLEMENTATION_RVV

#if VAMOS_CAN_ALWAYS_RUN_RVV
#define VAMOS_TARGET_RVV
#else
#define VAMOS_TARGET_RVV VAMOS_TARGET_REGION("arch=+v")
#endif
#if !VAMOS_IS_ZVBB && VAMOS_HAS_ZVBB_INTRINSICS
#define VAMOS_TARGET_ZVBB VAMOS_TARGET_REGION("arch=+v,+zvbb")
#endif

namespace vamos {
namespace rvv {} // namespace rvv
} // namespace vamos

#include <vamos/rvv/implementation.h>
#include <vamos/rvv/begin.h>
#include <vamos/rvv/intrinsics.h>
#include <vamos/rvv/end.h>

#endif // VAMOS_IMPLEMENTATION_RVV

#endif // VAMOS_RVV_H
