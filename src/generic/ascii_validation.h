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
