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
#include <tests/helpers/test.h>

namespace {
using vamos::tests::helpers::transcode_utf8_to_utf16_test_base;

constexpr size_t trials = 10000;
} // namespace

TEST_LOOP(trials, convert_all_latin1) {
  size_t counter = 0;
  auto generator = [&counter]() -> uint8_t { return counter++ & 0xFF; };

  auto procedure = [&implementation](const char *latin1, size_t size,
                                     char *utf8) -> size_t {
    return implementation.convert_latin1_to_utf8(latin1, size, utf8);
  };
  auto size_procedure = [&implementation](const char *latin1,
                                          size_t size) -> size_t {
    return implementation.utf8_length_from_latin1(latin1, size);
  };

  vamos::tests::helpers::transcode_latin1_to_utf8_test_base test(generator,
                                                                   256);
  ASSERT_TRUE(test(procedure));
  ASSERT_TRUE(test.check_size(size_procedure));
}

TEST(convert_all_latin1_safe) {
  std::vector<char> latin1(1024);
  for (size_t i = 0; i < latin1.size(); i++) {
    latin1[i] = i & 0xff;
  }
  size_t utf8_length =
      implementation.utf8_length_from_latin1(latin1.data(), latin1.size());
  std::vector<char> utf8(utf8_length);
  const auto result = implementation.convert_latin1_to_utf8(
      latin1.data(), latin1.size(), utf8.data());
  ASSERT_EQUAL(result, utf8_length);
  for (size_t output_size = 0; output_size < utf8.size(); output_size++) {
    std::vector<char> utf8_buffer(output_size);
    size_t used_size = vamos::convert_latin1_to_utf8_safe(
        latin1.data(), latin1.size(), utf8_buffer.data(), output_size);
    for (size_t i = 0; i < used_size; i++) {
      ASSERT_EQUAL(utf8_buffer[i], utf8[i]);
    }
    if (used_size < output_size) {
      ASSERT_EQUAL(used_size, output_size - 1);
      ASSERT_TRUE(uint8_t(utf8[used_size]) >= 0x80);
    }
  }
}

TEST_MAIN
