//
// Created by kyle on 12/23/20.
//

#pragma once

#include <stdexcept>
#include <string_view>

class Error : public std::runtime_error
{
  public:
    explicit Error(std::string_view message);
    [[nodiscard]] const char *what() const noexcept override;
};
