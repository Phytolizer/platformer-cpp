//
// Created by Kyle Coffey on 12/27/2020.
//

#ifndef PLATFORMER_LEVEL_FILE_PARSER_HPP
#define PLATFORMER_LEVEL_FILE_PARSER_HPP

#include "level_file_structure.hpp"
#include "level_file_token.hpp"
#include "level_file_name_statement.hpp"
#include "level_file_size_statement.hpp"
#include "level_file_block_statement.hpp"
#include <vector>
class LevelFileParser
{
    std::vector<LevelFileToken> tokens;
    int position;

    LevelFileToken Current() const noexcept;
    void ConsumeToken(LevelFileTokenType expectedType);
    void CheckToken(LevelFileTokenType expectedType);

    std::unique_ptr<LevelFileNameStatement> ParseNameStatement();
    std::unique_ptr<LevelFileSizeStatement> ParseSizeStatement();
    void ParseBlocksDelimiter();
    std::unique_ptr<LevelFileBlockStatement> ParseBlockStatement();

  public:
    explicit LevelFileParser(std::vector<LevelFileToken> &&tokens);
    [[nodiscard]] LevelFileStructure Parse();
};

#endif // PLATFORMER_LEVEL_FILE_PARSER_HPP
