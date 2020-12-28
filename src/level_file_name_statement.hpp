//
// Created by Kyle Coffey on 12/24/2020.
//

#ifndef PLATFORMER_LEVEL_FILE_NAME_STATEMENT_HPP
#define PLATFORMER_LEVEL_FILE_NAME_STATEMENT_HPP

#include "level_file_node.hpp"
#include <string>

class LevelFileNameStatement final : public LevelFileNode
{
    std::string name;

  public:
    explicit LevelFileNameStatement(std::string_view name) noexcept;
    [[nodiscard]] std::string Name() const noexcept;
    [[nodiscard]] LevelFileNodeType Type() const noexcept override;
};

#endif // PLATFORMER_LEVEL_FILE_NAME_STATEMENT_HPP
