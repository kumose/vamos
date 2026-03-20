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
#ifndef VAMOS_ARM64_BITMANIPULATION_H
#define VAMOS_ARM64_BITMANIPULATION_H

namespace vamos {
namespace VAMOS_IMPLEMENTATION {
namespace {

/* result might be undefined when input_num is zero */
vamos_really_inline int count_ones(uint64_t input_num) {
  return vaddv_u8(vcnt_u8(vcreate_u8(input_num)));
}

#if VAMOS_NEED_TRAILING_ZEROES
vamos_really_inline int trailing_zeroes(uint64_t input_num) {
  #ifdef VAMOS_REGULAR_VISUAL_STUDIO
  unsigned long ret;
  // Search the mask data from least significant bit (LSB)
  // to the most significant bit (MSB) for a set bit (1).
  _BitScanForward64(&ret, input_num);
  return (int)ret;
  #else  // VAMOS_REGULAR_VISUAL_STUDIO
  return __builtin_ctzll(input_num);
  #endif // VAMOS_REGULAR_VISUAL_STUDIO
}
#endif

} // unnamed namespace
} // namespace VAMOS_IMPLEMENTATION
} // namespace vamos

#endif // VAMOS_ARM64_BITMANIPULATION_H
