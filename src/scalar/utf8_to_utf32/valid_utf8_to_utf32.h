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
#ifndef VAMOS_VALID_UTF8_TO_UTF32_H
#define VAMOS_VALID_UTF8_TO_UTF32_H

namespace vamos {
namespace scalar {
namespace {
namespace utf8_to_utf32 {

inline size_t convert_valid(const char *buf, size_t len,
                            char32_t *utf32_output) {
  const uint8_t *data = reinterpret_cast<const uint8_t *>(buf);
  size_t pos = 0;
  char32_t *start{utf32_output};
  while (pos < len) {
    // try to convert the next block of 8 ASCII bytes
    if (pos + 8 <=
        len) { // if it is safe to read 8 more bytes, check that they are ascii
      uint64_t v;
      ::memcpy(&v, data + pos, sizeof(uint64_t));
      if ((v & 0x8080808080808080) == 0) {
        size_t final_pos = pos + 8;
        while (pos < final_pos) {
          *utf32_output++ = char32_t(buf[pos]);
          pos++;
        }
        continue;
      }
    }
    uint8_t leading_byte = data[pos]; // leading byte
    if (leading_byte < 0b10000000) {
      // converting one ASCII byte !!!
      *utf32_output++ = char32_t(leading_byte);
      pos++;
    } else if ((leading_byte & 0b11100000) == 0b11000000) {
      // We have a two-byte UTF-8
      if (pos + 1 >= len) {
        break;
      } // minimal bound checking
      *utf32_output++ = char32_t(((leading_byte & 0b00011111) << 6) |
                                 (data[pos + 1] & 0b00111111));
      pos += 2;
    } else if ((leading_byte & 0b11110000) == 0b11100000) {
      // We have a three-byte UTF-8
      if (pos + 2 >= len) {
        break;
      } // minimal bound checking
      *utf32_output++ = char32_t(((leading_byte & 0b00001111) << 12) |
                                 ((data[pos + 1] & 0b00111111) << 6) |
                                 (data[pos + 2] & 0b00111111));
      pos += 3;
    } else if ((leading_byte & 0b11111000) == 0b11110000) { // 0b11110000
      // we have a 4-byte UTF-8 word.
      if (pos + 3 >= len) {
        break;
      } // minimal bound checking
      uint32_t code_word = ((leading_byte & 0b00000111) << 18) |
                           ((data[pos + 1] & 0b00111111) << 12) |
                           ((data[pos + 2] & 0b00111111) << 6) |
                           (data[pos + 3] & 0b00111111);
      *utf32_output++ = char32_t(code_word);
      pos += 4;
    } else {
      // we may have a continuation but we do not do error checking
      return 0;
    }
  }
  return utf32_output - start;
}

} // namespace utf8_to_utf32
} // unnamed namespace
} // namespace scalar
} // namespace vamos

#endif
