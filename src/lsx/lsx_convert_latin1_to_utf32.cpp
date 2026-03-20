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
