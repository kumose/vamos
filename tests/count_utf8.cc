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

#include <tests/helpers/random_int.h>
#include <tests/helpers/transcode_test_base.h>
#include <tests/helpers/random_utf8.h>
#include <tests/helpers/test.h>

namespace {
std::array<size_t, 10> input_size{7, 12, 16, 64, 67, 128, 256, 511, 1000, 2000};

const size_t trials = 10000;

using vamos::tests::helpers::transcode_utf8_to_utf16_test_base;
} // namespace

TEST_LOOP(trials, count_pure_ASCII) {
  vamos::tests::helpers::random_utf8 random(seed, 1, 0, 0, 0);

  for (size_t size : input_size) {
    auto generated = random.generate_counted(size);
    ASSERT_TRUE(implementation.count_utf8(
                    reinterpret_cast<const char *>(generated.first.data()),
                    size) == generated.second);
  }
}

TEST_LOOP(trials, count_1_or_2_UTF8_bytes) {
  vamos::tests::helpers::random_utf8 random(seed, 1, 1, 0, 0);

  for (size_t size : input_size) {
    auto generated = random.generate_counted(size);
    ASSERT_TRUE(implementation.count_utf8(
                    reinterpret_cast<const char *>(generated.first.data()),
                    size) == generated.second);
  }
}

TEST_LOOP(trials, count_1_or_2_or_3_UTF8_bytes) {
  vamos::tests::helpers::random_utf8 random(seed, 1, 1, 1, 0);

  for (size_t size : input_size) {
    auto generated = random.generate_counted(size);
    ASSERT_TRUE(implementation.count_utf8(
                    reinterpret_cast<const char *>(generated.first.data()),
                    size) == generated.second);
  }
}

TEST_LOOP(trials, count_1_2_3_or_4_UTF8_bytes) {
  vamos::tests::helpers::random_utf8 random(seed, 1, 1, 1, 1);

  for (size_t size : input_size) {
    auto generated = random.generate_counted(size);
    ASSERT_TRUE(implementation.count_utf8(
                    reinterpret_cast<const char *>(generated.first.data()),
                    size) == generated.second);
  }
}

TEST_MAIN
