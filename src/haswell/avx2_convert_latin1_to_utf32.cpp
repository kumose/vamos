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
avx2_convert_latin1_to_utf32(const char *buf, size_t len,
                             char32_t *utf32_output) {
  size_t rounded_len = ((len | 7) ^ 7); // Round down to nearest multiple of 8

  for (size_t i = 0; i < rounded_len; i += 8) {
    // Load 8 Latin1 characters into a 64-bit register
    __m128i in = _mm_loadl_epi64((__m128i *)&buf[i]);

    // Zero extend each set of 8 Latin1 characters to 8 32-bit integers using
    // vpmovzxbd
    __m256i out = _mm256_cvtepu8_epi32(in);

    // Store the results back to memory
    _mm256_storeu_si256((__m256i *)&utf32_output[i], out);
  }

  // return pointers pointing to where we left off
  return std::make_pair(buf + rounded_len, utf32_output + rounded_len);
}
