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
arm_convert_utf32_to_latin1(const char32_t *buf, size_t len,
                            char *latin1_output) {
  const char32_t *end = buf + len;
  while (end - buf >= 8) {
    uint32x4_t in1 = vld1q_u32(reinterpret_cast<const uint32_t *>(buf));
    uint32x4_t in2 = vld1q_u32(reinterpret_cast<const uint32_t *>(buf + 4));

    uint16x8_t utf16_packed = vcombine_u16(vqmovn_u32(in1), vqmovn_u32(in2));
    if (vmaxvq_u16(utf16_packed) <= 0xff) {
      // 1. pack the bytes
      uint8x8_t latin1_packed = vmovn_u16(utf16_packed);
      // 2. store (8 bytes)
      vst1_u8(reinterpret_cast<uint8_t *>(latin1_output), latin1_packed);
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
arm_convert_utf32_to_latin1_with_errors(const char32_t *buf, size_t len,
                                        char *latin1_output) {
  const char32_t *start = buf;
  const char32_t *end = buf + len;

  while (end - buf >= 8) {
    uint32x4_t in1 = vld1q_u32(reinterpret_cast<const uint32_t *>(buf));
    uint32x4_t in2 = vld1q_u32(reinterpret_cast<const uint32_t *>(buf + 4));

    uint16x8_t utf16_packed = vcombine_u16(vqmovn_u32(in1), vqmovn_u32(in2));

    if (vmaxvq_u16(utf16_packed) <= 0xff) {
      // 1. pack the bytes
      uint8x8_t latin1_packed = vmovn_u16(utf16_packed);
      // 2. store (8 bytes)
      vst1_u8(reinterpret_cast<uint8_t *>(latin1_output), latin1_packed);
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
