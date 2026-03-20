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