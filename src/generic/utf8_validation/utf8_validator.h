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
namespace vamos {
namespace VAMOS_IMPLEMENTATION {
namespace {
namespace utf8_validation {

/**
 * Validates that the string is actual UTF-8.
 */
template <class checker>
bool generic_validate_utf8(const uint8_t *input, size_t length) {
  checker c{};
  buf_block_reader<64> reader(input, length);
  while (reader.has_full_block()) {
    simd::simd8x64<uint8_t> in(reader.full_block());
    c.check_next_input(in);
    reader.advance();
  }
  uint8_t block[64]{};
  reader.get_remainder(block);
  simd::simd8x64<uint8_t> in(block);
  c.check_next_input(in);
  reader.advance();
  c.check_eof();
  return !c.errors();
}

bool generic_validate_utf8(const char *input, size_t length) {
  return generic_validate_utf8<utf8_checker>(
      reinterpret_cast<const uint8_t *>(input), length);
}

/**
 * Validates that the string is actual UTF-8 and stops on errors.
 */
template <class checker>
result generic_validate_utf8_with_errors(const uint8_t *input, size_t length) {
  checker c{};
  buf_block_reader<64> reader(input, length);
  size_t count{0};
  while (reader.has_full_block()) {
    simd::simd8x64<uint8_t> in(reader.full_block());
    c.check_next_input(in);
    if (c.errors()) {
      if (count != 0) {
        count--;
      } // Sometimes the error is only detected in the next chunk
      result res = scalar::utf8::rewind_and_validate_with_errors(
          reinterpret_cast<const char *>(input),
          reinterpret_cast<const char *>(input + count), length - count);
      res.count += count;
      return res;
    }
    reader.advance();
    count += 64;
  }
  uint8_t block[64]{};
  reader.get_remainder(block);
  simd::simd8x64<uint8_t> in(block);
  c.check_next_input(in);
  reader.advance();
  c.check_eof();
  if (c.errors()) {
    if (count != 0) {
      count--;
    } // Sometimes the error is only detected in the next chunk
    result res = scalar::utf8::rewind_and_validate_with_errors(
        reinterpret_cast<const char *>(input),
        reinterpret_cast<const char *>(input) + count, length - count);
    res.count += count;
    return res;
  } else {
    return result(error_code::SUCCESS, length);
  }
}

result generic_validate_utf8_with_errors(const char *input, size_t length) {
  return generic_validate_utf8_with_errors<utf8_checker>(
      reinterpret_cast<const uint8_t *>(input), length);
}

} // namespace utf8_validation
} // unnamed namespace
} // namespace VAMOS_IMPLEMENTATION
} // namespace vamos
