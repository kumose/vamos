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

using vamos::tests::helpers::transcode_utf8_to_utf16_test_base;

constexpr size_t trials = 1000;
} // namespace

TEST(convert_latin1_only) {
  size_t counter = 0;
  auto generator = [&counter]() -> uint32_t { return counter++ & 0xFF; };

  auto procedure = [&implementation](const char32_t *utf32, size_t size,
                                     char *latin1) -> size_t {
    vamos::result res =
        implementation.convert_utf32_to_latin1_with_errors(utf32, size, latin1);
    ASSERT_EQUAL(res.error, vamos::error_code::SUCCESS);
    return res.count;
  };

  auto size_procedure = [](const char32_t *, size_t size) -> size_t {
    return size;
  };
  for (size_t size : input_size) {
    vamos::tests::helpers::transcode_utf32_to_latin1_test_base test(generator,
                                                                      size);
    ASSERT_TRUE(test(procedure));
    ASSERT_TRUE(test.check_size(size_procedure));
  }
}

TEST_LOOP(trials, convert_fails_if_input_too_large) {
  vamos::tests::helpers::RandomInt generator(0xFF, 0xffffffff, seed);
  const size_t size = 64;
  vamos::tests::helpers::transcode_utf32_to_latin1_test_base test(
      []() { return '*'; }, size + 32);

  for (size_t j = 0; j < 1000; j++) {
    uint32_t wrong_value = generator();
    for (size_t i = 0; i < size; i++) {

      auto procedure = [&implementation, &i](const char32_t *utf32, size_t size,
                                             char *latin1) -> size_t {
        vamos::result res =
            implementation.convert_utf32_to_latin1_with_errors(utf32, size,
                                                               latin1);
        ASSERT_EQUAL(res.error, vamos::error_code::TOO_LARGE);
        ASSERT_EQUAL(res.count, i);
        return 0;
      };

      auto old = test.input_utf32[i];
      test.input_utf32[i] = wrong_value;
      ASSERT_TRUE(test(procedure));
      test.input_utf32[i] = old;
    }
  }
}

TEST_MAIN
