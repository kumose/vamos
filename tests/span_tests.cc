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
#include <vamos/vamos.h>

#include <array>
#include <utility>
#include <vector>

#include <tests/helpers/test.h>

/// a span-like class which returns int as size (not std::size_t)
struct CustomSpan1 {
    using value_type = char;
    int size() const noexcept { return 3; }

    const char *data() const noexcept { return "hej"; }
};

struct Byte1 {
    char a;
};

struct Byte2 {
    using value_type = char;

    int size() const {
        return 0;
    }

    char *data() const {
        return nullptr;
    }

    char a;
    char b;
};

struct Byte4 {
    int a;
};


struct NonStand {
    using value_type = char;

    int size() const {
        return 0;
    }

    char *data() const {
        return nullptr;
    }

    char a;
    char b;
};

TEST(ValueTypeTraits_test) {
    /// 1 bytes
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<char>::value_type, char>));
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<int8_t>::value_type, char>));
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<uint8_t>::value_type, char>));
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<std::byte>::value_type, char>));
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<signed char>::value_type, char>));
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<unsigned char>::value_type, char>));
    /// 2 bytes
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<char16_t>::value_type, char16_t>));
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<int16_t>::value_type, char16_t>));
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<uint16_t>::value_type, char16_t>));
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<short>::value_type, char16_t>));
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<unsigned short>::value_type, char16_t>));
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<signed short>::value_type, char16_t>));
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<wchar_t>::value_type, char32_t>));

    /// 4 bytes
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<char32_t>::value_type, char32_t>));
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<int32_t>::value_type, char32_t>));
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<uint32_t>::value_type, char32_t>));
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<int>::value_type, char32_t>));
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<signed>::value_type, char32_t>));
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<unsigned>::value_type, char32_t>));

    /// invalid
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<float>::value_type, void>));
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<double>::value_type, void>));
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<Byte1>::value_type, void>));
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<Byte2>::value_type, void>));
    ASSERT_TRUE((std::is_same_v<vamos::detail::ValueTypeTraits<Byte4>::value_type, void>));

}

TEST(HasSizeMemberTraits_test) {
    ASSERT_FALSE((vamos::detail::HasDataMember<Byte1>::value));
    ASSERT_FALSE((vamos::detail::HasSizeMember<Byte1>::value));

    // std
    ASSERT_TRUE((vamos::detail::HasDataMember<std::string>::value));
    ASSERT_TRUE((vamos::detail::HasSizeMember<std::string>::value));
    ASSERT_TRUE((vamos::detail::HasDataMember<std::string_view>::value));
    ASSERT_TRUE((vamos::detail::HasSizeMember<std::string_view>::value));

    ASSERT_TRUE((vamos::detail::HasDataMember<std::vector<char>>::value));
    ASSERT_TRUE((vamos::detail::HasSizeMember<std::vector<char>>::value));

    ASSERT_TRUE((vamos::detail::HasDataMember<std::array<char, 10>>::value));
    ASSERT_TRUE((vamos::detail::HasSizeMember<std::array<char, 10>>::value));

    ASSERT_TRUE((vamos::detail::HasDataMember<NonStand>::value));
    ASSERT_TRUE((vamos::detail::HasSizeMember<NonStand>::value));
}

TEST(SpanType_test) {

    std::string abc("sadsd");

    vamos::InputSpan<std::string> span(abc);

    ASSERT_TRUE(span == abc);

    std::vector<char> vp;
    vp.push_back('a');
    vp.push_back('b');
    vp.push_back('c');
    vamos::InputSpan<std::vector<char>> vspan(vp);
    ASSERT_TRUE(vspan == "abc");

    ASSERT_TRUE(vspan == vp);
    ASSERT_TRUE(vp == vspan);
}

TEST(OutputSpan_test) {

    std::string abc;
    abc.resize(3);

    vamos::OutputSpan<std::string> span(&abc);
    auto ptr = span.data();
    ptr[0] = 'a';
    ptr[1] = 'b';
    ptr[2] = 'c';
    ASSERT_TRUE(abc == "abc");
}

