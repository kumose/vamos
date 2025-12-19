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
