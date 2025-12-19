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
std::pair<const char32_t *, char *>
lsx_convert_utf32_to_latin1(const char32_t *buf, size_t len,
                            char *latin1_output) {
  const char32_t *end = buf + len;
  const v16u8 shuf_mask = {0, 4, 8, 12, 16, 20, 24, 28, 0, 0, 0, 0, 0, 0, 0, 0};
  __m128i v_ff = __lsx_vrepli_w(0xFF);

  while (end - buf >= 16) {
    __m128i in1 = __lsx_vld(reinterpret_cast<const uint32_t *>(buf), 0);
    __m128i in2 = __lsx_vld(reinterpret_cast<const uint32_t *>(buf), 16);

    __m128i in12 = __lsx_vor_v(in1, in2);
    if (__lsx_bz_v(__lsx_vslt_wu(v_ff, in12))) {
      // 1. pack the bytes
      __m128i latin1_packed = __lsx_vshuf_b(in2, in1, (__m128i)shuf_mask);
      // 2. store (8 bytes)
      __lsx_vst(latin1_packed, reinterpret_cast<uint8_t *>(latin1_output), 0);
      // 3. adjust pointers
      buf += 8;
      latin1_output += 8;
    } else {
      return std::make_pair(nullptr, reinterpret_cast<char *>(latin1_output));
    }
  } // while
  return std::make_pair(buf, latin1_output);
}

std::pair<result, char *>
lsx_convert_utf32_to_latin1_with_errors(const char32_t *buf, size_t len,
                                        char *latin1_output) {
  const char32_t *start = buf;
  const char32_t *end = buf + len;

  const v16u8 shuf_mask = {0, 4, 8, 12, 16, 20, 24, 28, 0, 0, 0, 0, 0, 0, 0, 0};
  __m128i v_ff = __lsx_vrepli_w(0xFF);

  while (end - buf >= 16) {
    __m128i in1 = __lsx_vld(reinterpret_cast<const uint32_t *>(buf), 0);
    __m128i in2 = __lsx_vld(reinterpret_cast<const uint32_t *>(buf), 16);

    __m128i in12 = __lsx_vor_v(in1, in2);

    if (__lsx_bz_v(__lsx_vslt_wu(v_ff, in12))) {
      // 1. pack the bytes
      __m128i latin1_packed = __lsx_vshuf_b(in2, in1, (__m128i)shuf_mask);
      // 2. store (8 bytes)
      __lsx_vst(latin1_packed, reinterpret_cast<uint8_t *>(latin1_output), 0);
      // 3. adjust pointers
      buf += 8;
      latin1_output += 8;
    } else {
      // Let us do a scalar fallback.
      for (int k = 0; k < 8; k++) {
        uint32_t word = buf[k];
        if (word <= 0xff) {
          *latin1_output++ = char(word);
        } else {
          return std::make_pair(result(error_code::TOO_LARGE, buf - start + k),
                                latin1_output);
        }
      }
    }
  } // while
  return std::make_pair(result(error_code::SUCCESS, buf - start),
                        latin1_output);
}
