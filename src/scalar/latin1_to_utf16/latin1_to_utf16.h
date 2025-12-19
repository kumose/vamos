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
