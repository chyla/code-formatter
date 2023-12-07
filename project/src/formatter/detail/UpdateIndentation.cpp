/*
 * Copyright (c) 2023, Adam Chyła <adam@chyla.org>.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <formatter/detail/UpdateIndentation.hpp>

#include <algorithm>
#include <numeric>
#include <string_view>
#include <vector>

using NumberOfIndentationChars = long;
using IndentationParts = std::vector<NumberOfIndentationChars>;


namespace
{

void
lstrip(Line &line)
{
    line.erase(line.begin(),
               std::find_if_not(line.begin(), line.end(), is_white_char));
}


void
increase_indent(IndentationParts &indentation_parts, const NumberOfIndentationChars to_increase)
{
    indentation_parts.push_back(to_increase);
}


void
decrease_indent(IndentationParts &indentation_parts, NumberOfIndentationChars to_reduce)
{
    while (to_reduce > 0 and not indentation_parts.empty()) {
        auto current = indentation_parts.back();
        indentation_parts.pop_back();

        if (to_reduce > current) {
            to_reduce = to_reduce - current;
            current = 0;
        }
        else {
            current = current - to_reduce;
            to_reduce = 0;
        }

        if (current > 0) {
            indentation_parts.push_back(current);
        }
    }
}


unsigned
indentation_level(const IndentationParts &indentation_parts, const formatter::IndentationOptions &options)
{
    if (options.progressive_indent) {
        return indentation_parts.size();
    }
    else {
        return std::accumulate(indentation_parts.begin(),
                               indentation_parts.end(),
                               0);
    }
}

}

namespace formatter::detail
{

void
updateIndentation(FileContent &content,
                  const IndentationOptions &options)
{
    IndentationParts indentation_parts;

    for (auto &line : content) {
        lstrip(line);

        const bool decrease_indent_before_line_content =
            options.reduce_indent_for_last_decrease_char
            and line.length() > 0
            and options.decrease_indentation_chars.find(line.at(0)) != options.decrease_indentation_chars.end();

        unsigned already_analyzed = 0;
        if (decrease_indent_before_line_content) {
            const auto first_non_decrease_indentation_char = std::find_if_not(line.cbegin(), line.cend(), [&](char c){
                return options.decrease_indentation_chars.find(c) != options.decrease_indentation_chars.end();
            });
            const auto indentation_chars = std::distance(line.cbegin(), first_non_decrease_indentation_char);
            already_analyzed = indentation_chars;

            decrease_indent(indentation_parts, indentation_chars);
        }

        if (line.length() > 0) {
            constexpr char indentation_char = ' ';

            const auto num_of_chars_to_insert =
                indentation_level(indentation_parts, options) * options.num_of_spaces;
            line.insert(0, num_of_chars_to_insert, indentation_char);
            already_analyzed += num_of_chars_to_insert;
        }

        NumberOfIndentationChars indentation_chars = 0;
        for (auto it = std::next(line.cbegin(), already_analyzed); it != line.cend(); ++it) {
            if (options.increase_indentation_chars.find(*it) != options.increase_indentation_chars.end()) {
                ++indentation_chars;
            }
            if (options.decrease_indentation_chars.find(*it) != options.decrease_indentation_chars.end()) {
                --indentation_chars;
            }
        }

        if (indentation_chars > 0) {
            increase_indent(indentation_parts, indentation_chars);
        }
        else if (indentation_chars < 0) {
            decrease_indent(indentation_parts, abs(indentation_chars));
        }
    }
}

}
