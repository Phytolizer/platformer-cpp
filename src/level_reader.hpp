//
// Created by Kyle Coffey on 12/24/2020.
//

#ifndef PLATFORMER_LEVEL_READER_HPP
#define PLATFORMER_LEVEL_READER_HPP

#include "level.hpp"
#include "level_file_structure.hpp"
#include "level_file_token.hpp"
#include <fstream>
#include <vector>

class LevelReader
{
    std::ifstream m_levelFile;
    std::string m_path;

  public:
    explicit LevelReader(std::string_view levelFileName);

    /// Please do not call this function multiple times on a single object. It will break things.
    std::vector<LevelFileToken> LexFile();
    LevelFileStructure ParseFile();
    Level EvaluateFile(const LevelFileStructure &structure);
};

#endif // PLATFORMER_LEVEL_READER_HPP
