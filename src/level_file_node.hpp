//
// Created by Kyle Coffey on 12/24/2020.
//

#ifndef PLATFORMER_LEVEL_FILE_NODE_HPP
#define PLATFORMER_LEVEL_FILE_NODE_HPP

enum class LevelFileNodeType
{
    name_statement,
    size_statement,
    blocks_delimiter,
    block_statement,
};

class LevelFileNode
{
  public:
    virtual LevelFileNodeType Type() const noexcept = 0;
};

#endif // PLATFORMER_LEVEL_FILE_NODE_HPP
