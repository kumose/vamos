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

using vamos::tests::helpers::transcode_latin1_to_utf16_test_base;

constexpr int trials = 1000;
} // namespace

TEST_LOOP(trials, convert_all_latin) {
  // range for 2 UTF-16 bytes
  vamos::tests::helpers::RandomIntRanges random({{0x00, 0xff}}, seed);

  auto procedure = [&implementation](const char *latin1, size_t size,
                                     char16_t *utf16le) -> size_t {
    std::vector<char16_t> utf16be(size);
    size_t len =
        implementation.convert_latin1_to_utf16be(latin1, size, utf16be.data());
    implementation.change_endianness_utf16(utf16be.data(), size, utf16le);
    return len;
  };
  auto size_procedure = [&implementation]([[maybe_unused]] const char *latin1,
                                          size_t size) -> size_t {
    return implementation.utf16_length_from_latin1(size);
  };
  for (size_t size : input_size) {
    transcode_latin1_to_utf16_test_base test(random, size);
    ASSERT_TRUE(test(procedure));
    ASSERT_TRUE(test.check_size(size_procedure));
  }
}

TEST_MAIN
