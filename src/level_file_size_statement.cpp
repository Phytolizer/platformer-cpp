//
// Created by Kyle Coffey on 12/24/2020.
//

#include "level_file_size_statement.hpp"
LevelFileSizeStatement::LevelFileSizeStatement(int width, int height) noexcept : width(width), height(height)
{
}
LevelFileNodeType LevelFileSizeStatement::Type() const noexcept
{
    return LevelFileNodeType::size_statement;
}
int LevelFileSizeStatement::Width() const noexcept
{
    return width;
}
int LevelFileSizeStatement::Height() const noexcept
{
    return height;
}
