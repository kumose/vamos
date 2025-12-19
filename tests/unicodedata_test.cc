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

#include <tests/helpers/test.h>
#include <vamos/unicode.h>
#include <vamos/vamos.h>
#include <vamos/unicodelib/unicodedata.h>
#include <iostream>

using namespace vamos::unicode;

TEST(UnicodeDatanormalize) {
    vamos::Unicode s1;
    vamos::Unicode s2;
    vamos::Unicode s3;
    uint8_t a[] = "Spicy Jalape\u00f1o";
    const uint8_t *ab = reinterpret_cast<const uint8_t *>("Spicy Jalape\u00f1o");
    vamos::convert_utf8_to_utf32("Spicy Jalape\u00f1o", &s1);
    vamos::convert_utf8_to_utf32(std::string_view("Spicy Jalapen\u0303o"), &s2);
    vamos::convert_utf8_to_utf32(std::string_view("Spicy Jalape\u00f1o"), &s3);
    std::cout<<std::endl;
    std::cout<<"s1: "<<s1<<" n: "<<s1.size()<<std::endl;
    std::cout<<"s2: "<<s2<<" n: "<<s2.size()<<std::endl;
    std::cout<<"s3: "<<s3<<" n: "<<s3.size()<<std::endl;
    ASSERT_TRUE(s1 == s3);
    UnicodeData unicodedata;
    auto s2_nfc = unicodedata.normalize(UnicodeNormalForm::NFC, s2.view());
    std::cout<<"s2_nfc: "<<s2_nfc<<" n: "<<s2_nfc.size()<<std::endl;
    for(auto &i: s1) {
        std::cout<<i;
    }
    std::cout<<std::endl;
    for(auto &i: s2_nfc) {
        std::cout<<i;
    }
    std::cout<<std::endl;
    for(auto &i: s3) {
        std::cout<<i;
    }
    std::cout<<std::endl;
    ASSERT_TRUE((s2_nfc == s1));
    auto s1_nfd = unicodedata.normalize(UnicodeNormalForm::NFD, s1.view());
    ASSERT_TRUE(s1_nfd == s2);
}

TEST(UnicodeDatadecimal) {
    UnicodeData unicodedata;
    auto d = unicodedata.decimal('9');
    ASSERT_TRUE(*d == 9);
    ASSERT_TRUE(!unicodedata.decimal('a'));
}

TEST_MAIN