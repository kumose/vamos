
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