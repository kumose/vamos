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
// file included directly
/**
 * Store the last N bytes of previous followed by 512-N bytes from input.
 */
template <int N> __m512i prev(__m512i input, __m512i previous) {
  static_assert(N <= 32, "N must be no larger than 32");
  const __m512i movemask =
      _mm512_setr_epi32(28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11);
  const __m512i rotated = _mm512_permutex2var_epi32(input, movemask, previous);
#if VAMOS_GCC8 || VAMOS_GCC9
  constexpr int shift = 16 - N; // workaround for GCC8,9
  return _mm512_alignr_epi8(input, rotated, shift);
#else
  return _mm512_alignr_epi8(input, rotated, 16 - N);
#endif // VAMOS_GCC8 || VAMOS_GCC9
}

template <unsigned idx0, unsigned idx1, unsigned idx2, unsigned idx3>
__m512i shuffle_epi128(__m512i v) {
  static_assert((idx0 >= 0 && idx0 <= 3), "idx0 must be in range 0..3");
  static_assert((idx1 >= 0 && idx1 <= 3), "idx1 must be in range 0..3");
  static_assert((idx2 >= 0 && idx2 <= 3), "idx2 must be in range 0..3");
  static_assert((idx3 >= 0 && idx3 <= 3), "idx3 must be in range 0..3");

  constexpr unsigned shuffle = idx0 | (idx1 << 2) | (idx2 << 4) | (idx3 << 6);
  return _mm512_shuffle_i32x4(v, v, shuffle);
}

template <unsigned idx> constexpr __m512i broadcast_epi128(__m512i v) {
  return shuffle_epi128<idx, idx, idx, idx>(v);
}
