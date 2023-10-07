/*
 * Copyright (c) 2023, Adam Chyła <adam@chyla.org>.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <formatter/detail/InsertNewLineAfterChar.hpp>

#include <gtest/gtest.h>

namespace
{

constexpr char target = ';';

}


struct InsertNewLineAfterCharTests : ::testing::Test
{
    InsertNewLineAfterCharTests() = default;
    virtual ~InsertNewLineAfterCharTests() = default;
};


TEST_F(InsertNewLineAfterCharTests, ShouldNotInsertNewLineOnLineWithoutTarget)
{
    FileContent content {
        "first_line()"
    };

    formatter::detail::insertNewLineAfterChar(content, target);

    const FileContent expected_content {
        "first_line()",
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(InsertNewLineAfterCharTests, ShouldNotInsertNewLineOnLineWithTargetAsLastChar)
{
    FileContent content {
        "first_line();"
    };

    formatter::detail::insertNewLineAfterChar(content, target);

    const FileContent expected_content {
        "first_line();",
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(InsertNewLineAfterCharTests, ShouldNotInsertNewLineOnLineWithTargetAsLastCharBeforeSpaces)
{
    FileContent content {
        "first_line();   "
    };

    formatter::detail::insertNewLineAfterChar(content, target);

    const FileContent expected_content {
        "first_line();   ",
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(InsertNewLineAfterCharTests, ShouldNotInsertNewLineOnLineWithTargetAsLastCharBeforeTabs)
{
    FileContent content {
        "first_line();\t\t"
    };

    formatter::detail::insertNewLineAfterChar(content, target);

    const FileContent expected_content {
        "first_line();\t\t",
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(InsertNewLineAfterCharTests, InsertNewLineAfterTarget)
{
    FileContent content {
        "first_line();second_line()"
    };

    formatter::detail::insertNewLineAfterChar(content, target);

    const FileContent expected_content {
        "first_line();",
        "second_line()"
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(InsertNewLineAfterCharTests, InsertNewLineAfterTargetInTheMiddleOfTheFile)
{
    FileContent content {
        "first_line",
        "some_line();other_line()",
        "last_line"
    };

    formatter::detail::insertNewLineAfterChar(content, target);

    const FileContent expected_content {
        "first_line",
        "some_line();",
        "other_line()",
        "last_line"
    };
    EXPECT_EQ(content, expected_content);
}
