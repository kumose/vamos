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
