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
std::pair<const char *, char32_t *>
avx2_convert_latin1_to_utf32(const char *buf, size_t len,
                             char32_t *utf32_output) {
  size_t rounded_len = ((len | 7) ^ 7); // Round down to nearest multiple of 8

  for (size_t i = 0; i < rounded_len; i += 8) {
    // Load 8 Latin1 characters into a 64-bit register
    __m128i in = _mm_loadl_epi64((__m128i *)&buf[i]);

    // Zero extend each set of 8 Latin1 characters to 8 32-bit integers using
    // vpmovzxbd
    __m256i out = _mm256_cvtepu8_epi32(in);

    // Store the results back to memory
    _mm256_storeu_si256((__m256i *)&utf32_output[i], out);
  }

  // return pointers pointing to where we left off
  return std::make_pair(buf + rounded_len, utf32_output + rounded_len);
}
