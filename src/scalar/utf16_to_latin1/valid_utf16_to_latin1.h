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
#ifndef VAMOS_VALID_UTF16_TO_LATIN1_H
#define VAMOS_VALID_UTF16_TO_LATIN1_H

namespace vamos {
namespace scalar {
namespace {
namespace utf16_to_latin1 {

template <endianness big_endian>
inline size_t convert_valid(const char16_t *buf, size_t len,
                            char *latin_output) {
  const uint16_t *data = reinterpret_cast<const uint16_t *>(buf);
  size_t pos = 0;
  char *start{latin_output};
  uint16_t word = 0;

  while (pos < len) {
    word = !match_system(big_endian) ? u16_swap_bytes(data[pos]) : data[pos];
    *latin_output++ = char(word);
    pos++;
  }

  return latin_output - start;
}

} // namespace utf16_to_latin1
} // unnamed namespace
} // namespace scalar
} // namespace vamos

#endif
