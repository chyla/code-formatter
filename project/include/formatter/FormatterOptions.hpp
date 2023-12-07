/*
 * Copyright (c) 2023, Adam Chyła <adam@chyla.org>.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <set>


namespace formatter
{

struct IndentationOptions
{
    std::set<char> increase_indentation_chars;
    std::set<char> decrease_indentation_chars;
    int num_of_spaces {0};
    bool reduce_indent_for_last_decrease_char {false};
    bool progressive_indent {false};
};

struct FormatterOptions
{
    IndentationOptions indentation;
};

}
