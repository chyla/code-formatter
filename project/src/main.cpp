/*
 * Copyright (c) 2023, Adam Chyła <adam@chyla.org>.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <iostream>
#include <fstream>

#include <FileContent.hpp>
#include <formatter/Formatter.hpp>


namespace
{

FileContent readFile(const char *name)
{
    FileContent content;

    auto f = std::ifstream(name, std::ios::binary);
    f.exceptions(std::ifstream::failbit);

    Line line;
    char c;
    while (f.peek() != std::ifstream::traits_type::eof()) {
        f.get(c);
        if (c == '\n') {
            content.push_back(line);
            line.clear();
        }
        else {
            line.append(&c, 1);
        }
    }

    return content;
}

}


int main(int argc, char *argv[])
{
    const char *input_file = argv[1];

    auto file_content = readFile(input_file);

    formatter::FormatterOptions options;
    options.indentation.increase_indentation_chars = {'{', '('};
    options.indentation.decrease_indentation_chars = {'}', ')'} ;
    options.indentation.num_of_spaces = 4;
    options.indentation.reduce_indent_for_last_decrease_char = true;

    formatter::format(file_content, options);

    for (const auto &line : file_content) {
        std::cout << line << '\n';
    }

    return 0;
}
