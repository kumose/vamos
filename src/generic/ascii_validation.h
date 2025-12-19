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
namespace ascii_validation {

bool generic_validate_ascii(const char *input, size_t length) {
  buf_block_reader<64> reader(reinterpret_cast<const uint8_t *>(input), length);
  uint8_t blocks[64]{};
  simd::simd8x64<uint8_t> running_or(blocks);
  while (reader.has_full_block()) {
    simd::simd8x64<uint8_t> in(reader.full_block());
    running_or |= in;
    reader.advance();
  }
  uint8_t block[64]{};
  reader.get_remainder(block);
  simd::simd8x64<uint8_t> in(block);
  running_or |= in;
  return running_or.is_ascii();
}

result generic_validate_ascii_with_errors(const char *input, size_t length) {
  buf_block_reader<64> reader(reinterpret_cast<const uint8_t *>(input), length);
  size_t count{0};
  while (reader.has_full_block()) {
    simd::simd8x64<uint8_t> in(reader.full_block());
    if (!in.is_ascii()) {
      result res = scalar::ascii::validate_with_errors(
          reinterpret_cast<const char *>(input + count), length - count);
      return result(res.error, count + res.count);
    }
    reader.advance();

    count += 64;
  }
  uint8_t block[64]{};
  reader.get_remainder(block);
  simd::simd8x64<uint8_t> in(block);
  if (!in.is_ascii()) {
    result res = scalar::ascii::validate_with_errors(
        reinterpret_cast<const char *>(input + count), length - count);
    return result(res.error, count + res.count);
  } else {
    return result(error_code::SUCCESS, length);
  }
}

} // namespace ascii_validation
} // unnamed namespace
} // namespace VAMOS_IMPLEMENTATION
} // namespace vamos
