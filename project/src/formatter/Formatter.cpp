/*
 * Copyright (c) 2023, Adam Chyła <adam@chyla.org>.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <formatter/Formatter.hpp>
#include <formatter/detail/InsertNewLineAfterChar.hpp>
#include <formatter/detail/UpdateIndentation.hpp>

namespace formatter
{

void
format(FileContent &content, const FormatterOptions &options)
{
    detail::insertNewLineAfterChar(content, ';');
    detail::updateIndentation(content, options.indentation);
}

}
