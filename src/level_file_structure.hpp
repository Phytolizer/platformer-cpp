//
// Created by Kyle Coffey on 12/24/2020.
//

#ifndef PLATFORMER_LEVEL_FILE_STRUCTURE_HPP
#define PLATFORMER_LEVEL_FILE_STRUCTURE_HPP

#include "level_file_node.hpp"
#include <memory>
#include <vector>

struct LevelFileStructure
{
    std::vector<std::unique_ptr<LevelFileNode>> Statements;
};

#endif // PLATFORMER_LEVEL_FILE_STRUCTURE_HPP
