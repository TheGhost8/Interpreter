//
// Created by ghost on 06.05.2020.
//

#include "operations.h"

OperationIndex Go::GetIndex() const
{
    return index;
}

Go::Go(OperationIndex new_index, Token::Type new_type) : Context(new_type)
{
    index = new_index;
}