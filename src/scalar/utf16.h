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
#ifndef VAMOS_UTF16_H
#define VAMOS_UTF16_H

namespace vamos {
namespace scalar {
namespace {
namespace utf16 {

template <endianness big_endian>
inline vamos_warn_unused bool validate(const char16_t *data,
                                         size_t len) noexcept {
  uint64_t pos = 0;
  while (pos < len) {
    char16_t word =
        !match_system(big_endian) ? u16_swap_bytes(data[pos]) : data[pos];
    if ((word & 0xF800) == 0xD800) {
      if (pos + 1 >= len) {
        return false;
      }
      char16_t diff = char16_t(word - 0xD800);
      if (diff > 0x3FF) {
        return false;
      }
      char16_t next_word = !match_system(big_endian)
                               ? u16_swap_bytes(data[pos + 1])
                               : data[pos + 1];
      char16_t diff2 = char16_t(next_word - 0xDC00);
      if (diff2 > 0x3FF) {
        return false;
      }
      pos += 2;
    } else {
      pos++;
    }
  }
  return true;
}

template <endianness big_endian>
inline vamos_warn_unused result validate_with_errors(const char16_t *data,
                                                       size_t len) noexcept {
  size_t pos = 0;
  while (pos < len) {
    char16_t word =
        !match_system(big_endian) ? u16_swap_bytes(data[pos]) : data[pos];
    if ((word & 0xF800) == 0xD800) {
      if (pos + 1 >= len) {
        return result(error_code::SURROGATE, pos);
      }
      char16_t diff = char16_t(word - 0xD800);
      if (diff > 0x3FF) {
        return result(error_code::SURROGATE, pos);
      }
      char16_t next_word = !match_system(big_endian)
                               ? u16_swap_bytes(data[pos + 1])
                               : data[pos + 1];
      char16_t diff2 = uint16_t(next_word - 0xDC00);
      if (diff2 > 0x3FF) {
        return result(error_code::SURROGATE, pos);
      }
      pos += 2;
    } else {
      pos++;
    }
  }
  return result(error_code::SUCCESS, pos);
}

template <endianness big_endian>
inline size_t count_code_points(const char16_t *p, size_t len) {
  // We are not BOM aware.
  size_t counter{0};
  for (size_t i = 0; i < len; i++) {
    char16_t word = !match_system(big_endian) ? u16_swap_bytes(p[i]) : p[i];
    counter += ((word & 0xFC00) != 0xDC00);
  }
  return counter;
}

template <endianness big_endian>
inline size_t utf8_length_from_utf16(const char16_t *p, size_t len) {
  // We are not BOM aware.
  size_t counter{0};
  for (size_t i = 0; i < len; i++) {
    char16_t word = !match_system(big_endian) ? u16_swap_bytes(p[i]) : p[i];
    counter++; // ASCII
    counter += static_cast<size_t>(
        word >
        0x7F); // non-ASCII is at least 2 bytes, surrogates are 2*2 == 4 bytes
    counter += static_cast<size_t>((word > 0x7FF && word <= 0xD7FF) ||
                                   (word >= 0xE000)); // three-byte
  }
  return counter;
}

template <endianness big_endian>
inline size_t utf32_length_from_utf16(const char16_t *p, size_t len) {
  // We are not BOM aware.
  size_t counter{0};
  for (size_t i = 0; i < len; i++) {
    char16_t word = !match_system(big_endian) ? u16_swap_bytes(p[i]) : p[i];
    counter += ((word & 0xFC00) != 0xDC00);
  }
  return counter;
}

vamos_really_inline void
change_endianness_utf16(const char16_t *input, size_t size, char16_t *output) {
  for (size_t i = 0; i < size; i++) {
    *output++ = char16_t(input[i] >> 8 | input[i] << 8);
  }
}

template <endianness big_endian>
vamos_warn_unused inline size_t trim_partial_utf16(const char16_t *input,
                                                     size_t length) {
  if (length <= 1) {
    return length;
  }
  uint16_t last_word = uint16_t(input[length - 1]);
  last_word = !match_system(big_endian) ? u16_swap_bytes(last_word) : last_word;
  length -= ((last_word & 0xFC00) == 0xD800);
  return length;
}

} // namespace utf16
} // unnamed namespace
} // namespace scalar
} // namespace vamos

#endif
