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
   Unicode character type helpers.

   Written by Marc-Andre Lemburg (mal@lemburg.com).
   Modified for Python 2.0 by Fredrik Lundh (fredrik@pythonware.com)

   Copyright (c) Corporation for National Research Initiatives.

*/

#define ALPHA_MASK 0x01
#define DECIMAL_MASK 0x02
#define DIGIT_MASK 0x04
#define LOWER_MASK 0x08
#define LINEBREAK_MASK 0x10
#define SPACE_MASK 0x20
#define TITLE_MASK 0x40
#define UPPER_MASK 0x80
#define XID_START_MASK 0x100
#define XID_CONTINUE_MASK 0x200
#define PRINTABLE_MASK 0x400
#define NUMERIC_MASK 0x800
#define CASE_IGNORABLE_MASK 0x1000
#define CASED_MASK 0x2000
#define EXTENDED_CASE_MASK 0x4000

#include <vamos/unicodelib/unicode_object.h>

namespace vamos::unicode {

// clang-format off

    typedef struct {
        /*
           These are either deltas to the character or offsets in
           _Unicode_ExtendedCase.
        */
        const int upper;
        const int lower;
        const int title;
        /* Note if more flag space is needed, decimal and digit could be unified. */
        const unsigned char decimal;
        const unsigned char digit;
        const unsigned short flags;
    } UnicodeTypeRecord;

}  // namespace vamos::unicode

#include "unicodetype_db.h"

namespace vamos::unicode {

    static const UnicodeTypeRecord *
    gettyperecord(char32_t code) noexcept {
        int index;

        if (code >= 0x110000)
            index = 0;
        else {
            index = index1[(code >> SHIFT)];
            index = index2[(index << SHIFT) + (code & ((1 << SHIFT) - 1))];
        }

        return &_Unicode_TypeRecords[index];
    }


    /* Returns the integer decimal (0-9) for Unicode characters having
       this property, -1 otherwise. */

    int unicode_to_decimal_digit(char32_t ch) noexcept {
        const UnicodeTypeRecord *ctype = gettyperecord(ch);

        return (ctype->flags & DECIMAL_MASK) ? ctype->decimal : -1;
    }


    /* Returns the integer digit (0-9) for Unicode characters having
       this property, -1 otherwise. */

    int unicode_to_digit(char32_t ch) noexcept {
        const UnicodeTypeRecord *ctype = gettyperecord(ch);

        return (ctype->flags & DIGIT_MASK) ? ctype->digit : -1;
    }

    int unicode_is_digit(char32_t ch) noexcept {
        if (unicode_to_digit(ch) < 0)
            return 0;
        return 1;
    }


    int unicode_to_lower_full(char32_t ch, char32_t *res) noexcept {
        const UnicodeTypeRecord *ctype = gettyperecord(ch);

        if (ctype->flags & EXTENDED_CASE_MASK) {
            int index = ctype->lower & 0xFFFF;
            int n = ctype->lower >> 24;
            int i;
            for (i = 0; i < n; i++)
                res[i] = _Unicode_ExtendedCase[index + i];
            return n;
        }
        res[0] = ch + ctype->lower;
        return 1;
    }


    int unicode_to_upper_full(char32_t ch, char32_t *res) noexcept {
        const UnicodeTypeRecord *ctype = gettyperecord(ch);

        if (ctype->flags & EXTENDED_CASE_MASK) {
            int index = ctype->upper & 0xFFFF;
            int n = ctype->upper >> 24;
            int i;
            for (i = 0; i < n; i++)
                res[i] = _Unicode_ExtendedCase[index + i];
            return n;
        }
        res[0] = ch + ctype->upper;
        return 1;
    }

    int unicode_is_cased(char32_t ch) noexcept {
        const UnicodeTypeRecord *ctype = gettyperecord(ch);

        return (ctype->flags & CASED_MASK) != 0;
    }

    int unicode_is_case_ignorable(char32_t ch) noexcept {
        const UnicodeTypeRecord *ctype = gettyperecord(ch);

        return (ctype->flags & CASE_IGNORABLE_MASK) != 0;
    }

    /* Returns 1 for Unicode characters having the category 'Ll', 'Lu', 'Lt',
       'Lo' or 'Lm',  0 otherwise. */

    int unicode_is_alpha(char32_t ch) noexcept {
        const UnicodeTypeRecord *ctype = gettyperecord(ch);

        return (ctype->flags & ALPHA_MASK) != 0;
    }

// clang-format on
}  // namespace vamos::unicode
