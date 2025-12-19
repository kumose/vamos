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
template <endianness big_endian>
simd8<uint8_t> utf16_gather_high_bytes(const simd16<uint16_t> in0,
                                       const simd16<uint16_t> in1) {
  if (big_endian) {
    const auto mask = simd16<uint16_t>(0x00ff);
    const auto t0 = in0 & mask;
    const auto t1 = in1 & mask;

    return simd16<uint16_t>::pack(t0, t1);
  } else {
    return simd8<uint8_t>(__lsx_vssrlni_bu_h(in1.value, in0.value, 8));
  }
}
