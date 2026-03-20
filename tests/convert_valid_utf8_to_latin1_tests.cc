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

using vamos::tests::helpers::transcode_utf8_to_latin1_test_base;

constexpr size_t trials = 10000;
} // namespace

TEST_LOOP(trials, convert_pure_ASCII) {
  size_t counter = 0;
  auto generator = [&counter]() -> uint8_t { return counter++ & 0x7f; };

  auto procedure = [&implementation](const char *utf8, size_t size,
                                     char *latin1) -> size_t {
    return implementation.convert_valid_utf8_to_latin1(utf8, size, latin1);
  };
  auto size_procedure = [&implementation](const char *utf8,
                                          size_t size) -> size_t {
    return implementation.latin1_length_from_utf8(utf8, size);
  };

  for (size_t size : input_size) {
    transcode_utf8_to_latin1_test_base test(generator, size);
    ASSERT_TRUE(test(procedure));
    ASSERT_TRUE(test.check_size(size_procedure));
  }
}

TEST_LOOP(trials, convert_1_or_2_valid_UTF8_bytes_to_latin1) {
  vamos::tests::helpers::RandomInt random(
      0x0000, 0x0ff, seed); // range for 1 or 2 UTF-8 bytes

  auto procedure = [&implementation](const char *utf8, size_t size,
                                     char *latin1) -> size_t {
    return implementation.convert_valid_utf8_to_latin1(utf8, size, latin1);
  };
  auto size_procedure = [&implementation](const char *utf8,
                                          size_t size) -> size_t {
    return implementation.latin1_length_from_utf8(utf8, size);
  };
  for (size_t size : input_size) {
    transcode_utf8_to_latin1_test_base test(random, size);
    ASSERT_TRUE(test(procedure));
    ASSERT_TRUE(test.check_size(size_procedure));
  }
}

TEST_MAIN
