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
hasNonWhiteChar(Line::const_iterator begin, Line::const_iterator end)
{
    return std::any_of(begin, end, [](const auto &character){
        return character != ' ' and character != '\t';});
}


void
insertLineAfterPosition(FileContent &content, Line &&line, FileContent::iterator pos)
{
    auto next_line_it = pos;
    next_line_it++;
    content.insert(next_line_it, line);
}

}


void
insertNewLineAfterChar(FileContent &content, char character)
{
    for (auto line_it = content.begin(); line_it != content.end(); line_it++) {
        auto &line = *line_it;

        auto semicolon_position = find(line.begin(), line.end(), character);
        if (semicolon_position != line.end()) {
            auto after_semicolon = semicolon_position;
            std::advance(after_semicolon, 1);

            if (hasNonWhiteChar(after_semicolon, line.end())) {
                auto pos = std::distance(line.begin(), after_semicolon);
                auto new_line = line.substr(pos);
                line.erase(after_semicolon, line.end());
                insertLineAfterPosition(content, std::move(new_line), line_it);
            }
        }
    }
}

}
