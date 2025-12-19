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
std::pair<const char16_t *, char *>
lsx_convert_utf16_to_latin1(const char16_t *buf, size_t len,
                            char *latin1_output) {
  const char16_t *end = buf + len;
  while (end - buf >= 16) {
    __m128i in = __lsx_vld(reinterpret_cast<const uint16_t *>(buf), 0);
    __m128i in1 = __lsx_vld(reinterpret_cast<const uint16_t *>(buf), 16);
    if (!match_system(big_endian)) {
      in = lsx_swap_bytes(in);
      in1 = lsx_swap_bytes(in1);
    }
    if (__lsx_bz_v(__lsx_vpickod_b(in1, in))) {
      // 1. pack the bytes
      __m128i latin1_packed = __lsx_vpickev_b(in1, in);
      // 2. store (8 bytes)
      __lsx_vst(latin1_packed, reinterpret_cast<uint8_t *>(latin1_output), 0);
      // 3. adjust pointers
      buf += 16;
      latin1_output += 16;
    } else {
      return std::make_pair(nullptr, reinterpret_cast<char *>(latin1_output));
    }
  } // while
  return std::make_pair(buf, latin1_output);
}

template <endianness big_endian>
std::pair<result, char *>
lsx_convert_utf16_to_latin1_with_errors(const char16_t *buf, size_t len,
                                        char *latin1_output) {
  const char16_t *start = buf;
  const char16_t *end = buf + len;
  while (end - buf >= 16) {
    __m128i in = __lsx_vld(reinterpret_cast<const uint16_t *>(buf), 0);
    __m128i in1 = __lsx_vld(reinterpret_cast<const uint16_t *>(buf), 16);
    if (!match_system(big_endian)) {
      in = lsx_swap_bytes(in);
      in1 = lsx_swap_bytes(in1);
    }
    if (__lsx_bz_v(__lsx_vpickod_b(in1, in))) {
      // 1. pack the bytes
      __m128i latin1_packed = __lsx_vpickev_b(in1, in);
      // 2. store (8 bytes)
      __lsx_vst(latin1_packed, reinterpret_cast<uint8_t *>(latin1_output), 0);
      // 3. adjust pointers
      buf += 16;
      latin1_output += 16;
    } else {
      // Let us do a scalar fallback.
      for (int k = 0; k < 16; k++) {
        uint16_t word =
            !match_system(big_endian) ? scalar::u16_swap_bytes(buf[k]) : buf[k];
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