template<typename C>
void auto_construct(const C &arg, std::basic_string_view<typename C::value_type> exp) {
    vamos::InputSpan<C> input_args(arg);
    ASSERT_TRUE(input_args == exp);
}

TEST(SpanType_auto_construct_test) {
    std::string_view abc("abc");
    auto_construct(abc, "abc");
}

TEST(autodect_can_use_containers_and_views) {
    std::vector<char> data{1, 2, 3, 4, 5};
    auto r1a = vamos::autodetect_encoding(data);
    auto r1d = vamos::autodetect_encoding(std::as_const(data));
    auto r1e = vamos::autodetect_encoding(std::move(data));

    std::vector<unsigned char> udata{1, 2, 3, 4, 5};
    auto r2a = vamos::autodetect_encoding(udata);
    auto r2d = vamos::autodetect_encoding(std::as_const(udata));

    std::vector<signed char> sdata{1, 2, 3, 4, 5};
    auto r3a = vamos::autodetect_encoding(udata);
    auto r3d = vamos::autodetect_encoding(std::as_const(udata));

    std::string stringdata{1, 2, 3, 4, 5};
    auto r4a = vamos::autodetect_encoding(stringdata);
    auto r4d = vamos::autodetect_encoding(std::as_const(stringdata));

    std::string_view stringview_data{stringdata};
    auto r5a = vamos::autodetect_encoding(stringview_data);
    auto r5b = vamos::autodetect_encoding(std::as_const(stringview_data));

    std::vector<std::uint8_t> u8data{1, 2, 3, 4, 5};
    auto r6a = vamos::autodetect_encoding(u8data);
    auto r6d = vamos::autodetect_encoding(std::as_const(u8data));

    std::vector<std::uint8_t> i8data{1, 2, 3, 4, 5};
    auto r7a = vamos::autodetect_encoding(i8data);
    auto r7d = vamos::autodetect_encoding(std::as_const(i8data));

    std::vector<std::byte> bdata;
    auto r8a = vamos::autodetect_encoding(bdata);
    auto r8d = vamos::autodetect_encoding(std::as_const(bdata));

    CustomSpan1 c;
    auto r9a = vamos::autodetect_encoding(c);
    auto r9b = vamos::autodetect_encoding(std::as_const(c));
    auto r9c = vamos::autodetect_encoding(std::move(c));
}


// this is used to prove that no copying takes place in the output parameter
struct non_movable_or_copyable_span {
    non_movable_or_copyable_span &
    operator=(non_movable_or_copyable_span &&) = delete;
    auto data() noexcept { return m_data; }
    auto data() const noexcept { return m_data; }
    auto size() const noexcept { return m_size; }
    char *m_data{};
    std::size_t m_size{};
};

TEST(convert_latin1_to_utf8_safe) {
    const std::vector<char> input{1, 2, 3, 4, 5};
    std::vector<char> output(input.size());
    auto r1a = vamos::convert_latin1_to_utf8_fixed(input, &output);
    std::vector<char> output1;
    auto r1b = vamos::convert_latin1_to_utf8(input, &output1);
    ASSERT_TRUE(r1a == output1.size());
    ASSERT_TRUE(r1b == r1a);
    ASSERT_TRUE(output == output1);
    r1b = vamos::convert_latin1_to_utf8_append(input, &output1);
    ASSERT_TRUE(r1b == r1a);
    ASSERT_TRUE((r1b * 2) == output1.size());
}

