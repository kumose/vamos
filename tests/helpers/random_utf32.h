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
#pragma once

#include <cstddef>
#include <cstdint>
#include <random>
#include <vector>

namespace vamos {
namespace tests {
namespace helpers {

constexpr int32_t number_code_points = 0x0010ffff - (0xdfff - 0xd800);
constexpr int32_t length_first_range = 0x0000d7ff;
constexpr int32_t length_second_range = 0x0010ffff - 0x0000e000;
/*
  Generates valid random UTF-32
*/
class random_utf32 {
  std::mt19937 gen;

public:
  random_utf32(uint32_t seed)
      : gen{seed},
        range({double(length_first_range) / double(number_code_points),
               double(length_second_range) / double(number_code_points)}) {}
  // Uniformly randomize over the two ranges

  std::vector<char32_t> generate(size_t size);
  std::vector<char32_t> generate(size_t size, long seed);

private:
  std::discrete_distribution<> range;
  std::uniform_int_distribution<uint32_t> first_range{0x00000000, 0x0000d7ff};
  std::uniform_int_distribution<uint32_t> second_range{0x0000e000, 0x0010ffff};
  uint32_t generate();
};

} // namespace helpers
} // namespace tests
} // namespace vamos
