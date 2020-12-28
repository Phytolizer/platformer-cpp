//
// Created by Kyle Coffey on 12/27/2020.
//

#ifndef PLATFORMER_LEVEL_FILE_PARSER_HPP
#define PLATFORMER_LEVEL_FILE_PARSER_HPP

#include "level_file_structure.hpp"
#include "level_file_token.hpp"
#include <vector>
class LevelFileParser
{
    std::vector<LevelFileToken> tokens;
    int position;

  public:
    explicit LevelFileParser(std::vector<LevelFileToken> &&tokens);
    [[nodiscard]] LevelFileStructure Parse();
};

#endif // PLATFORMER_LEVEL_FILE_PARSER_HPP
