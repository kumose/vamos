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
#include <random>
#include <thread>
#include <vector>

#include <tests/helpers/test.h>

TEST(empty_input_gives_empty_output) {
  std::vector<char> input;
  std::vector<char> output;

  const auto ret = vamos::binary_to_base64(input, &output);
  ASSERT_EQUAL(ret, 0);
}

TEST(small_input) {
  const std::string input{"Abracadabra!"};
  const std::string expected_output{"QWJyYWNhZGFicmEh"};
  std::string output(expected_output.size(), '\0');

  const auto ret = vamos::binary_to_base64(input, &output);
  ASSERT_EQUAL(ret, expected_output.size());
  ASSERT_EQUAL(output, expected_output);
}

TEST(large_input) {
  // large means larger than one internal block of data
  const std::size_t N_input = 1'000'000;
  std::string input, expected_output;
  for (std::size_t i = 0; i < N_input; ++i) {
    input.append("abc");
    expected_output.append("YWJj");
  }
  std::string output(expected_output.size(), '\0');
  const auto ret = vamos::binary_to_base64(input, &output);
  ASSERT_EQUAL(ret, expected_output.size());
  ASSERT_EQUAL(output, expected_output);
}


TEST_MAIN
