//
// Created by ghost on 06.05.2020.
//

#include "flex.h"

#ifndef INTERPRETER_CONTEXT_H
#define INTERPRETER_CONTEXT_H

#endif //INTERPRETER_CONTEXT_H

#pragma once

struct Context
{
public:
    explicit Context(Token::Type new_type = Token::TokenUndefined)
    {
        type = new_type;
    }

    Token::Type GetType() const;

private:
    Token::Type type;
    std::size_t operation_index = 0;
};