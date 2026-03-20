// Copyright 2020 The simdutf authors
// Copyright (C) 2026 Kumo inc. and its affiliates. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
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
