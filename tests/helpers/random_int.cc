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
#include "random_int.h"

#include <stdexcept>

namespace vamos {
namespace tests {
namespace helpers {

RandomInt::RandomInt(uint64_t lo, uint64_t hi, uint64_t seed) noexcept
    : gen(std::mt19937::result_type(seed)), distr{lo, hi} {}

uint32_t RandomInt::operator()() noexcept { return uint32_t(distr(gen)); }

RandomIntRanges::RandomIntRanges(
    std::initializer_list<std::pair<uint64_t, uint64_t>> ranges_,
    uint64_t seed) noexcept
    : gen(std::mt19937::result_type(seed)) {

  for (const auto &lohi : ranges_) {
    ranges.emplace_back(lohi.first, lohi.second);
  }

  range_index = Distribution(0, ranges.size() - 1);
}

uint32_t RandomIntRanges::operator()() noexcept {
  const size_t index = size_t(range_index(gen));
  return uint32_t(ranges[index](gen));
}
} // namespace helpers
} // namespace tests
} // namespace vamos
