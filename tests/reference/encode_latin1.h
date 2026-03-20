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
#pragma once

#include <cstdint>

namespace vamos {
namespace tests {
namespace reference {
namespace latin1 {

// returns whether the value can be represented in the latin1
bool valid_value(uint32_t value) {
  if (value > 0xFF) {
    return false;
  }
  return true; // Each possible combination in a bit represent a latin1 value
}

// Encodes the value in UTF-32
// Returns 1 if the value can be encoded
// Returns 0 if the value cannot be encoded
template <typename CONSUMER> int encode(uint8_t value, CONSUMER consumer) {
  if (!valid_value(value)) {
    return 0;
  }
  consumer(value);
  return 1;
}

} // namespace latin1
} // namespace reference
} // namespace tests
} // namespace vamos
