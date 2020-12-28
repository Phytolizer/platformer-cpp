//
// Created by Kyle Coffey on 12/24/2020.
//

#ifndef PLATFORMER_LEVEL_FILE_TOKEN_HPP
#define PLATFORMER_LEVEL_FILE_TOKEN_HPP

#include <string>
enum class LevelFileTokenType
{
    bad,

    name_kw,
    size_kw,
    blocks_kw,

    colon,

    block_id,
    string,
    number,

    eof,
};

struct LevelFileToken
{
    LevelFileTokenType Type;
    std::string Text;
    int Line;
};

#endif // PLATFORMER_LEVEL_FILE_TOKEN_HPP