/*
TEST(convert_latin1_to_utf8_safe) {
    const std::vector<char> input{1, 2, 3, 4, 5};
    std::vector<char> output(input.size());
    auto r1a = vamos::convert_latin1_to_utf8_safe(input, output);
    auto r1b = vamos::convert_latin1_to_utf8_safe(input, std::span{output});
    auto r1c =
            vamos::convert_latin1_to_utf8_safe(std::move(input), std::span{output});

    // we handle const, mutable and rvalues for the output parameter
    const std::span s1{output};
    auto r1d = vamos::convert_latin1_to_utf8_safe(input, s1);
    std::span s2{output};
    auto r1e = vamos::convert_latin1_to_utf8_safe(input, s2);
    auto r1f = vamos::convert_latin1_to_utf8_safe(input, std::move(s2));

    // make sure no copying or move happens in the output parameter
    const non_movable_or_copyable_span nmcms{.m_data = output.data(),
            .m_size = output.size()};
    auto r2a = vamos::convert_latin1_to_utf8_safe(input, nmcms);
    auto r2b = vamos::convert_latin1_to_utf8_safe(
            input, non_movable_or_copyable_span{.m_data = output.data(),
                    .m_size = output.size()});

    // the output can be anything byte like
    std::vector<unsigned char> output3(input.size());
    auto r3a = vamos::convert_latin1_to_utf8_safe(input, output3);
    //... but not compile if it is anything else
    static_assert(
            !is_convert_latin1_to_utf8_safe_invokable<std::vector<char>,
                    std::vector<char16_t>>);

    // writing to a const object should not be possible
    static_assert(
            !is_convert_latin1_to_utf8_safe_invokable<std::vector<char>,
                    const std::vector<char>>);

    // writing to a std::string through .data() is ok since C++17
    static_assert(
            is_convert_latin1_to_utf8_safe_invokable<std::vector<char>, std::string>);
    static_assert(
            is_convert_latin1_to_utf8_safe_invokable<std::string, std::vector<char>>);
    static_assert(is_convert_latin1_to_utf8_safe_invokable<std::string_view,
            std::vector<char>>);
}
 */


/// a span-like class which returns an iterator as data (not a pointer)
struct CustomSpan2 {
  std::size_t size() const noexcept { return 3; }
  auto data() const noexcept { return m_data.begin(); }
  std::list<char> m_data;
};


TEST(validate_utf16_handles_various_sources) {
  std::vector<char16_t> data{1, 2, 3, 4, 5};
  auto r1a = vamos::validate_utf16(data);
  auto r1d = vamos::validate_utf16(std::as_const(data));
  auto r1e = vamos::validate_utf16(std::move(data));

}


TEST(validate_utf32_handles_various_sources) {
  std::vector<char32_t> data{1, 2, 3, 4, 5};
  auto r1a = vamos::validate_utf32(data);
  auto r1d = vamos::validate_utf32(std::as_const(data));
  auto r1e = vamos::validate_utf32(std::move(data));
}


TEST(validate_utf32_with_errors) {
  std::array<char32_t, 3> data{1, 2, 3};
  auto r1a = vamos::validate_utf32_with_errors(data);
  auto r1b = vamos::validate_utf32_with_errors(std::as_const(data));
}

TEST(convert_latin1_to_utf16le) {
  std::string input{"hej!"};
  std::array<char16_t, 4> output{};
  auto r1a = vamos::convert_latin1_to_utf16le_fix(input, &output);
  auto r1b = vamos::convert_latin1_to_utf16le_fix(std::as_const(input), &output);
}

TEST(convert_utf8_to_latin1) {
  std::string input{"hej!"};

  std::array<signed char, 4> output{};
  auto r1a = vamos::convert_utf8_to_latin1_fix(input, &output);
  auto r1b = vamos::convert_utf8_to_latin1_fix(std::as_const(input), &output);

  std::array<unsigned char, 4> output2{};
  auto r2a = vamos::convert_utf8_to_latin1_fix(input, &output2);
  auto r2b = vamos::convert_utf8_to_latin1_fix(std::as_const(input), &output2);
}

TEST(convert_utf8_to_utf16) {
  std::string input{"hej!"};

  std::array<char16_t, 4> output{};
  auto r1a = vamos::convert_utf8_to_utf16_fix(input, &output);
  auto r1b = vamos::convert_utf8_to_utf16_fix(std::as_const(input), &output);
}

TEST_MAIN
