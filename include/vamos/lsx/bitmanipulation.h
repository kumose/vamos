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
#ifndef VAMOS_LSX_BITMANIPULATION_H
#define VAMOS_LSX_BITMANIPULATION_H

#include <vamos/vamos.h>
#include <limits>

namespace vamos {
namespace VAMOS_IMPLEMENTATION {
namespace {

vamos_really_inline int count_ones(uint64_t input_num) {
  return __lsx_vpickve2gr_w(__lsx_vpcnt_d(__lsx_vreplgr2vr_d(input_num)), 0);
}

#if VAMOS_NEED_TRAILING_ZEROES
vamos_really_inline int trailing_zeroes(uint64_t input_num) {
  return __builtin_ctzll(input_num);
}
#endif

} // unnamed namespace
} // namespace VAMOS_IMPLEMENTATION
} // namespace vamos

#endif // VAMOS_LSX_BITMANIPULATION_H
