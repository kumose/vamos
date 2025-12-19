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
                                     char16_t *utf16) -> size_t {
    return implementation.convert_latin1_to_utf16le(latin1, size, utf16);
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
