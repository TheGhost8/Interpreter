//
// Created by ghost on 05.05.2020.
//

#include <stack>
#include "flex.h"
#include "parser.h"
#include "data.h"

#pragma once

using OperationIndex = std::size_t;

class Interpreter
{
public:
    Interpreter(std::string input_file) : parser(input_file) {}

    void Execute();

private:
    Parser parser;
    Data::Context context;

    bool CheckValue(Type type);
};