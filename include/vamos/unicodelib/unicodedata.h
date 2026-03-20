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
/*
 * Acknowledgement: This file originates from CPython.
 *
 * This module provides access to the Unicode Character Database which
 * defines character properties for all Unicode characters. The data in
 * this database is based on the UnicodeData.txt file version
 * which is publicly available from ftp://ftp.unicode.org/.
 *
 * The module uses the same names and symbols as defined by the
 * UnicodeData File Format.
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

#include <vamos/unicodelib/unicode_object.h>
#include <vamos/unicodelib/unicode_normal_form.h>
#include <vamos/unicode.h>
#include <vamos/unicode_view.h>
#include <cstdint>
#include <optional>

namespace vamos::unicode {

    /* ------------- Previous-version API ------------------------------------- */
    struct UnicodeDataPreviousDBVersion;

    class UnicodeData {
    public:
        enum UCD_VERSION {
            DEFAULT = 0,    // version 11.0.0 from python 3.8.3
            VERSION_3_2_0,  // unicode data 3.2.0
        };

    public:
        // constructor
        explicit UnicodeData(UCD_VERSION ver = UCD_VERSION::DEFAULT);

        UnicodeData(const UnicodeData &) = default;

        UnicodeData(UnicodeData &&) noexcept = default;

        UnicodeData &operator=(const UnicodeData &) = default;

        UnicodeData &operator=(UnicodeData &&) noexcept = default;

    public:
        // interface

        /**
         * Look up character by name.
         *
         * If a character with the given name is found, return the
         * corresponding character.  If not found, KeyError is raised.
         *
         * @param name
         * @return
         */
        Unicode lookup(std::string_view name) const;

        /**
         * Returns the name assigned to the character chr as a string.
         *
         * If no name is defined, default is returned, or, if not given,
         * ValueError is raised.
         *
         * @param chr
         * @param default_value
         * @return
         */
        std::string name(int chr, std::string *default_value = nullptr) const;

        /**
         * Converts a Unicode character into its equivalent decimal value.
         *
         * Returns the decimal value assigned to the character chr as integer.
         * If no such value is defined, default is returned, or, if not given,
         * ValueError is raised.
         *
         * @param chr
         * @param default_value
         * @return
         */
        std::optional<long> decimal(int chr, long *default_value = nullptr) const;

        /**
         * Converts a Unicode character into its equivalent digit value.
         *
         * Returns the digit value assigned to the character chr as integer.
         * If no such value is defined, default is returned, or, if not given,
         * ValueError is raised.
         *
         * @param chr
         * @param default_value
         * @return
         */
        std::optional<long> digit(int chr, long *default_value = nullptr) const;

        /**
         * Converts a Unicode character into its equivalent numeric value.
         *
         * Returns the numeric value assigned to the character chr as float.
         * If no such value is defined, default is returned, or, if not given,
         * ValueError is raised.
         *
         * @param chr
         * @param default_value
         * @return
         */
        std::optional<double> numeric(int chr, double *default_value = nullptr) const;

        /**
         * Returns the general category assigned to the character chr as string.
         *
         * @param chr
         * @return
         */
        [[nodiscard]] std::string_view category(int chr) const;

        /**
         * Returns the bidirectional class assigned to the character chr as string.
         *
         * @param chr
         * @return
         */
        [[nodiscard]] std::string_view bidirectional(int chr) const;

        /**
         * Returns the canonical combining class assigned to the character chr as integer.
         *
         * Returns 0 if no combining class is defined.
         *
         * @param chr
         * @return
         */
        [[nodiscard]] int combining(int chr) const;

        /**
         * Returns the east asian width assigned to the character chr as string.
         *
         * @param chr
         * @return
         */
        [[nodiscard]] std::string_view east_asian_width(int chr) const;

        /**
         * Returns the mirrored property assigned to the character chr as integer.
         *
         * Returns 1 if the character has been identified as a "mirrored"
         * character in bidirectional text, 0 otherwise.
         *
         * @param chr
         * @return
         */
        [[nodiscard]] int mirrored(int chr) const;

        /**
         * Returns the character decomposition mapping assigned to the character chr as string.
         *
         * An empty string is returned in case no such mapping is defined.
         *
         * @param chr
         * @return
         */
        [[nodiscard]] std::string decomposition(int chr) const;

        /**
         * Return the normal form 'form' for the Unicode string unistr.
         *
         * Valid values for form are 'NFC', 'NFKC', 'NFD', and 'NFKD'.
         *
         * @param form UnicodeNormalForm
         * @param input
         * @return
         */
        [[nodiscard]] Unicode normalize(int32_t form, const unicode_view &input) const;

        /**
         * Return whether the Unicode string unistr is in the normal form 'form'.
         *
         * Valid values for form are 'NFC', 'NFKC', 'NFD', and 'NFKD'.
         *
         * TODO(maxiandi): add unicode_view replace input type
         * @param form
         * @param input
         * @return
         */
        [[nodiscard]] bool is_normalized(int32_t form, const unicode_view &input) const;

        [[nodiscard]] UCD_VERSION unidata_version() const {
            return ucd_version_;
        }

    private:
        UCD_VERSION ucd_version_ = UCD_VERSION::DEFAULT;
        UnicodeDataPreviousDBVersion *previous_ucd_ = nullptr;
    };

}  // namespace vamos::unicode
