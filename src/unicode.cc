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
#include <initializer_list>

namespace vamos {

    const typename Unicode::size_type Unicode::npos;

    Unicode Unicode::concat(view_type lhs, view_type rhs) {
        Unicode ret;
        size_type lhs_size = lhs.size();
        size_type rhs_size = rhs.size();
        ret.reserve(lhs_size + rhs_size);
        ret.append(lhs);
        ret.append(rhs);
        return ret;
    }

    // default constructors
    Unicode &Unicode::operator=(const Unicode &other) {
        if (vamos_unlikely(&other == this)) {
            return *this;
        }
        assign(other.data_.data(), other.data_.size());
        return *this;
    }

    Unicode &Unicode::operator=(Unicode &&other) noexcept {
        if (vamos_unlikely(&other == this)) {
            // Compatibility with std::basic_string<>,
            // C++11 21.4.2 [string.cons] / 23 requires self-move-assignment support.
            return *this;
        }
        // No need of this anymore
        this->~Unicode();
        // Move the goner into this
        new(&data_) container_type(std::move(other.data_));
        return *this;
    }

    Unicode &Unicode::operator=(const value_type *other) {
        if (other) {
            assign(other, std::char_traits<value_type>::length(other));
        }
        return *this;
    }

    Unicode &Unicode::operator=(value_type other) {
        *this = Unicode(1, other);
        return *this;
    }

    Unicode &Unicode::operator=(std::initializer_list<value_type> il) {
        assign(il.begin(), il.size());
        return *this;
    }

    typename Unicode::iterator Unicode::Unicode::begin() {
        return data_.data();
    }

    typename Unicode::const_iterator Unicode::Unicode::begin() const noexcept {
        return data_.data();
    }

    typename Unicode::const_iterator Unicode::Unicode::cbegin() const noexcept {
        return data_.data();
    }

    typename Unicode::iterator Unicode::Unicode::end() {
        return data_.data() + data_.size();
    }

    typename Unicode::const_iterator Unicode::Unicode::end() const noexcept {
        return data_.data() + data_.size();
    }

    typename Unicode::const_iterator Unicode::Unicode::cend() const noexcept {
        return data_.data() + data_.size();
    }

    typename Unicode::reverse_iterator Unicode::Unicode::rbegin() {
        return reverse_iterator(end());
    }

    typename Unicode::const_reverse_iterator Unicode::Unicode::rbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    typename Unicode::const_reverse_iterator Unicode::Unicode::crbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    typename Unicode::reverse_iterator Unicode::Unicode::rend() {
        return reverse_iterator(begin());
    }

    typename Unicode::const_reverse_iterator Unicode::Unicode::rend() const noexcept {
        return const_reverse_iterator(begin());
    }

    typename Unicode::const_reverse_iterator Unicode::Unicode::crend() const noexcept {
        return const_reverse_iterator(begin());
    }

    const Unicode::value_type &Unicode::front() const noexcept {
        return view().front();
    }

    const Unicode::value_type &Unicode::back() const noexcept {
        return view().back();
    }

    Unicode::value_type &Unicode::front() {
        return *(data_.data());
    }

    Unicode::value_type &Unicode::back() {
        return *(data_.data() + data_.size() - 1);
    }

    void Unicode::pop_back() {
        assert(!empty());
        data_.pop_back();
    }

    size_t Unicode::size() const noexcept {
        return view().size();
    }

    void Unicode::resize(size_type n, value_type c) {
        data_.resize(n, c);
    }

    void Unicode::resize(size_type n) {
        data_.resize(n, '\0');
    }

    size_t Unicode::capacity() const noexcept {
        return data_.capacity();
    }

    void Unicode::reserve(size_type res_arg) {
        data_.reserve(res_arg);
    }

    void Unicode::clear() {
        data_.clear();
    }

    bool Unicode::empty() const noexcept {
        return data_.empty();
    }

    const Unicode::value_type &Unicode::operator[](size_type pos) const noexcept {
        return view().operator[](pos);
    }

    Unicode::value_type &Unicode::operator[](size_type pos) {
        return *(data_.data() + pos);
    }

    const Unicode::value_type &Unicode::at(size_type n) const {
        if (n >= size()) {
            throw std::out_of_range("Unicode: index out of range");
        }
        return *(data_.data() + n);
    }


    Unicode::value_type &Unicode::at(size_type n) {
        if (n >= size()) {
            throw std::out_of_range("Unicode: index out of range");
        }
        return *(data_.data() + n);
    }

    Unicode &Unicode::operator+=(value_type c) {
        push_back(c);
        return *this;
    }


    Unicode &Unicode::operator+=(std::initializer_list<value_type> il) {
        append(il);
        return *this;
    }

    Unicode &Unicode::operator+=(view_type s) {
        return append(s);
    }

