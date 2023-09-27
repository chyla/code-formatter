/*
 * Copyright (c) 2023, Adam Chyła <adam@chyla.org>.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "formatter/Formatter.hpp"

#include <gtest/gtest.h>


struct FormatterTests : ::testing::Test
{
    FormatterTests() = default;
    virtual ~FormatterTests() = default;
};


struct NewLineTests : FormatterTests
{
};

TEST_F(NewLineTests, ShouldNotInsertNewLineOnLineWithoutSemicolon)
{
    formatter::FileContent content {
        "first_line()"
    };

    formatter::format(content);

    const formatter::FileContent expected_content {
        "first_line()",
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(NewLineTests, ShouldNotInsertNewLineOnLineWithSemicolonAsLastChar)
{
    formatter::FileContent content {
        "first_line();"
    };

    formatter::format(content);

    const formatter::FileContent expected_content {
        "first_line();",
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(NewLineTests, ShouldNotInsertNewLineOnLineWithSemicolonAsLastCharBeforeSpaces)
{
    formatter::FileContent content {
        "first_line();   "
    };

    formatter::format(content);

    const formatter::FileContent expected_content {
        "first_line();   ",
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(NewLineTests, ShouldNotInsertNewLineOnLineWithSemicolonAsLastCharBeforeTabs)
{
    formatter::FileContent content {
        "first_line();\t\t"
    };

    formatter::format(content);

    const formatter::FileContent expected_content {
        "first_line();\t\t",
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(NewLineTests, InsertNewLineAfterSemicolon)
{
    formatter::FileContent content {
        "first_line();second_line()"
    };

    formatter::format(content);

    const formatter::FileContent expected_content {
        "first_line();",
        "second_line()"
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(NewLineTests, InsertNewLineAfterSemicolonInTheMiddleOfTheFile)
{
    formatter::FileContent content {
        "first_line",
        "some_line();other_line()",
        "last_line"
    };

    formatter::format(content);

    const formatter::FileContent expected_content {
        "first_line",
        "some_line();",
        "other_line()",
        "last_line"
    };
    EXPECT_EQ(content, expected_content);
}
