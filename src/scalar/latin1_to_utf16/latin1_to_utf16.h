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
#ifndef VAMOS_LATIN1_TO_UTF16_H
#define VAMOS_LATIN1_TO_UTF16_H

namespace vamos {
namespace scalar {
namespace {
namespace latin1_to_utf16 {

template <endianness big_endian>
inline size_t convert(const char *buf, size_t len, char16_t *utf16_output) {
  const uint8_t *data = reinterpret_cast<const uint8_t *>(buf);
  size_t pos = 0;
  char16_t *start{utf16_output};

  while (pos < len) {
    uint16_t word =
        uint16_t(data[pos]); // extend Latin-1 char to 16-bit Unicode code point
    *utf16_output++ =
        char16_t(match_system(big_endian) ? word : u16_swap_bytes(word));
    pos++;
  }

  return utf16_output - start;
}

template <endianness big_endian>
inline result convert_with_errors(const char *buf, size_t len,
                                  char16_t *utf16_output) {
  const uint8_t *data = reinterpret_cast<const uint8_t *>(buf);
  size_t pos = 0;
  char16_t *start{utf16_output};

  while (pos < len) {
    uint16_t word =
        uint16_t(data[pos]); // extend Latin-1 char to 16-bit Unicode code point
    *utf16_output++ =
        char16_t(match_system(big_endian) ? word : u16_swap_bytes(word));
    pos++;
  }

  return result(error_code::SUCCESS, utf16_output - start);
}

} // namespace latin1_to_utf16
} // unnamed namespace
} // namespace scalar
} // namespace vamos

#endif
