//
// Created by Kyle Coffey on 12/24/2020.
//

#ifndef PLATFORMER_LEVEL_FILE_SIZE_STATEMENT_HPP
#define PLATFORMER_LEVEL_FILE_SIZE_STATEMENT_HPP

#include "level_file_node.hpp"
class LevelFileSizeStatement : public LevelFileNode
{
    int width;
    int height;
  public:
    LevelFileSizeStatement(int width, int height) noexcept;
    [[nodiscard]] int Width() const noexcept;
    [[nodiscard]] int Height() const noexcept;
    [[nodiscard]] LevelFileNodeType Type() const noexcept override;
};

#endif // PLATFORMER_LEVEL_FILE_SIZE_STATEMENT_HPP
