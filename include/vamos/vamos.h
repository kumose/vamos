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
