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
template <endianness big_endian>
simd8<uint8_t> utf16_gather_high_bytes(const simd16<uint16_t> in0,
                                       const simd16<uint16_t> in1) {
  if (big_endian) {
    const auto mask = simd16<uint16_t>(0x00ff);
    const auto t0 = in0 & mask;
    const auto t1 = in1 & mask;

    return simd16<uint16_t>::pack(t0, t1);
  } else {
    return simd8<uint8_t>(__lasx_xvssrlni_bu_h(in1.value, in0.value, 8));
  }
}
