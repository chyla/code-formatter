/*
 * Copyright (c) 2023, Adam Chyła <adam@chyla.org>.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <formatter/detail/InsertNewLineAfterChar.hpp>

#include <algorithm>
#include <iterator>


namespace formatter::detail
{

namespace
{

bool
hasNonWhiteChar(const Line::const_iterator begin, const Line::const_iterator end)
{
    return std::any_of(begin, end, [](const auto &character){
        return character != ' ' and character != '\t';});
}


void
insertLineAfter(FileContent &content, Line &&line, FileContent::iterator current_line_it)
{
    auto &next_line_it = current_line_it;
    ++next_line_it;
    content.insert(next_line_it, line);
}

}


void
insertNewLineAfterChar(FileContent &content, char character)
{
    for (auto current_line_it = content.begin(); current_line_it != content.end(); ++current_line_it) {
        auto &current_line = *current_line_it;

        auto target_char_it = find(current_line.begin(), current_line.end(), character);
        if (target_char_it != current_line.end()) {
            auto after_target_char_it = target_char_it;
            std::advance(after_target_char_it, 1);

            if (hasNonWhiteChar(after_target_char_it, current_line.end())) {
                const auto split_pos = std::distance(current_line.begin(), after_target_char_it);
                auto new_line = current_line.substr(split_pos);
                current_line.erase(after_target_char_it, current_line.end());
                insertLineAfter(content, std::move(new_line), current_line_it);
            }
        }
    }
}

}
