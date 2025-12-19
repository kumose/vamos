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
std::pair<const char *, char32_t *>
lsx_convert_latin1_to_utf32(const char *buf, size_t len,
                            char32_t *utf32_output) {
  const char *end = buf + len;

  while (end - buf >= 16) {
    __m128i in8 = __lsx_vld(reinterpret_cast<const uint8_t *>(buf), 0);

    __m128i zero = __lsx_vldi(0);
    __m128i in16low = __lsx_vilvl_b(zero, in8);
    __m128i in16high = __lsx_vilvh_b(zero, in8);
    __m128i in32_0 = __lsx_vilvl_h(zero, in16low);
    __m128i in32_1 = __lsx_vilvh_h(zero, in16low);
    __m128i in32_2 = __lsx_vilvl_h(zero, in16high);
    __m128i in32_3 = __lsx_vilvh_h(zero, in16high);

    __lsx_vst(in32_0, reinterpret_cast<uint32_t *>(utf32_output), 0);
    __lsx_vst(in32_1, reinterpret_cast<uint32_t *>(utf32_output + 4), 0);
    __lsx_vst(in32_2, reinterpret_cast<uint32_t *>(utf32_output + 8), 0);
    __lsx_vst(in32_3, reinterpret_cast<uint32_t *>(utf32_output + 12), 0);

    utf32_output += 16;
    buf += 16;
  }

  return std::make_pair(buf, utf32_output);
}
