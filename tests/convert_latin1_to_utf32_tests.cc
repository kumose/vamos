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

#include <tests/helpers/transcode_test_base.h>
#include <tests/helpers/random_int.h>
#include <tests/helpers/test.h>

namespace {
using vamos::tests::helpers::transcode_utf8_to_utf16_test_base;

constexpr size_t trials = 10000;
} // namespace

TEST_LOOP(trials, convert_all_latin1) {
  size_t counter = 0;
  auto generator = [&counter]() -> uint32_t { return counter++ & 0xFF; };

  auto procedure = [&implementation](const char *latin1, size_t size,
                                     char32_t *utf32) -> size_t {
    return implementation.convert_latin1_to_utf32(latin1, size, utf32);
  };
  auto size_procedure = [&implementation]([[maybe_unused]] const char *latin1,
                                          size_t size) -> size_t {
    return implementation.utf32_length_from_latin1(size);
  };
  // Check varying length inputs for upto 16 bytes
  for (size_t i = 240; i <= 256; i++) {
    vamos::tests::helpers::transcode_latin1_to_utf32_test_base test(generator,
                                                                      i);
    ASSERT_TRUE(test(procedure));
    ASSERT_TRUE(test.check_size(size_procedure));
  }
}

TEST_MAIN
