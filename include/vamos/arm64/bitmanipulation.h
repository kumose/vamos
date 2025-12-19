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
