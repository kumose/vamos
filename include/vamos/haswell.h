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
