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
#ifndef VAMOS_WESTMERE_BITMANIPULATION_H
#define VAMOS_WESTMERE_BITMANIPULATION_H

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
  unsigned long ret;
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

#endif // VAMOS_WESTMERE_BITMANIPULATION_H
