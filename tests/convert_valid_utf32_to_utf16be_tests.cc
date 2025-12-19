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
#include <vamos/vamos.h>

#include <array>
#include <vector>

#include <tests/helpers/transcode_test_base.h>
#include <tests/helpers/random_int.h>
#include <tests/helpers/test.h>

namespace {
std::array<size_t, 7> input_size{7, 16, 12, 64, 67, 128, 256};

using vamos::tests::helpers::transcode_utf32_to_utf16_test_base;

constexpr int trials = 1000;
} // namespace

TEST_LOOP(trials, convert_into_2_UTF16_bytes) {
  // range for 2 UTF-16 bytes
  vamos::tests::helpers::RandomIntRanges random(
      {{0x0000, 0xd7ff}, {0xe000, 0xffff}}, seed);

  auto procedure = [&implementation](const char32_t *utf32, size_t size,
                                     char16_t *utf16le) -> size_t {
    std::vector<char16_t> utf16be(size);
    size_t len =
        implementation.convert_utf32_to_utf16be(utf32, size, utf16be.data());
    implementation.change_endianness_utf16(utf16be.data(), len, utf16le);
    return len;
  };
  for (size_t size : input_size) {
    transcode_utf32_to_utf16_test_base test(random, size);
    ASSERT_TRUE(test(procedure));
  }
}

TEST_LOOP(trials, convert_into_4_UTF16_bytes) {
  // range for 4 UTF-16 bytes
  vamos::tests::helpers::RandomIntRanges random({{0x10000, 0x10ffff}}, seed);

  auto procedure = [&implementation](const char32_t *utf32, size_t size,
                                     char16_t *utf16le) -> size_t {
    std::vector<char16_t> utf16be(2 * size);
    size_t len =
        implementation.convert_utf32_to_utf16be(utf32, size, utf16be.data());
    implementation.change_endianness_utf16(utf16be.data(), len, utf16le);
    return len;
  };
  for (size_t size : input_size) {
    transcode_utf32_to_utf16_test_base test(random, size);
    ASSERT_TRUE(test(procedure));
  }
}

TEST_LOOP(trials, convert_into_2_or_4_UTF16_bytes) {
  // range for 2 or 4 UTF-16 bytes (all codepoints)
  vamos::tests::helpers::RandomIntRanges random(
      {{0x0000, 0xd7ff}, {0xe000, 0xffff}, {0x10000, 0x10ffff}}, seed);

  auto procedure = [&implementation](const char32_t *utf32, size_t size,
                                     char16_t *utf16le) -> size_t {
    std::vector<char16_t> utf16be(2 * size);
    size_t len =
        implementation.convert_utf32_to_utf16be(utf32, size, utf16be.data());
    implementation.change_endianness_utf16(utf16be.data(), len, utf16le);
    return len;
  };
  for (size_t size : input_size) {
    transcode_utf32_to_utf16_test_base test(random, size);
    ASSERT_TRUE(test(procedure));
  }
}

TEST_MAIN
