/*
 * Copyright (c) 2023, Adam Chyła <adam@chyla.org>.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <formatter/detail/UpdateIndentation.hpp>

#include <gtest/gtest.h>


namespace
{

const std::set default_increase_indent_chars = {'{', '('};
const std::set default_decrease_indent_chars = {'}', ')'};
constexpr int default_num_of_spaces = 4;
constexpr bool default_reduce_indent_for_last_decrease_char = false;

const formatter::IndentationOptions baseTestsOptions
{
    default_increase_indent_chars,
    default_decrease_indent_chars,
    default_num_of_spaces,
    default_reduce_indent_for_last_decrease_char
};

}


struct UpdateIndentationTests : ::testing::Test
{
    UpdateIndentationTests() = default;
    virtual ~UpdateIndentationTests() = default;
};

TEST_F(UpdateIndentationTests, RemoveWhiteCharsFromWhiteLines)
{
    FileContent content {
        "     ",
        "  ",
    };

    formatter::detail::updateIndentation(content, baseTestsOptions);

    const FileContent expected_content {
        "",
        "",
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(UpdateIndentationTests, RemoveWhiteCharsFromBeginingOfLine)
{
    FileContent content {
        "     first_line();",
        "  second_line();",
    };

    formatter::detail::updateIndentation(content, baseTestsOptions);

    const FileContent expected_content {
        "first_line();",
        "second_line();",
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(UpdateIndentationTests, DoNotChangeWhenNoIndentChar)
{
    FileContent content {
        "first_line();",
        "second_line();",
        "third_line();"
    };

    formatter::detail::updateIndentation(content, baseTestsOptions);

    const FileContent expected_content {
        "first_line();",
        "second_line();",
        "third_line();"
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(UpdateIndentationTests, RemoveWhiteCharsFromWhiteLinesAfterIndentation)
{
    FileContent content {
        "     ",
        "  ",
        "  {",
        "     ",
        "  }",
        "   ",
    };

    formatter::detail::updateIndentation(content, baseTestsOptions);

    const FileContent expected_content {
        "",
        "",
        "{",
        "",
        "    }",
        "",
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(UpdateIndentationTests, ChangeWhenLinesWhichContainsInvalidIndentation)
{
    FileContent content {
        "     first_line();{",
        "  second_line();(",
        " third_line();)",
        "        fourth_line();"
    };

    formatter::detail::updateIndentation(content, baseTestsOptions);

    const FileContent expected_content {
        "first_line();{",
        "    second_line();(",
        "        third_line();)",
        "    fourth_line();"
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(UpdateIndentationTests, DoNotChangeWhenLineIsEmpty)
{
    FileContent content {
        "     first_line();{",
        "  second_line();(",
        "",
        " third_line();)",
        "        fourth_line();"
    };

    formatter::detail::updateIndentation(content, baseTestsOptions);

    const FileContent expected_content {
        "first_line();{",
        "    second_line();(",
        "",
        "        third_line();)",
        "    fourth_line();"
    };
    EXPECT_EQ(content, expected_content);
}


struct IncreaseIndentationTests : UpdateIndentationTests
{
};

TEST_F(IncreaseIndentationTests, UpdateNextLineAfterIndentChar)
{
    FileContent content {
        "first_line();{",
        "second_line();"
    };

    formatter::detail::updateIndentation(content, baseTestsOptions);

    const FileContent expected_content {
        "first_line();{",
        "    second_line();"
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(IncreaseIndentationTests, KeepIndentationForNextLinesAfterIndentChar)
{
    FileContent content {
        "first_line();{",
        "second_line();",
        "third_line();",
        "fourth_line();"
    };

    formatter::detail::updateIndentation(content, baseTestsOptions);

    const FileContent expected_content {
        "first_line();{",
        "    second_line();",
        "    third_line();",
        "    fourth_line();"
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(IncreaseIndentationTests, UpdateMultipleLinesAfterEachIndentChar)
{
    FileContent content {
        "first_line();{",
        "second_line();(",
        "third_line();",
        "fourth_line();"
    };

    formatter::detail::updateIndentation(content, baseTestsOptions);

    const FileContent expected_content {
        "first_line();{",
        "    second_line();(",
        "        third_line();",
        "        fourth_line();"
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(IncreaseIndentationTests, UpdateByTwoSpaces)
{
    formatter::IndentationOptions options = baseTestsOptions;
    options.num_of_spaces = 2;

    FileContent content {
        "first_line();{",
        "second_line();(",
        "third_line();",
        "fourth_line();"
    };

    formatter::detail::updateIndentation(content, options);

    const FileContent expected_content {
        "first_line();{",
        "  second_line();(",
        "    third_line();",
        "    fourth_line();"
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(IncreaseIndentationTests, ProgressiveIndentIsDisabled_UpdateByNumerOfIndentationChars)
{
    formatter::IndentationOptions options = baseTestsOptions;
    options.progressive_indent = false;

    FileContent content {
        "first_line();{{",
        "second_line();({{",
        "third_line();",
        "fourth_line();"
    };

    formatter::detail::updateIndentation(content, options);

    const FileContent expected_content {
        "first_line();{{",
        "        second_line();({{",
        "                    third_line();",
        "                    fourth_line();"
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(IncreaseIndentationTests, ProgressiveIndentIsEnabled_UpdateByStep)
{
    formatter::IndentationOptions options = baseTestsOptions;
    options.progressive_indent = true;

    FileContent content {
        "first_line();{{",
        "second_line();({{",
        "third_line();",
        "fourth_line();"
    };

    formatter::detail::updateIndentation(content, options);

    const FileContent expected_content {
        "first_line();{{",
        "    second_line();({{",
        "        third_line();",
        "        fourth_line();"
    };
    EXPECT_EQ(content, expected_content);
}

struct DecreaseIndentationTests : UpdateIndentationTests
{
};

TEST_F(DecreaseIndentationTests, UpdateNextLineAfterIndentChar)
{
    FileContent content {
        "first_line();{",
        "second_line();()}",
        "third_line();"
    };

    formatter::detail::updateIndentation(content, baseTestsOptions);

    const FileContent expected_content {
        "first_line();{",
        "    second_line();()}",
        "third_line();"
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(DecreaseIndentationTests, DoNotUpdateLinesOnMoreDescreaseChars)
{
    FileContent content {
        "first_line();}",
        "second_line();()}",
        "third_line();"
    };

    formatter::detail::updateIndentation(content, baseTestsOptions);

    const FileContent expected_content {
        "first_line();}",
        "second_line();()}",
        "third_line();"
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(DecreaseIndentationTests, UpdateByTwoSpaces)
{
    formatter::IndentationOptions options = baseTestsOptions;
    options.num_of_spaces = 2;

    FileContent content {
        "first_line();{",
        "second_line();{",
        "third_line();}",
        "fourth_line();}",
        "fifth_line();"
    };

    formatter::detail::updateIndentation(content, options);

    const FileContent expected_content {
        "first_line();{",
        "  second_line();{",
        "    third_line();}",
        "  fourth_line();}",
        "fifth_line();"
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(DecreaseIndentationTests, DoNotReduceIndentationForLastDecreaseChar)
{
    formatter::IndentationOptions options = baseTestsOptions;
    options.reduce_indent_for_last_decrease_char = false;

    FileContent content {
        "{",
        "{",
        "}",
        "}"
    };

    formatter::detail::updateIndentation(content, options);

    const FileContent expected_content {
        "{",
        "    {",
        "        }",
        "    }"
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(DecreaseIndentationTests, ReduceIndentationForLastDecreaseCharIsEnabled_DoNotUpdateLinesOnMoreDescreaseChars)
{
    formatter::IndentationOptions options = baseTestsOptions;
    options.reduce_indent_for_last_decrease_char = true;

    FileContent content {
        "}",
        "}"
    };

    formatter::detail::updateIndentation(content, options);

    const FileContent expected_content {
        "}",
        "}"
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(DecreaseIndentationTests, ReduceIndentationForLastDecreaseChar)
{
    formatter::IndentationOptions options = baseTestsOptions;
    options.reduce_indent_for_last_decrease_char = true;

    FileContent content {
        "{",
        "{",
        "}",
        "}"
    };

    formatter::detail::updateIndentation(content, options);

    const FileContent expected_content {
        "{",
        "    {",
        "    }",
        "}"
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(DecreaseIndentationTests, DoNotDoublyReduceIndentationForLastDecreaseChar)
{
    formatter::IndentationOptions options = baseTestsOptions;
    options.reduce_indent_for_last_decrease_char = true;

    FileContent content {
        "{",
        "{",
        "{",
        "}",
        "}",
        "}"
    };

    formatter::detail::updateIndentation(content, options);

    const FileContent expected_content {
        "{",
        "    {",
        "        {",
        "        }",
        "    }",
        "}"
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(DecreaseIndentationTests, ReduceIndentationForLastDecreaseCharWhenOthersCharsAfter)
{
    formatter::IndentationOptions options = baseTestsOptions;
    options.reduce_indent_for_last_decrease_char = true;

    FileContent content {
        "{",
        "{",
        "}sth",
        "}other"
    };

    formatter::detail::updateIndentation(content, options);

    const FileContent expected_content {
        "{",
        "    {",
        "    }sth",
        "}other"
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(DecreaseIndentationTests, ProgressiveIndentIsEnabledThenUpdateByStep)
{
    formatter::IndentationOptions options = baseTestsOptions;
    options.progressive_indent = true;

    FileContent content {
        "first_line();{{",
        "second_line();({{",
        "third_line();",
        "}})",
        "fourth_line();",
        "}}",
        "fifth_line();",
    };

    formatter::detail::updateIndentation(content, options);

    const FileContent expected_content {
        "first_line();{{",
        "    second_line();({{",
        "        third_line();",
        "        }})",
        "    fourth_line();",
        "    }}",
        "fifth_line();",
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(DecreaseIndentationTests, ProgressiveIndentIsEnabledWhenNotAllDecreaseIndentationChars_ThenDoNotUpdate)
{
    formatter::IndentationOptions options = baseTestsOptions;
    options.progressive_indent = true;

    FileContent content {
        "first_line();{{",
        "second_line();({{",
        "third_line();",
        "}",
        "fourth_line();",
        "})",
        "fifth_line();",
    };

    formatter::detail::updateIndentation(content, options);

    const FileContent expected_content {
        "first_line();{{",
        "    second_line();({{",
        "        third_line();",
        "        }",
        "        fourth_line();",
        "        })",
        "    fifth_line();",
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(DecreaseIndentationTests, ReduceIndentationForLastDecreaseCharWithProgressiveIndentIsEnabled_ThenUpdateByStep)
{
    formatter::IndentationOptions options = baseTestsOptions;
    options.reduce_indent_for_last_decrease_char = true;
    options.progressive_indent = true;

    FileContent content {
        "{{",
        "{{",
        "x",
        "}}",
        "}}"
    };

    formatter::detail::updateIndentation(content, options);

    const FileContent expected_content {
        "{{",
        "    {{",
        "        x",
        "    }}",
        "}}"
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(DecreaseIndentationTests, ReduceIndentationForLastDecreaseCharWithProgressiveIndentIsEnabled_WhenLastOneDecreaseCharThenReduceIndent)
{
    formatter::IndentationOptions options = baseTestsOptions;
    options.reduce_indent_for_last_decrease_char = true;
    options.progressive_indent = true;

    FileContent content {
        "{{",
        "{{{",
        "x",
        "}}",
        "}",
        "}}"
    };

    formatter::detail::updateIndentation(content, options);

    const FileContent expected_content {
        "{{",
        "    {{{",
        "        x",
        "        }}",
        "    }",
        "}}"
    };
    EXPECT_EQ(content, expected_content);
}

TEST_F(DecreaseIndentationTests, ReduceIndentationForLastDecreaseCharWithProgressiveIndentIsEnabled_WhenOtherTextBetweenDecreaseCharsThenDoNotReduceIndent)
{
    formatter::IndentationOptions options = baseTestsOptions;
    options.reduce_indent_for_last_decrease_char = true;
    options.progressive_indent = true;

    FileContent content {
        "{{",
        "{{{",
        "x",
        "}} sth }",
        "}}"
    };

    formatter::detail::updateIndentation(content, options);

    const FileContent expected_content {
        "{{",
        "    {{{",
        "        x",
        "        }} sth }",
        "}}"
    };
    EXPECT_EQ(content, expected_content);
}
