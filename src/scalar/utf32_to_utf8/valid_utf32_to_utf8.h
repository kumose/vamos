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
#ifndef VAMOS_VALID_UTF32_TO_UTF8_H
#define VAMOS_VALID_UTF32_TO_UTF8_H

namespace vamos {
namespace scalar {
namespace {
namespace utf32_to_utf8 {

#if VAMOS_IMPLEMENTATION_FALLBACK || VAMOS_IMPLEMENTATION_PPC64
// only used by the fallback and POWER kernel
inline size_t convert_valid(const char32_t *buf, size_t len,
                            char *utf8_output) {
  const uint32_t *data = reinterpret_cast<const uint32_t *>(buf);
  size_t pos = 0;
  char *start{utf8_output};
  while (pos < len) {
    // try to convert the next block of 2 ASCII characters
    if (pos + 2 <=
        len) { // if it is safe to read 8 more bytes, check that they are ascii
      uint64_t v;
      ::memcpy(&v, data + pos, sizeof(uint64_t));
      if ((v & 0xFFFFFF80FFFFFF80) == 0) {
        *utf8_output++ = char(buf[pos]);
        *utf8_output++ = char(buf[pos + 1]);
        pos += 2;
        continue;
      }
    }
    uint32_t word = data[pos];
    if ((word & 0xFFFFFF80) == 0) {
      // will generate one UTF-8 bytes
      *utf8_output++ = char(word);
      pos++;
    } else if ((word & 0xFFFFF800) == 0) {
      // will generate two UTF-8 bytes
      // we have 0b110XXXXX 0b10XXXXXX
      *utf8_output++ = char((word >> 6) | 0b11000000);
      *utf8_output++ = char((word & 0b111111) | 0b10000000);
      pos++;
    } else if ((word & 0xFFFF0000) == 0) {
      // will generate three UTF-8 bytes
      // we have 0b1110XXXX 0b10XXXXXX 0b10XXXXXX
      *utf8_output++ = char((word >> 12) | 0b11100000);
      *utf8_output++ = char(((word >> 6) & 0b111111) | 0b10000000);
      *utf8_output++ = char((word & 0b111111) | 0b10000000);
      pos++;
    } else {
      // will generate four UTF-8 bytes
      // we have 0b11110XXX 0b10XXXXXX 0b10XXXXXX 0b10XXXXXX
      *utf8_output++ = char((word >> 18) | 0b11110000);
      *utf8_output++ = char(((word >> 12) & 0b111111) | 0b10000000);
      *utf8_output++ = char(((word >> 6) & 0b111111) | 0b10000000);
      *utf8_output++ = char((word & 0b111111) | 0b10000000);
      pos++;
    }
  }
  return utf8_output - start;
}
#endif // VAMOS_IMPLEMENTATION_FALLBACK || VAMOS_IMPLEMENTATION_PPC64

} // namespace utf32_to_utf8
} // unnamed namespace
} // namespace scalar
} // namespace vamos

#endif
