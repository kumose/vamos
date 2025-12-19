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
#ifndef VAMOS_PPC64_H
#define VAMOS_PPC64_H

#ifdef VAMOS_FALLBACK_H
#error "ppc64.h must be included before fallback.h"
#endif

#include <vamos/portability.h>

#ifndef VAMOS_IMPLEMENTATION_PPC64
#define VAMOS_IMPLEMENTATION_PPC64 (VAMOS_IS_PPC64)
#endif
#define VAMOS_CAN_ALWAYS_RUN_PPC64                                           \
  VAMOS_IMPLEMENTATION_PPC64 &&VAMOS_IS_PPC64

#include <vamos/internal/isadetection.h>

#if VAMOS_IMPLEMENTATION_PPC64

namespace vamos {
/**
 * Implementation for ALTIVEC (PPC64).
 */
namespace ppc64 {} // namespace ppc64
} // namespace vamos

#include <vamos/ppc64/implementation.h>

#include <vamos/ppc64/begin.h>

  // Declarations
#include <vamos/ppc64/intrinsics.h>
#include <vamos/ppc64/bitmanipulation.h>
#include <vamos/ppc64/simd.h>

#include <vamos/ppc64/end.h>

#endif // VAMOS_IMPLEMENTATION_PPC64

#endif // VAMOS_PPC64_H
