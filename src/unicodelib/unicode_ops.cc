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
/*
 * Acknowledgement: This file originates from CPython.
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#include <vamos/unicode.h>
#include <vamos/unicodelib/unicode_ops.h>

namespace vamos::unicode {

    static inline char32_t handle_capital_sigma(const char32_t *data, intptr_t length, intptr_t i) {
        intptr_t j;
        int final_sigma;
        char32_t c = 0; /* initialize to prevent gcc warning */
        /* U+03A3 is in the Final_Sigma context when, it is found like this:

         \p{cased}\p{case-ignorable}*U+03A3!(\p{case-ignorable}*\p{cased})

        where ! is a negation and \p{xxx} is a character with property xxx.
        */
        for (j = i - 1; j >= 0; j--) {
            c = data[j];
            if (!unicode_is_case_ignorable(c))
                break;
        }
        final_sigma = j >= 0 && unicode_is_cased(c);
        if (final_sigma) {
            for (j = i + 1; j < length; j++) {
                c = data[j];
                if (!unicode_is_case_ignorable(c))
                    break;
            }
            final_sigma = j == length || !unicode_is_cased(c);
        }
        return (final_sigma) ? 0x3C2 : 0x3C3;
    }

    static inline int lower_ucs4(
            const char32_t *data, intptr_t length, intptr_t i, char32_t c, char32_t *mapped) {
        /* Obscure special case. */
        if (c == 0x3A3) {
            mapped[0] = handle_capital_sigma(data, length, i);
            return 1;
        }
        return unicode_to_lower_full(c, mapped);
    }

    unicode_string ops_unicode_do_upper(unicode_view input) {
        unicode_string result;
        size_t i;
        result.reserve(input.length() * 3);
        for (i = 0; i < input.length(); i++) {
            char32_t c = input[i], mapped[3];
            int n_res, j;
            n_res = unicode_to_upper_full(c, mapped);
            for (j = 0; j < n_res; j++) {
                result.push_back(mapped[j]);
            }
        }
        return result;
    }

    unicode_string ops_unicode_do_lower(unicode_view input) {
        unicode_string result;
        size_t i;
        result.reserve(input.length() * 3);
        for (i = 0; i < input.length(); i++) {
            char32_t c = input[i], mapped[3];
            int n_res, j;
            n_res = lower_ucs4(input.data(), input.length(), i, c, mapped);
            for (j = 0; j < n_res; j++) {
                result.push_back(mapped[j]);
            }
        }
        return result;
    }

    vamos::Unicode ops_unicode_do_upper_optimize(unicode_view input) {
        vamos::Unicode result;
        size_t i;
        result.reserve(input.length() * 3);
        for (i = 0; i < input.length(); i++) {
            char32_t c = input[i], mapped[3];
            int n_res, j;
            n_res = unicode_to_upper_full(c, mapped);
            for (j = 0; j < n_res; j++) {
                result.push_back(mapped[j]);
            }
        }
        return result;
    }

    Unicode ops_unicode_do_lower_optimize(unicode_view input) {
        Unicode result;
        size_t i;
        result.reserve(input.length() * 3);
        for (i = 0; i < input.length(); i++) {
            char32_t c = input[i], mapped[3];
            int n_res, j;
            n_res = lower_ucs4(input.data(), input.length(), i, c, mapped);
            for (j = 0; j < n_res; j++) {
                result.push_back(mapped[j]);
            }
        }
        return result;
    }

}  // namespace vamos::unicode
