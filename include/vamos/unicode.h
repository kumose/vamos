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
#pragma once

#include <string>
#include <vamos/unicode_view.h>
#include <optional>
#include <ostream>

namespace vamos {

    class Unicode {
    public:
        static constexpr bool _type_is_nullable = false;

    public:
        // data holder
        using value_type = char32_t;
        using container_type = std::basic_string<value_type>;
        using view_type = unicode_view;
        using size_type = view_type::size_type;

        static constexpr size_type npos = view_type::npos;
        // types
        using pointer = value_type *;
        using const_pointer = const value_type *;
        using reference = value_type &;
        using const_reference = const value_type &;
        using iterator = value_type *;
        using const_iterator = const value_type *;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using difference_type = std::ptrdiff_t;
        using traits_type = std::char_traits<value_type>;

    public:
        // Custom operator with string view
        operator view_type() const noexcept;

        [[nodiscard]] view_type view() const noexcept;

        // C++11 21.4.2 construct/copy/destroy
        Unicode() noexcept = default;

        Unicode(const Unicode &other) = default;

        Unicode(Unicode &&other) noexcept = default;

        Unicode(const Unicode &str, size_type pos, size_type n) : Unicode(str.view().substr(pos, n)) {
        }

        // TODO: add Unicode(const Unicode& str, size_type pos)

        explicit Unicode(const value_type *other) : Unicode(other, std::char_traits<value_type>::length(other)) {
        }

        Unicode(const value_type *other, size_type n) : data_(other, n) {
        }

        Unicode(size_type n, value_type c) : data_(n, c) {
        }

        template<typename IterType,
                typename = typename std::enable_if<!std::is_same<IterType, value_type *>::value>::type>
        Unicode(IterType first, IterType last) {
            size_type num = std::distance(first, last);
            this->reserve(num);
            while (first != last) {
                this->push_back(*first);
                ++first;
            }
        }

        // Specialization for const char*, const char*
        explicit Unicode(const value_type *b, const value_type *e) : data_(b, e - b) {
        }

        // Nonstandard constructor
        explicit Unicode(const container_type &other) : data_(other) {
        }

        explicit Unicode(container_type &&other) noexcept: data_(std::move(other)) {
        }

        explicit Unicode(const view_type &other) : data_(other.data(), other.size()) {
        }

        // Construction from initialization list
        Unicode(std::initializer_list<value_type> il) : Unicode(il.begin(), il.size()) {
        }

        // Copy assignment
        Unicode &operator=(const Unicode &other);

        // Move assignment
        Unicode &operator=(Unicode &&other) noexcept;

        Unicode &operator=(const value_type *other);

        Unicode &operator=(value_type other);

        Unicode &operator=(std::initializer_list<value_type> il);

        // Nonstandard assignment
        Unicode &operator=(view_type other) {
            assign(other);
            return *this;
        }

        // Compatibility with std::basic_string_view
        // clang-format off
        explicit operator std::basic_string_view<value_type, std::char_traits<value_type>>() const noexcept {
            return {data(), size()};
        }

        // C++11 21.4.3 iterators:
        iterator begin();

        [[nodiscard]] const_iterator begin() const noexcept;

        [[nodiscard]] const_iterator cbegin() const noexcept;

        iterator end();

        [[nodiscard]] const_iterator end() const noexcept;

        [[nodiscard]] const_iterator cend() const noexcept;

        reverse_iterator rbegin();

        [[nodiscard]] const_reverse_iterator rbegin() const noexcept;

        [[nodiscard]] const_reverse_iterator crbegin() const noexcept;

        reverse_iterator rend();

        [[nodiscard]] const_reverse_iterator rend() const noexcept;

        [[nodiscard]] const_reverse_iterator crend() const noexcept;

        // Added by C++11
        // C++11 21.4.5, element access:
        [[nodiscard]] const value_type &front() const noexcept;

        [[nodiscard]] const value_type &back() const noexcept;

        value_type &front();

        value_type &back();

        void pop_back();

        // C++11 21.4.4 capacity:
        [[nodiscard]] size_t size() const noexcept;

        void resize(size_type n, value_type c);

        void resize(size_type n);


