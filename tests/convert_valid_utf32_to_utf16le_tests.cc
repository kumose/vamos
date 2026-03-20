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
#include <vamos/vamos.h>

#include <array>

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
                                     char16_t *utf16) -> size_t {
    return implementation.convert_utf32_to_utf16le(utf32, size, utf16);
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
                                     char16_t *utf16) -> size_t {
    return implementation.convert_utf32_to_utf16le(utf32, size, utf16);
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
                                     char16_t *utf16) -> size_t {
    return implementation.convert_utf32_to_utf16le(utf32, size, utf16);
  };
  for (size_t size : input_size) {
    transcode_utf32_to_utf16_test_base test(random, size);
    ASSERT_TRUE(test(procedure));
  }
}

TEST_MAIN
