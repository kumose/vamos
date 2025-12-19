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
