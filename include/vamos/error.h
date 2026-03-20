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
namespace vamos {

    enum error_code {
        SUCCESS = 0,
        HEADER_BITS, // Any byte must have fewer than 5 header bits.
        TOO_SHORT,   // The leading byte must be followed by N-1 continuation bytes,
        // where N is the UTF-8 character length This is also the error
        // when the input is truncated.
        TOO_LONG,    // We either have too many consecutive continuation bytes or the
        // string starts with a continuation byte.
        OVERLONG, // The decoded character must be above U+7F for two-byte characters,
        // U+7FF for three-byte characters, and U+FFFF for four-byte
        // characters.
        TOO_LARGE, // The decoded character must be less than or equal to
        // U+10FFFF,less than or equal than U+7F for ASCII OR less than
        // equal than U+FF for Latin1
        SURROGATE, // The decoded character must be not be in U+D800...DFFF (UTF-8 or
        // UTF-32) OR a high surrogate must be followed by a low surrogate
        // and a low surrogate must be preceded by a high surrogate
        // (UTF-16) OR there must be no surrogate at all (Latin1)
        INVALID_BASE64_CHARACTER, // Found a character that cannot be part of a valid
        // base64 string. This may include a misplaced
        // padding character ('=').
        BASE64_INPUT_REMAINDER,   // The base64 input terminates with a single
        // character, excluding padding (=).
        BASE64_EXTRA_BITS,        // The base64 input terminates with non-zero
        // padding bits.
        OUTPUT_BUFFER_TOO_SMALL,  // The provided buffer is too small.
        OTHER                     // Not related to validation/transcoding.
    };

    struct result {
        error_code error;
        size_t count; // In case of error, indicates the position of the error. In
        // case of success, indicates the number of code units
        // validated/written.

        vamos_really_inline result() : error{error_code::SUCCESS}, count{0} {}

        vamos_really_inline result(error_code err, size_t pos)
                : error{err}, count{pos} {}

        [[nodiscard]] vamos_really_inline bool is_ok() const {
            return error == error_code::SUCCESS;
        }

        [[nodiscard]] vamos_really_inline bool is_err() const {
            return error != error_code::SUCCESS;
        }
    };

    struct full_result {
        error_code error;
        size_t input_count;
        size_t output_count;

        vamos_really_inline full_result()
                : error{error_code::SUCCESS}, input_count{0}, output_count{0} {}

        vamos_really_inline full_result(error_code err, size_t pos_in,
                                        size_t pos_out)
                : error{err}, input_count{pos_in}, output_count{pos_out} {}

        vamos_really_inline operator result() const noexcept {
            if (error == error_code::SUCCESS ||
                error == error_code::BASE64_INPUT_REMAINDER) {
                return result{error, output_count};
            } else {
                return result{error, input_count};
            }
        }
    };

} // namespace vamos
