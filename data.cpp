//
// Created by ghost on 09.05.2020.
//

#include "data.h"

void Data::Error(std::string expected) const
{
    std::cout << "Expected: " << expected;
    exit(0);
}

Type Data::GetType() const
{
    return type;
}

void Data::Do(Context &context)
{
    Error("not to use do in plug");
}