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
// file included directly

bool validate_ascii(const char *buf, size_t len) {
  const char *end = buf + len;
  const __m512i ascii = _mm512_set1_epi8((uint8_t)0x80);
  __m512i running_or = _mm512_setzero_si512();
  for (; end - buf >= 64; buf += 64) {
    const __m512i utf8 = _mm512_loadu_si512((const __m512i *)buf);
    running_or = _mm512_ternarylogic_epi32(running_or, utf8, ascii,
                                           0xf8); // running_or | (utf8 & ascii)
  }
  if (buf < end) {
    const __m512i utf8 = _mm512_maskz_loadu_epi8(
        (uint64_t(1) << (end - buf)) - 1, (const __m512i *)buf);
    running_or = _mm512_ternarylogic_epi32(running_or, utf8, ascii,
                                           0xf8); // running_or | (utf8 & ascii)
  }
  return (_mm512_test_epi8_mask(running_or, running_or) == 0);
}