        [[nodiscard]] size_t capacity() const noexcept;

        void reserve(size_type res_arg = 0);

        void clear();

        [[nodiscard]] bool empty() const noexcept;

        // C++11 21.4.5 element access:
        const_reference operator[](size_type pos) const noexcept;

        reference operator[](size_type pos);

        [[nodiscard]] const_reference at(size_type n) const;

        reference at(size_type n);

        // C++11 21.4.6 modifiers:
        Unicode &operator+=(value_type c);

        Unicode &operator+=(std::initializer_list<value_type> il);

        // Nonstandard alternative for:
        //   Unicode& operator+=(const Unicode& str);
        //   Unicode& operator+=(const value_type* s);
        Unicode &operator+=(view_type s);

        Unicode &append(view_type str);

        Unicode &append(const Unicode &str);

        Unicode &append(view_type str, size_type pos, size_type n);

        Unicode &append(size_type n, value_type c);

        template<class InputIterator>
        Unicode &append(InputIterator first, InputIterator last) {
            size_type num = std::distance(first, last);
            this->reserve(size() + num);
            while (first != last) {
                this->push_back(*first);
                ++first;
            }
            return *this;
        }

        Unicode &append(std::initializer_list<value_type> il) {
            return append(il.begin(), il.end());
        }

        void push_back(value_type c);  // primitive

        Unicode &assign(const Unicode &str);

        Unicode &assign(Unicode &&str);

        Unicode &assign(const Unicode &str, size_type pos, size_type n);

        Unicode &assign(const value_type *s, size_type n);

        Unicode &assign(const value_type *s);

        template<class ItOrLength, class ItOrChar>
        Unicode &assign(ItOrLength first_or_n, ItOrChar last_or_c) {
            return assign(Unicode(first_or_n, last_or_c));
        }

        // Nonstandard assignment:
        Unicode &assign(view_type sv);

        Unicode &assign(std::initializer_list<value_type> il) {
            return assign(il.begin(), il.size());
        }

        /// insert
        Unicode &insert(size_type pos1, const Unicode &str);

        Unicode &insert(size_type pos1, const Unicode &str, size_type pos2, size_type n);

        Unicode &insert(size_type pos, const value_type *s);

        Unicode &insert(size_type pos, const value_type *s, size_type n);

        Unicode &insert(size_type pos, size_type n, value_type c);

        Unicode &insert(size_type pos, view_type s);  // Nonstandard

        // TODO: insert by iterator

        Unicode &erase(size_type pos = 0, size_type n = npos);

        // TODO: erase by iterator

        // Replaces at most n1 chars of *this, starting with pos1 with the
        // content of s
        Unicode &replace(size_type pos1, size_type n1, view_type s);

        // Replaces at most n1 chars of *this, starting with pos1,
        // with at most n2 chars of s starting with pos2
        Unicode &replace(size_type pos1, size_type n1, view_type s, size_type pos2, size_type n2);

        // Replaces at most n1 chars of *this, starting with pos, with n2
        // occurrences of c
        //
        // consolidated with
        //
        // Replaces at most n1 chars of *this, starting with pos, with at
        // most n2 chars of str.  str must have at least n2 chars.
        Unicode &replace(size_type pos, size_type n1, view_type s, size_type n2);

        Unicode &replace(size_type pos, size_type n1, size_type n2, value_type c);

        // Just as what python does.
        [[nodiscard]] Unicode replace(view_type old_s, view_type new_s, int64_t count = -1) const;

        // TODO: replace by iterator

        // TODO: add copy

        // TODO: add swap

        [[nodiscard]] const value_type *c_str() const noexcept;

        [[nodiscard]] const value_type *data() const noexcept;

        [[nodiscard]] value_type *data() noexcept;

        [[nodiscard]] size_type find(view_type str, size_type pos = 0) const;

        [[nodiscard]] size_type find(value_type c, size_type pos = 0) const;

        [[nodiscard]] size_type rfind(view_type str, size_type pos = npos) const;

        [[nodiscard]] size_type rfind(value_type c, size_type pos = npos) const;

        [[nodiscard]] size_type find_first_of(view_type str, size_type pos = 0) const;

