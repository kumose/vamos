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
