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
#define VAMOS_IMPLEMENTATION haswell

#if VAMOS_CAN_ALWAYS_RUN_HASWELL
// nothing needed.
#else
VAMOS_TARGET_HASWELL
#endif

#if VAMOS_GCC11ORMORE // workaround for
                        // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=105593
// clang-format off
VAMOS_DISABLE_GCC_WARNING(-Wmaybe-uninitialized)
// clang-format on
#endif // end of workaround
