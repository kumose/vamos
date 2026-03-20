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
#ifndef VAMOS_UTF32_TO_LATIN1_H
#define VAMOS_UTF32_TO_LATIN1_H

namespace vamos {
namespace scalar {
namespace {
namespace utf32_to_latin1 {

inline size_t convert(const char32_t *buf, size_t len, char *latin1_output) {
  const uint32_t *data = reinterpret_cast<const uint32_t *>(buf);
  char *start = latin1_output;
  uint32_t utf32_char;
  size_t pos = 0;
  uint32_t too_large = 0;

  while (pos < len) {
    utf32_char = (uint32_t)data[pos];
    too_large |= utf32_char;
    *latin1_output++ = (char)(utf32_char & 0xFF);
    pos++;
  }
  if ((too_large & 0xFFFFFF00) != 0) {
    return 0;
  }
  return latin1_output - start;
}

inline result convert_with_errors(const char32_t *buf, size_t len,
                                  char *latin1_output) {
  const uint32_t *data = reinterpret_cast<const uint32_t *>(buf);
  char *start{latin1_output};
  size_t pos = 0;
  while (pos < len) {
    if (pos + 2 <=
        len) { // if it is safe to read 8 more bytes, check that they are Latin1
      uint64_t v;
      ::memcpy(&v, data + pos, sizeof(uint64_t));
      if ((v & 0xFFFFFF00FFFFFF00) == 0) {
        *latin1_output++ = char(buf[pos]);
        *latin1_output++ = char(buf[pos + 1]);
        pos += 2;
        continue;
      }
    }
    uint32_t utf32_char = data[pos];
    if ((utf32_char & 0xFFFFFF00) ==
        0) { // Check if the character can be represented in Latin-1
      *latin1_output++ = (char)(utf32_char & 0xFF);
      pos++;
    } else {
      return result(error_code::TOO_LARGE, pos);
    };
  }
  return result(error_code::SUCCESS, latin1_output - start);
}

} // namespace utf32_to_latin1
} // unnamed namespace
} // namespace scalar
} // namespace vamos

#endif
