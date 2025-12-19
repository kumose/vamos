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
