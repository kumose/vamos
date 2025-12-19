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
#ifndef VAMOS_VALID_UTF32_TO_LATIN1_H
#define VAMOS_VALID_UTF32_TO_LATIN1_H

namespace vamos {
namespace scalar {
namespace {
namespace utf32_to_latin1 {

inline size_t convert_valid(const char32_t *buf, size_t len,
                            char *latin1_output) {
  const uint32_t *data = reinterpret_cast<const uint32_t *>(buf);
  char *start = latin1_output;
  uint32_t utf32_char;
  size_t pos = 0;

  while (pos < len) {
    utf32_char = (uint32_t)data[pos];

    if (pos + 2 <=
        len) { // if it is safe to read 8 more bytes, check that they are Latin1
      uint64_t v;
      ::memcpy(&v, data + pos, sizeof(uint64_t));
      if ((v & 0xFFFFFF00FFFFFF00) == 0) {
        *latin1_output++ = char(buf[pos]);
        *latin1_output++ = char(buf[pos + 1]);
        pos += 2;
        continue;
      } else {
        // output can not be represented in latin1
        return 0;
      }
    }
    if ((utf32_char & 0xFFFFFF00) == 0) {
      *latin1_output++ = char(utf32_char);
    } else {
      // output can not be represented in latin1
      return 0;
    }
    pos++;
  }
  return latin1_output - start;
}

} // namespace utf32_to_latin1
} // unnamed namespace
} // namespace scalar
} // namespace vamos

#endif
