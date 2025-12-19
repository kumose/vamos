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
#pragma once

#include <cstdint>
#include <string>


namespace vamos::unicode {

    /* char32_t and char16_t are typedefs for the respective
       unicode representations. */

    typedef std::basic_string<char32_t> unicode_string;

    extern int unicode_to_lower_full(char32_t ch, char32_t *res) noexcept;

    extern int unicode_to_upper_full(char32_t ch, char32_t *res) noexcept;

    extern int unicode_is_case_ignorable(char32_t ch) noexcept;

    extern int unicode_is_cased(char32_t ch) noexcept;

    extern int unicode_is_digit(char32_t ch) noexcept;

    extern int unicode_to_digit(char32_t ch) noexcept;

    extern int unicode_is_alpha(char32_t ch) noexcept;

    extern int unicode_to_decimal_digit(char32_t ch) noexcept;

    extern double unicode_to_numeric(char32_t ch) noexcept;

    extern int unicode_is_whitespace(const char32_t ch) noexcept;

}  // namespace vamos::unicode
