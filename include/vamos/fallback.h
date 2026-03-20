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
#ifndef VAMOS_FALLBACK_H
#define VAMOS_FALLBACK_H

#include <vamos/portability.h>

// Note that fallback.h is always imported last.

// Default Fallback to on unless a builtin implementation has already been
// selected.
#ifndef VAMOS_IMPLEMENTATION_FALLBACK
#if VAMOS_CAN_ALWAYS_RUN_ARM64 || VAMOS_CAN_ALWAYS_RUN_ICELAKE || \
      VAMOS_CAN_ALWAYS_RUN_HASWELL || VAMOS_CAN_ALWAYS_RUN_WESTMERE || \
      VAMOS_CAN_ALWAYS_RUN_PPC64 || VAMOS_CAN_ALWAYS_RUN_RVV || \
      VAMOS_CAN_ALWAYS_RUN_LSX || VAMOS_CAN_ALWAYS_RUN_LASX
#define VAMOS_IMPLEMENTATION_FALLBACK 0
#else
#define VAMOS_IMPLEMENTATION_FALLBACK 1
#endif
#endif

#define VAMOS_CAN_ALWAYS_RUN_FALLBACK (VAMOS_IMPLEMENTATION_FALLBACK)

#if VAMOS_IMPLEMENTATION_FALLBACK

namespace vamos {
/**
 * Fallback implementation (runs on any machine).
 */
    namespace fallback {} // namespace fallback
} // namespace vamos

#include <vamos/fallback/implementation.h>

#include <vamos/fallback/begin.h>

// Declarations
#include <vamos/fallback/bitmanipulation.h>

#include <vamos/fallback/end.h>

#endif // VAMOS_IMPLEMENTATION_FALLBACK
#endif // VAMOS_FALLBACK_H
