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
/* Returns:
   - pointer to the last unprocessed character (a scalar fallback should check
   the rest);
   - nullptr if an error was detected.
*/
const char32_t *avx2_validate_utf32le(const char32_t *input, size_t size) {
  const char32_t *end = input + size;

  const __m256i standardmax = _mm256_set1_epi32(0x10ffff);
  const __m256i offset = _mm256_set1_epi32(0xffff2000);
  const __m256i standardoffsetmax = _mm256_set1_epi32(0xfffff7ff);
  __m256i currentmax = _mm256_setzero_si256();
  __m256i currentoffsetmax = _mm256_setzero_si256();

  while (input + 8 < end) {
    const __m256i in = _mm256_loadu_si256((__m256i *)input);
    currentmax = _mm256_max_epu32(in, currentmax);
    currentoffsetmax =
        _mm256_max_epu32(_mm256_add_epi32(in, offset), currentoffsetmax);
    input += 8;
  }
  __m256i is_zero =
      _mm256_xor_si256(_mm256_max_epu32(currentmax, standardmax), standardmax);
  if (_mm256_testz_si256(is_zero, is_zero) == 0) {
    return nullptr;
  }

  is_zero = _mm256_xor_si256(
      _mm256_max_epu32(currentoffsetmax, standardoffsetmax), standardoffsetmax);
  if (_mm256_testz_si256(is_zero, is_zero) == 0) {
    return nullptr;
  }

  return input;
}

const result avx2_validate_utf32le_with_errors(const char32_t *input,
                                               size_t size) {
  const char32_t *start = input;
  const char32_t *end = input + size;

  const __m256i standardmax = _mm256_set1_epi32(0x10ffff);
  const __m256i offset = _mm256_set1_epi32(0xffff2000);
  const __m256i standardoffsetmax = _mm256_set1_epi32(0xfffff7ff);
  __m256i currentmax = _mm256_setzero_si256();
  __m256i currentoffsetmax = _mm256_setzero_si256();

  while (input + 8 < end) {
    const __m256i in = _mm256_loadu_si256((__m256i *)input);
    currentmax = _mm256_max_epu32(in, currentmax);
    currentoffsetmax =
        _mm256_max_epu32(_mm256_add_epi32(in, offset), currentoffsetmax);

    __m256i is_zero = _mm256_xor_si256(
        _mm256_max_epu32(currentmax, standardmax), standardmax);
    if (_mm256_testz_si256(is_zero, is_zero) == 0) {
      return result(error_code::TOO_LARGE, input - start);
    }

    is_zero =
        _mm256_xor_si256(_mm256_max_epu32(currentoffsetmax, standardoffsetmax),
                         standardoffsetmax);
    if (_mm256_testz_si256(is_zero, is_zero) == 0) {
      return result(error_code::SURROGATE, input - start);
    }
    input += 8;
  }

  return result(error_code::SUCCESS, input - start);
}
