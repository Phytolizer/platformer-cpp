//
// Created by Kyle Coffey on 12/24/2020.
//

#include "level_file_block_statement.hpp"
LevelFileBlockStatement::LevelFileBlockStatement(std::string_view name, int x, int y) noexcept : name(name), x(x), y(y)
{
}
std::string LevelFileBlockStatement::Name() const noexcept
{
    return name;
}
int LevelFileBlockStatement::X() const noexcept
{
    return x;
}
int LevelFileBlockStatement::Y() const noexcept
{
    return y;
}
LevelFileNodeType LevelFileBlockStatement::Type() const noexcept
{
    return LevelFileNodeType::block_statement;
}