        [[nodiscard]] size_type find_first_of(value_type c, size_type pos = 0) const;

        [[nodiscard]] size_type find_last_of(view_type str, size_type pos = npos) const;

        [[nodiscard]] size_type find_last_of(value_type c, size_type pos = npos) const;

        [[nodiscard]] size_type find_first_not_of(view_type str, size_type pos = 0) const;

        [[nodiscard]] size_type find_first_not_of(value_type c, size_type pos = 0) const;

        [[nodiscard]] size_type find_last_not_of(view_type str, size_type pos = npos) const;

        [[nodiscard]] size_type find_last_not_of(value_type c, size_type pos = npos) const;

        // TODO: find by pointer

        [[nodiscard]] Unicode substr(size_type pos = 0, size_type n = npos) const;

        [[nodiscard]] int compare(const Unicode &other) const noexcept;

        /******************************************************************************
         * Nonstandard logical operator
         *****************************************************************************/
        inline bool operator==(view_type other) const noexcept {
            return view() == other;
        }

        inline bool operator==(const vamos::Unicode &rhs) const noexcept {
            return view() == rhs.view();
        }

        inline bool operator!=(view_type other) const noexcept {
            return view() != other;
        }

        inline bool operator<(view_type other) const noexcept {
            return view() < other;
        }

        inline bool operator>(view_type other) const noexcept {
            return view() > other;
        }

        inline bool operator<=(view_type other) const noexcept {
            return view() <= other;
        }

        inline bool operator>=(view_type other) const noexcept {
            return view() >= other;
        }

        // python methods
        [[nodiscard]] Unicode repeat(int64_t times) const;

        Unicode &repeat(int64_t times);

        [[nodiscard]] Unicode lower() const;

        [[nodiscard]] Unicode upper() const;

        [[nodiscard]] bool isdigit() const noexcept;

        [[nodiscard]] bool isalpha() const noexcept;

        [[nodiscard]] bool contains(view_type str) const noexcept;

        [[nodiscard]] std::optional<std::string> encode() const;

        static Unicode concat(view_type lhs, view_type rhs);

        static Unicode replace(view_type sv, view_type old_s, view_type new_s, int64_t count);

        static Unicode to_lower(view_type sv);

        static Unicode to_upper(view_type sv);

        static std::optional<Unicode> from_utf8(std::string_view utf8);

    private:

    private:
        container_type data_{};
    };

    // Overload + operator
    inline Unicode operator+(const Unicode &lhs, const Unicode &rhs) {
        return Unicode::concat(Unicode::view_type(lhs), Unicode::view_type(rhs));
    }

    inline Unicode operator+(const char32_t *lhs, const Unicode &rhs) {
        return Unicode::concat(Unicode::view_type(lhs), Unicode::view_type(rhs));
    }

    inline Unicode operator+(const Unicode &lhs, const char32_t *rhs) {
        return Unicode::concat(Unicode::view_type(lhs), Unicode::view_type(rhs));
    }

    inline Unicode operator+(const Unicode &lhs, const unicode_view &rhs) {
        return Unicode::concat(Unicode::view_type(lhs), rhs);
    }

    inline Unicode operator+(const unicode_view &lhs, const Unicode &rhs) {
        return Unicode::concat(lhs, Unicode::view_type(rhs));
    }

    inline Unicode operator+(const Unicode &lhs,
                             std::basic_string_view<Unicode::value_type, std::char_traits<Unicode::value_type>> rhs) {
        return Unicode::concat(Unicode::view_type(lhs), Unicode::view_type(rhs));
    }

    inline Unicode operator+(std::basic_string_view<Unicode::value_type, std::char_traits<Unicode::value_type>> lhs,
                             const Unicode &rhs) {
        return Unicode::concat(Unicode::view_type(lhs), Unicode::view_type(rhs));
    }

    std::ostream &operator<<(std::ostream &out, const Unicode &input);

}  // namespace vamos

namespace std {
    template<>
    struct hash<::vamos::Unicode> {
        std::size_t operator()(const ::vamos::Unicode &str) const noexcept {
            return std::hash<::vamos::unicode_view>()(str.view());
        }
    };

}  // namespace std
