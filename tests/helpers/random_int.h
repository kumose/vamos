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

#include <random>
#include <vector>
#include <initializer_list>
#include <utility>
#include <cstdint>

namespace vamos {
namespace tests {
namespace helpers {

class RandomInt {
  std::mt19937 gen;
  std::uniform_int_distribution<uint64_t> distr;

public:
  RandomInt(uint64_t lo, uint64_t hi, uint64_t seed) noexcept;

  uint32_t operator()() noexcept;
};

class RandomIntRanges {
  std::mt19937 gen;
  using Distribution = std::uniform_int_distribution<uint64_t>;

  Distribution range_index;
  std::vector<Distribution> ranges;

public:
  RandomIntRanges(std::initializer_list<std::pair<uint64_t, uint64_t>> ranges,
                  uint64_t seed) noexcept;

  uint32_t operator()() noexcept;
};

} // namespace helpers
} // namespace tests
} // namespace vamos
