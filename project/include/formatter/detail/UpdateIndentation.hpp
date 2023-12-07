/*
 * Copyright (c) 2023, Adam Chyła <adam@chyla.org>.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <FileContent.hpp>
#include "formatter/FormatterOptions.hpp"

#include <set>


namespace formatter::detail
{

void updateIndentation(FileContent &content,
                       const IndentationOptions &options);

}
