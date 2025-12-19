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