    Unicode &Unicode::append(view_type str) {
        auto s = str.data();
        auto n = str.size();

        if (vamos_unlikely(!n)) {
            // Unlikely but must be done
            return *this;
        }
        data_.append(s, n);
        return *this;
    }

    Unicode &Unicode::append(const Unicode &str) {
        return append(str.view());
    }

    Unicode &Unicode::append(view_type str, size_type pos, size_type n) {
        return append(str.substr(pos, n));
    }

    Unicode &Unicode::append(size_type n, value_type c) {
        data_.append(n, c);
        return *this;
    }

    void Unicode::push_back(value_type c) {
        data_.push_back(c);
    }

    Unicode &Unicode::assign(const Unicode &str) {
        if (vamos_unlikely(&str == this)) {
            return *this;
        }
        assign(str.data_.data(), str.data_.size());
        return *this;
    }

    Unicode &Unicode::assign(Unicode &&str) {
        return *this = std::move(str);
    }

    Unicode &Unicode::assign(const Unicode &str, size_type pos, size_type n) {
        auto sub_view = str.view().substr(pos, n);
        assign(sub_view.data(), sub_view.size());
        return *this;
    }

    Unicode &Unicode::assign(const value_type *s, size_type n) {
        data_.assign(s, n);
        return *this;
    }

    Unicode &Unicode::assign(const value_type *s) {
        if (s) {
            assign(s, std::char_traits<value_type>::length(s));
        }
        return *this;
    }

    Unicode &Unicode::assign(view_type s) {
        data_.assign(s.data(), s.size());
        return assign(s.data(), s.size());
    }

    Unicode &Unicode::insert(size_type pos1, const Unicode &str) {
        return insert(pos1, str.view());
    }

    Unicode &Unicode::insert(size_type pos1, const Unicode &str, size_type pos2, size_type n) {
        return insert(pos1, str.view().substr(pos2, n));
    }

    Unicode &Unicode::insert(size_type pos, const value_type *s) {
        return insert(pos, view_type(s));
    }

    Unicode &Unicode::insert(size_type pos, const value_type *s, size_type n) {
        return insert(pos, view_type(s, n));
    }

    Unicode &Unicode::insert(size_type pos, size_type n, value_type c) {
        data_.insert(pos, n, c);
        return *this;
    }

    Unicode &Unicode::insert(size_type pos, view_type s) {
        data_.insert(pos, s.data(), s.size());
        return *this;
    }


    Unicode &Unicode::erase(size_type pos, size_type n) {
        if (pos > size()) {
            throw std::out_of_range("Unicode: index out of range");
        }
        n = std::min(n, size_type(size()) - pos);
        std::copy(begin() + pos + n, end(), begin() + pos);
        resize(size() - n);
        return *this;
    }

    Unicode &Unicode::replace(size_type pos, size_type n1, view_type s) {
        size_t len = size();
        if (pos > len) {
            throw std::out_of_range("Unicode: index out of range");
        }
        n1 = std::min(n1, len - pos);
        Unicode temp;
        temp.reserve(len - n1 + s.size());
        temp.append(substr(0, pos)).append(s).append(substr(pos + n1));
        *this = std::move(temp);
        return *this;
    }

    Unicode &Unicode::replace(size_type pos1, size_type n1, view_type s, size_type pos2, size_type n2) {
        return replace(pos1, n1, s.substr(pos2, n2));;
    }

    Unicode &Unicode::replace(size_type pos, size_type n1, view_type s, size_type n2) {
        return replace(pos, n1, s.substr(0, n2));
    }

    Unicode &Unicode::replace(size_type pos, size_type n1, size_type n2, value_type c) {
        Unicode temp;
        temp.reserve(size() - n1 + size());
        temp.append(substr(0, pos)).append(n2, c).append(substr(pos + n1));
        *this = std::move(temp);
        return *this;
    }

    Unicode Unicode::replace(view_type sv, view_type old_s, view_type new_s, int64_t count) {
        if (count < 0) {
            count = std::numeric_limits<int64_t>::max();
        }
        Unicode ret;
        // What's the proper value of the capacity?
        if (new_s.length() > old_s.length()) {
            ret.reserve(static_cast<size_t>(sv.size() * 1.5));
        } else {
            ret.reserve(sv.size());
        }
        size_type current = 0, next;
        while ((next = sv.find(old_s, current)) != npos && count > 0) {
            ret.append(view_type(sv.data() + current, next - current));
            ret.append(new_s);
            current = next + old_s.size();
            --count;
        }
        ret.append(view_type(sv.data() + current, sv.size() - current));
        return ret;
    }

    Unicode Unicode::replace(view_type old_s, view_type new_s, int64_t count) const {
        return replace(view(), old_s, new_s, count);
    }

    const Unicode::value_type *Unicode::c_str() const noexcept {
        return data_.c_str();
    }

    const Unicode::value_type *Unicode::data() const noexcept {
        return data_.data();
    }

