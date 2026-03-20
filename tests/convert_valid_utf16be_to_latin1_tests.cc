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
#include <vector>

#include <tests/helpers/transcode_test_base.h>
#include <tests/helpers/random_int.h>
#include <tests/helpers/test.h>

namespace {
std::array<size_t, 7> input_size{7, 16, 12, 64, 67, 128, 256};

using vamos::tests::helpers::transcode_utf16_to_latin1_test_base;

constexpr int trials = 1000;
} // namespace

TEST_LOOP(trials, convert_2_UTF16_bytes) {
  // range for 1, 2 or 3 UTF-8 bytes
  vamos::tests::helpers::RandomIntRanges random(
      {
          {0x0000, 0x00ff},
      },
      seed);

  auto procedure = [&implementation](const char16_t *utf16le, size_t size,
                                     char *latin1) -> size_t {
    std::vector<char16_t> utf16be(size);
    implementation.change_endianness_utf16(utf16le, size, utf16be.data());

    return implementation.convert_valid_utf16be_to_latin1(utf16be.data(), size,
                                                          latin1);
  };
  auto size_procedure =
      [&implementation]([[maybe_unused]] const char16_t *utf16,
                        size_t size) -> size_t {
    return implementation.latin1_length_from_utf16(size);
  };
  for (size_t size : input_size) {
    transcode_utf16_to_latin1_test_base test(random, size);
    ASSERT_TRUE(test(procedure));
    ASSERT_TRUE(test.check_size(size_procedure));
  }
}

TEST_MAIN
