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


#include <tests/helpers/test.h>
#include <vamos/unicode.h>
#include <vamos/vamos.h>
#include <vamos/unicodelib/unicodedata.h>
#include <iostream>
#include <iostream>

using namespace vamos;
using namespace vamos::unicode;

TEST(UnicodeViewConstChars) {
    unicode_view a = U"hello";

    ASSERT_TRUE(a == U"hello");
    ASSERT_TRUE(a != U"hh");
    unicode_view b(U"hello");
    ASSERT_TRUE(a == b);
    unicode_view c(U"");
    ASSERT_TRUE(c == U"");
    ASSERT_TRUE(c != U"hh");
    ASSERT_TRUE(c != a);

    std::cout << a << std::endl;

}

TEST(UnicodeViewstd_string) {
    std::basic_string<char32_t> std_s(U"hello");
    unicode_view a = U"hello";
    std::cout<<std::endl;
    std::cout << a << std::endl;
    ASSERT_TRUE(a == std_s);
    a = std_s;
    ASSERT_TRUE(a == std_s);
    std::basic_string<char32_t> new_std_s((const char32_t *) a.data(), a.size());
    ASSERT_TRUE(new_std_s == std_s);
    std::cout << a << std::endl;
}

TEST(UnicodeViewMediumConverter) {
    Unicode raw;
    raw.resize(32, 'a');
    unicode_view raw_view = raw;
    Unicode copy1 = raw;
    Unicode copy2 = Unicode(raw_view);
    ASSERT_TRUE(copy1.data() != copy2.data());
    ASSERT_TRUE(copy1 == copy2);
}

TEST(UnicodeViewSmallConverter) {
    Unicode raw;
    raw.resize(1, 'a');
    unicode_view raw_view = raw;
    Unicode copy1 = raw;
    Unicode copy2 = Unicode(raw_view);
    ASSERT_TRUE(copy1.data() != copy2.data());
    ASSERT_TRUE(copy1 == copy2);
}

TEST_MAIN