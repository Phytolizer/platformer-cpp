//
// Created by Kyle Coffey on 12/24/2020.
//

#include "level_file_name_statement.hpp"
LevelFileNodeType LevelFileNameStatement::Type() const noexcept
{
    return LevelFileNodeType::name_statement;
}
LevelFileNameStatement::LevelFileNameStatement(std::string_view name) noexcept : name(name)
{
}
std::string LevelFileNameStatement::Name() const noexcept
{
    return name;
}
