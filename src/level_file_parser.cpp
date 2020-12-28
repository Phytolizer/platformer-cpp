//
// Created by Kyle Coffey on 12/27/2020.
//

#include "level_file_parser.hpp"
#include <fmt/format.h>
#include <sstream>

LevelFileToken LevelFileParser::Current() const noexcept
{
    return tokens[position];
}

void LevelFileParser::ConsumeToken(LevelFileTokenType expectedType)
{
    CheckToken(expectedType);
    ++position;
}

void LevelFileParser::CheckToken(LevelFileTokenType expectedType)
{
    if (Current().Type != expectedType) {
        throw std::runtime_error{fmt::format("Syntax error: did not expect '{}' on line {}", Current().Text, Current().Line)};
    }
}

std::unique_ptr<LevelFileNameStatement> LevelFileParser::ParseNameStatement()
{
    ConsumeToken(LevelFileTokenType::name_kw);
    ConsumeToken(LevelFileTokenType::colon);
    CheckToken(LevelFileTokenType::string);
    return std::make_unique<LevelFileNameStatement>(Current().Text.substr(1, Current().Text.length() - 2));
}

std::unique_ptr<LevelFileSizeStatement> LevelFileParser::ParseSizeStatement()
{
    ConsumeToken(LevelFileTokenType::size_kw);
    ConsumeToken(LevelFileTokenType::colon);
    CheckToken(LevelFileTokenType::number);
    std::stringstream ss;
    ss << Current().Text;
    int width;
    ss >> width;
    ++position;
    CheckToken(LevelFileTokenType::number);
    ss << Current().Text;
    int height;
    ss >> height;
    ++position;
    return std::make_unique<LevelFileSizeStatement>(width, height);
}

void LevelFileParser::ParseBlocksDelimiter()
{
    ConsumeToken(LevelFileTokenType::blocks_kw);
    ConsumeToken(LevelFileTokenType::colon);
}

std::unique_ptr<LevelFileBlockStatement> LevelFileParser::ParseBlockStatement()
{
    std::string blockId = Current().Text;
    ++position;
    CheckToken(LevelFileTokenType::number);
    std::stringstream ss;
    ss << Current().Text;
    int x;
    ss >> x;
    ++position;
    CheckToken(LevelFileTokenType::number);
    ss << Current().Text;
    int y;
    ss >> y;
    ++position;
    return std::make_unique<LevelFileBlockStatement>(blockId, x, y);
}

LevelFileParser::LevelFileParser(std::vector<LevelFileToken> &&tokens) : tokens(tokens), position(0) {}

LevelFileStructure LevelFileParser::Parse() {
    LevelFileStructure structure;
    bool parse = true;
    while (parse)
    {
        switch (Current().Type) {
            case LevelFileTokenType::eof:
                parse = false;
                break;
            case LevelFileTokenType::name_kw:
                structure.Statements.push_back(ParseNameStatement());
                ++position;
                break;
            case LevelFileTokenType::size_kw:
                structure.Statements.push_back(ParseSizeStatement());
                break;
            case LevelFileTokenType::blocks_kw:
                ParseBlocksDelimiter();
                break;
            case LevelFileTokenType::block_id:
                structure.Statements.push_back(ParseBlockStatement());
                break;
            default:
                throw std::runtime_error{fmt::format("Syntax error: expected one of [Name Size Blocks <BLOCK_ID>], found '{}'", Current().Text)};
        }
    }
}
