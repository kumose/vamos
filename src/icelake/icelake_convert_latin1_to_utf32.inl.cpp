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
void avx512_convert_latin1_to_utf32(const char *buf, size_t len,
                                    char32_t *utf32_output) {
  while (len >= 16) {
    // Load 16 Latin1 characters into a 128-bit register
    __m128i in = _mm_loadu_si128((__m128i *)buf);

    // Zero extend each set of 8 Latin1 characters to 16 32-bit integers using
    // vpmovzxbd
    __m512i out = _mm512_cvtepu8_epi32(in);

    // Store the results back to memory
    _mm512_storeu_si512((__m512i *)utf32_output, out);

    len -= 16;
    buf += 16;
    utf32_output += 16;
  }

  __mmask16 mask = __mmask16((1 << len) - 1);
  __m128i in = _mm_maskz_loadu_epi8(mask, buf);
  __m512i out = _mm512_cvtepu8_epi32(in);
  _mm512_mask_storeu_epi32((__m512i *)utf32_output, mask, out);
}
