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
#ifndef VAMOS_LSX_BITMANIPULATION_H
#define VAMOS_LSX_BITMANIPULATION_H

#include <vamos/vamos.h>
#include <limits>

namespace vamos {
namespace VAMOS_IMPLEMENTATION {
namespace {

vamos_really_inline int count_ones(uint64_t input_num) {
  return __lsx_vpickve2gr_w(__lsx_vpcnt_d(__lsx_vreplgr2vr_d(input_num)), 0);
}

#if VAMOS_NEED_TRAILING_ZEROES
vamos_really_inline int trailing_zeroes(uint64_t input_num) {
  return __builtin_ctzll(input_num);
}
#endif

} // unnamed namespace
} // namespace VAMOS_IMPLEMENTATION
} // namespace vamos

#endif // VAMOS_LSX_BITMANIPULATION_H
