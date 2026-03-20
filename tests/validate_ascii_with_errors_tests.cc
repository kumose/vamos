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

#include <tests/helpers/random_utf8.h>
#include <tests/helpers/test.h>

constexpr size_t trials = 1000;

TEST_LOOP(trials, no_error_ASCII) {
  vamos::tests::helpers::random_utf8 generator{seed, 1, 0, 0, 0};
  const auto ascii{generator.generate(512)};

  vamos::result res = implementation.validate_ascii_with_errors(
      reinterpret_cast<const char *>(ascii.data()), ascii.size());

  ASSERT_EQUAL(res.error, vamos::error_code::SUCCESS);
  ASSERT_EQUAL(res.count, ascii.size());
}

TEST_LOOP(trials, error_ASCII) {
  vamos::tests::helpers::random_utf8 generator{seed, 1, 0, 0, 0};

  auto ascii{generator.generate(512)};

  for (unsigned int i = 0; i < ascii.size(); i++) {
    ascii[i] += 0b10000000;

    vamos::result res = implementation.validate_ascii_with_errors(
        reinterpret_cast<const char *>(ascii.data()), ascii.size());

    ASSERT_EQUAL(res.error, vamos::error_code::TOO_LARGE);
    ASSERT_EQUAL(res.count, i);

    ascii[i] -= 0b10000000;
  }
}

TEST_MAIN
