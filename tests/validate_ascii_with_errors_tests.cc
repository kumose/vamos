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