    Unicode::value_type *Unicode::data() noexcept {
        return data_.data();
    }

    Unicode::size_type Unicode::find(view_type str, size_type pos) const {
        return view().find(str, pos);
    }

    Unicode::size_type Unicode::find(value_type c, size_type pos) const {
        return view().find(c, pos);
    }

    Unicode::size_type Unicode::rfind(view_type str, size_type pos) const {
        return view().rfind(str, pos);
    }

    Unicode::size_type Unicode::rfind(value_type c, size_type pos) const {
        return view().rfind(c, pos);
    }

    Unicode::size_type Unicode::find_first_of(view_type str, size_type pos) const {
        return view().find_first_of(str, pos);
    }

    Unicode::size_type Unicode::find_first_of(value_type c, size_type pos) const {
        return view().find_first_of(c, pos);
    }

    Unicode::size_type Unicode::find_last_of(view_type str, size_type pos) const {
        return view().find_last_of(str, pos);
    }

    Unicode::size_type Unicode::find_last_of(value_type c, size_type pos) const {
        return view().find_last_of(c, pos);
    }


    Unicode::size_type Unicode::find_first_not_of(view_type str, size_type pos) const {
        return view().find_first_not_of(str, pos);
    }

    Unicode::size_type Unicode::find_first_not_of(value_type c, size_type pos) const {
        return view().find_first_not_of(c, pos);
    }

    Unicode::size_type Unicode::find_last_not_of(view_type str, size_type pos) const {
        return view().find_last_not_of(str, pos);
    }

    Unicode::size_type Unicode::find_last_not_of(value_type c, size_type pos) const {
        return view().find_last_not_of(c, pos);
    }

    Unicode Unicode::substr(size_type pos, size_type n) const {
        return Unicode(view().substr(pos, n));
    }

    int Unicode::compare(const Unicode &other) const noexcept {
        return view().compare(other.view());
    }

    Unicode Unicode::repeat(int64_t times) const {
        auto sv = view();
        times = vamos_unlikely(times < 0) ? 0 : times;
        auto result_size = times * sv.length();
        Unicode::container_type store;
        store.resize(result_size);
        auto *data = (Unicode::pointer) store.data();
        auto *src_data = sv.data();
        auto src_size = sv.size();
        for (int64_t i = 0; i < times; ++i) {
            Unicode::traits_type::copy(data, src_data, src_size);
            data += src_size;
        }
        return Unicode(std::move(store));
    }

    Unicode &Unicode::repeat(int64_t times) {

        auto sv = view();
        times = vamos_unlikely(times < 0) ? 0 : times;
        auto result_size = times * sv.length();
        Unicode::container_type store;
        store.resize(result_size);
        auto *data = (Unicode::pointer) store.data();
        auto *src_data = sv.data();
        auto src_size = sv.size();
        for (int64_t i = 0; i < times; ++i) {
            Unicode::traits_type::copy(data, src_data, src_size);
            data += src_size;
        }
        data_ = std::move(store);
        return *this;
    }

    Unicode Unicode::lower() const {
        return to_lower(view());
    }

    Unicode Unicode::upper() const {
        return to_upper(view());
    }


    Unicode Unicode::to_lower(view_type input) {
        return unicode::ops_unicode_do_lower_optimize(input);
    }

    Unicode Unicode::to_upper(view_type sv) {
        return unicode::ops_unicode_do_upper_optimize(sv);
    }

    bool Unicode::isdigit() const noexcept {
        return unicode::ops_unicode_isdigit(view());
    }

    bool Unicode::isalpha() const noexcept {
        return unicode::ops_unicode_isalpha(view());
    }

    std::ostream &operator<<(std::ostream &out, const Unicode &input) {
        std::string str;
        auto s = convert_utf32_to_utf8(input.view(), &str);
        (void)s;
        out.write(str.data(), str.size());
        return out;
    }

    bool Unicode::contains(view_type str) const noexcept {
        return view().find(str) != npos;
    }

    [[nodiscard]] std::optional<std::string> Unicode::encode() const {
        std::string store;
        auto rs = convert_utf32_to_utf8_with_errors(view(), &store);
        if(!rs.is_ok()) {
            return std::nullopt;
        }
        return store;
    }

    std::optional<Unicode> Unicode::from_utf8(std::string_view utf8) {
        Unicode::container_type store;
        auto rs = convert_utf8_to_utf32_with_errors(utf8, &store);
        if(!rs.is_ok()) {
            return std::nullopt;
        }
        Unicode result(std::move(store));
        return result;
    }

    ///anchor
    /******************************************************************************
     * Unicode container
     *****************************************************************************/



    Unicode::operator view_type() const noexcept {
        return view_type{data_.data(), data_.size()};
    }

    Unicode::view_type Unicode::view() const noexcept {
        return view_type{data_.data(), data_.size()};
    }

}  // namespace vamos
