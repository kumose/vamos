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
#ifndef VAMOS_UTF32_TO_UTF16_H
#define VAMOS_UTF32_TO_UTF16_H

namespace vamos {
namespace scalar {
namespace {
namespace utf32_to_utf16 {

template <endianness big_endian>
inline size_t convert(const char32_t *buf, size_t len, char16_t *utf16_output) {
  const uint32_t *data = reinterpret_cast<const uint32_t *>(buf);
  size_t pos = 0;
  char16_t *start{utf16_output};
  while (pos < len) {
    uint32_t word = data[pos];
    if ((word & 0xFFFF0000) == 0) {
      if (word >= 0xD800 && word <= 0xDFFF) {
        return 0;
      }
      // will not generate a surrogate pair
      *utf16_output++ = !match_system(big_endian)
                            ? char16_t(u16_swap_bytes(uint16_t(word)))
                            : char16_t(word);
    } else {
      // will generate a surrogate pair
      if (word > 0x10FFFF) {
        return 0;
      }
      word -= 0x10000;
      uint16_t high_surrogate = uint16_t(0xD800 + (word >> 10));
      uint16_t low_surrogate = uint16_t(0xDC00 + (word & 0x3FF));
      if (!match_system(big_endian)) {
        high_surrogate = u16_swap_bytes(high_surrogate);
        low_surrogate = u16_swap_bytes(low_surrogate);
      }
      *utf16_output++ = char16_t(high_surrogate);
      *utf16_output++ = char16_t(low_surrogate);
    }
    pos++;
  }
  return utf16_output - start;
}

template <endianness big_endian>
inline result convert_with_errors(const char32_t *buf, size_t len,
                                  char16_t *utf16_output) {
  const uint32_t *data = reinterpret_cast<const uint32_t *>(buf);
  size_t pos = 0;
  char16_t *start{utf16_output};
  while (pos < len) {
    uint32_t word = data[pos];
    if ((word & 0xFFFF0000) == 0) {
      if (word >= 0xD800 && word <= 0xDFFF) {
        return result(error_code::SURROGATE, pos);
      }
      // will not generate a surrogate pair
      *utf16_output++ = !match_system(big_endian)
                            ? char16_t(u16_swap_bytes(uint16_t(word)))
                            : char16_t(word);
    } else {
      // will generate a surrogate pair
      if (word > 0x10FFFF) {
        return result(error_code::TOO_LARGE, pos);
      }
      word -= 0x10000;
      uint16_t high_surrogate = uint16_t(0xD800 + (word >> 10));
      uint16_t low_surrogate = uint16_t(0xDC00 + (word & 0x3FF));
      if (!match_system(big_endian)) {
        high_surrogate = u16_swap_bytes(high_surrogate);
        low_surrogate = u16_swap_bytes(low_surrogate);
      }
      *utf16_output++ = char16_t(high_surrogate);
      *utf16_output++ = char16_t(low_surrogate);
    }
    pos++;
  }
  return result(error_code::SUCCESS, utf16_output - start);
}

} // namespace utf32_to_utf16
} // unnamed namespace
} // namespace scalar
} // namespace vamos

#endif
