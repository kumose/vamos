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
std::pair<const char *, char16_t *>
lsx_convert_latin1_to_utf16le(const char *buf, size_t len,
                              char16_t *utf16_output) {
  const char *end = buf + len;

  __m128i zero = __lsx_vldi(0);
  while (end - buf >= 16) {
    __m128i in8 = __lsx_vld(reinterpret_cast<const uint8_t *>(buf), 0);

    __m128i inlow = __lsx_vilvl_b(zero, in8);
    __m128i inhigh = __lsx_vilvh_b(zero, in8);
    __lsx_vst(inlow, reinterpret_cast<uint16_t *>(utf16_output), 0);
    __lsx_vst(inhigh, reinterpret_cast<uint16_t *>(utf16_output), 16);

    utf16_output += 16;
    buf += 16;
  }

  return std::make_pair(buf, utf16_output);
}

std::pair<const char *, char16_t *>
lsx_convert_latin1_to_utf16be(const char *buf, size_t len,
                              char16_t *utf16_output) {
  const char *end = buf + len;
  __m128i zero = __lsx_vldi(0);
  while (end - buf >= 16) {
    __m128i in8 = __lsx_vld(reinterpret_cast<const uint8_t *>(buf), 0);

    __m128i inlow = __lsx_vilvl_b(in8, zero);
    __m128i inhigh = __lsx_vilvh_b(in8, zero);
    __lsx_vst(inlow, reinterpret_cast<uint16_t *>(utf16_output), 0);
    __lsx_vst(inhigh, reinterpret_cast<uint16_t *>(utf16_output), 16);
    utf16_output += 16;
    buf += 16;
  }

  return std::make_pair(buf, utf16_output);
}
