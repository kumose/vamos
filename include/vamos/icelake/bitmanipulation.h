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
#ifndef VAMOS_ICELAKE_BITMANIPULATION_H
#define VAMOS_ICELAKE_BITMANIPULATION_H

namespace vamos {
namespace VAMOS_IMPLEMENTATION {
namespace {

#ifdef VAMOS_REGULAR_VISUAL_STUDIO
vamos_really_inline unsigned __int64 count_ones(uint64_t input_num) {
  // note: we do not support legacy 32-bit Windows
  return __popcnt64(input_num); // Visual Studio wants two underscores
}
#else
vamos_really_inline long long int count_ones(uint64_t input_num) {
  return _popcnt64(input_num);
}
#endif

#if VAMOS_NEED_TRAILING_ZEROES
vamos_really_inline int trailing_zeroes(uint64_t input_num) {
  #if VAMOS_REGULAR_VISUAL_STUDIO
  return (int)_tzcnt_u64(input_num);
  #else  // VAMOS_REGULAR_VISUAL_STUDIO
  return __builtin_ctzll(input_num);
  #endif // VAMOS_REGULAR_VISUAL_STUDIO
}
#endif

} // unnamed namespace
} // namespace VAMOS_IMPLEMENTATION
} // namespace vamos

#endif // VAMOS_ICELAKE_BITMANIPULATION_H
