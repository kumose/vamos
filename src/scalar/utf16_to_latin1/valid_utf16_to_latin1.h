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
