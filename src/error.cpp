//
// Created by kyle on 12/23/20.
//

#include "error.hpp"
Error::Error(std::string_view message) : std::runtime_error(message.data())
{
}

const char * Error::what() const noexcept
{
    return std::runtime_error::what();
}
