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
