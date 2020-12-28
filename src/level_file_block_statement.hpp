//
// Created by Kyle Coffey on 12/24/2020.
//

#ifndef PLATFORMER_LEVEL_FILE_BLOCK_STATEMENT_HPP
#define PLATFORMER_LEVEL_FILE_BLOCK_STATEMENT_HPP

#include "level_file_node.hpp"
#include <string>
class LevelFileBlockStatement : public LevelFileNode
{
    std::string name;
    int x;
    int y;
  public:
    LevelFileBlockStatement(std::string_view name, int x, int y) noexcept;
    [[nodiscard]] std::string Name() const noexcept;
    [[nodiscard]] int X() const noexcept;
    [[nodiscard]] int Y() const noexcept;
    [[nodiscard]] LevelFileNodeType Type() const noexcept override;
};

#endif // PLATFORMER_LEVEL_FILE_BLOCK_STATEMENT_HPP
