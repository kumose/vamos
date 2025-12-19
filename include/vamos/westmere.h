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
#ifndef VAMOS_WESTMERE_H
#define VAMOS_WESTMERE_H

#ifdef VAMOS_FALLBACK_H
#error "westmere.h must be included before fallback.h"
#endif

#include <vamos/portability.h>

// Default Westmere to on if this is x86-64, unless we'll always select Haswell.
#ifndef VAMOS_IMPLEMENTATION_WESTMERE
//
// You do not want to set it to (VAMOS_IS_X86_64 &&
// !VAMOS_REQUIRES_HASWELL) because you want to rely on runtime dispatch!
//
#if VAMOS_CAN_ALWAYS_RUN_ICELAKE || VAMOS_CAN_ALWAYS_RUN_HASWELL
#define VAMOS_IMPLEMENTATION_WESTMERE 0
#else
#define VAMOS_IMPLEMENTATION_WESTMERE (VAMOS_IS_X86_64)
#endif

#endif

#if (VAMOS_IMPLEMENTATION_WESTMERE && VAMOS_IS_X86_64 && __SSE4_2__)
#define VAMOS_CAN_ALWAYS_RUN_WESTMERE 1
#else
#define VAMOS_CAN_ALWAYS_RUN_WESTMERE 0
#endif

#if VAMOS_IMPLEMENTATION_WESTMERE

#define VAMOS_TARGET_WESTMERE VAMOS_TARGET_REGION("sse4.2,popcnt")

namespace vamos {
/**
 * Implementation for Westmere (Intel SSE4.2).
 */
    namespace westmere {} // namespace westmere
} // namespace vamos

//
// These two need to be included outside VAMOS_TARGET_REGION
//
#include <vamos/westmere/implementation.h>
#include <vamos/westmere/intrinsics.h>

//
// The rest need to be inside the region
//
#include <vamos/westmere/begin.h>

// Declarations
#include <vamos/westmere/bitmanipulation.h>
#include <vamos/westmere/simd.h>

#include <vamos/westmere/end.h>

#endif // VAMOS_IMPLEMENTATION_WESTMERE
#endif // VAMOS_WESTMERE_COMMON_H
