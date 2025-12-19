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
#ifndef VAMOS_H
#define VAMOS_H
#include <cstring>

#include <vamos/compiler_check.h>
#include <vamos/common_defs.h>
#include <vamos/encoding_types.h>
#include <vamos/error.h>

VAMOS_PUSH_DISABLE_WARNINGS
VAMOS_DISABLE_UNDESIRED_WARNINGS

// Public API
#include <vamos/vamos_version.h>
#include <vamos/implementation.h>

// Implementation-internal files (must be included before the implementations
// themselves, to keep amalgamation working--otherwise, the first time a file is
// included, it might be put inside the #ifdef
// VAMOS_IMPLEMENTATION_ARM64/FALLBACK/etc., which means the other
// implementations can't compile unless that implementation is turned on).
#include <vamos/internal/isadetection.h>

VAMOS_POP_DISABLE_WARNINGS

#endif // VAMOS_H
