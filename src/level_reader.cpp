//
// Created by Kyle Coffey on 12/24/2020.
//

#include "level_reader.hpp"
#include "level_file_name_statement.hpp"
#include "level_file_size_statement.hpp"
#include <fmt/format.h>
#include <fstream>
#include <sstream>
LevelReader::LevelReader(const std::string_view levelFileName)
    : m_levelFile(levelFileName.data()), m_path(levelFileName)
{
}
static void ConsumeToken(LevelFileTokenType type, const std::vector<LevelFileToken> &tokens, int position)
{
    if (tokens[position].Type != type)
    {
        throw std::runtime_error{fmt::format("Invalid syntax: expected ':', found '{}'", tokens[position].Text)};
    }
}
static std::unique_ptr<LevelFileNameStatement> ParseNameStatement(const std::vector<LevelFileToken> &tokens,
                                                                  int *const position)
{
    ConsumeToken(LevelFileTokenType::colon, tokens, *position);
    ++(*position);
    ConsumeToken(LevelFileTokenType::string, tokens, *position);
    return std::make_unique<LevelFileNameStatement>(
        tokens[*position].Text.substr(1, tokens[*position].Text.length() - 2));
}
static std::unique_ptr<LevelFileSizeStatement> ParseSizeStatement(const std::vector<LevelFileToken> &tokens,
                                                                  int *const position)
{
    ConsumeToken(LevelFileTokenType::colon, tokens, *position);
    ++(*position);
}
static std::unique_ptr<LevelFileNode> ParseLevelFileStatement(const std::vector<LevelFileToken> &tokens, int position)
{
    LevelFileParser levelFileParser(tokens, position);
    switch (tokens[position].Type)
    {
    case LevelFileTokenType::name_kw:
        ++position;
        return ParseNameStatement(tokens, position);
    case LevelFileTokenType::size_kw:
        return ParseSizeStatement(tokens, position);
    case LevelFileTokenType::blocks_kw:
        return ParseBlocksStatement(tokens, position + 1);
    case LevelFileTokenType::block_id:
        return ParseBlockIdStatement(tokens, position + 1);
    default:
        throw std::runtime_error{
            fmt::format("Invalid syntax: expected [Name Size Blocks <BLOCK_ID>], found '{}'", tokens[position].Text)};
    }
}
LevelFileStructure LevelReader::ParseFile(const std::vector<LevelFileToken> &tokens)
{
    // TODO
    LevelFileStructure structure;
    int position = 0;
    while (tokens[position].Type != LevelFileTokenType::eof)
    {
        structure.Statements.push_back(ParseLevelFileStatement(tokens, position));
    }
    return structure;
}
static char GetChar(std::string_view text, int position)
{
    if (position >= text.length())
    {
        return '\0';
    }

    return text[position];
}
static std::string ReadFile(std::ifstream reader)
{
    std::ostringstream text;
    text << reader.rdbuf();
    return text.str();
}
static LevelFileTokenType CheckKeywordType(std::string_view tokenText)
{
    if (tokenText == "Name")
    {
        return LevelFileTokenType::name_kw;
    }
    if (tokenText == "Size")
    {
        return LevelFileTokenType::size_kw;
    }
    if (tokenText == "Blocks")
    {
        return LevelFileTokenType::blocks_kw;
    }
    return LevelFileTokenType::block_id;
}
std::vector<LevelFileToken> LevelReader::LexFile()
{
    std::vector<LevelFileToken> result;

    auto text = ReadFile(std::move(m_levelFile));

    int position = 0;
    LevelFileTokenType type = LevelFileTokenType::bad;
    int line = 1;
    while (GetChar(text, position) != '\0')
    {
        auto start = position;
        ++position;
        char c = text[position - 1];

        switch (c)
        {
        case ':':
            type = LevelFileTokenType::colon;
            break;
        case '"':
            while (GetChar(text, position) != '"')
            {
                auto s = GetChar(text, position);
                if (s == '\n')
                {
                    ++line;
                }
                if (s == '\0')
                {
                    throw std::runtime_error{
                        fmt::format("In file '{}', line {}: Unterminated string literal", m_path, line)};
                }
                ++position;
            }
            ++position;
            type = LevelFileTokenType::string;
            break;
        case ' ':
        case '\r':
        case '\t':
            continue;
        case '\n':
            ++line;
            continue;
        default:
            if (isalpha(c))
            {
                while (isalpha(GetChar(text, position)))
                {
                    ++position;
                }

                type = CheckKeywordType(text.substr(start, position - start));
            }
            break;
        }

        if (type == LevelFileTokenType::bad)
        {
            throw std::runtime_error{fmt::format("In file '{}', line {}: Unexpected character '{}'.", m_path, line,
                                                 text.substr(start, position - start))};
        }
        result.push_back(LevelFileToken{.Type = type, .Text = text.substr(start, position - start), .Line = line});
    }

    return result;
}
