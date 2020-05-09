//
// Created by ghost on 05.05.2020.
//

#ifndef INTERPRETER_INTERPRETER_H
#define INTERPRETER_INTERPRETER_H

#endif //INTERPRETER_INTERPRETER_H

#include <stack>
#include "flex.h"
#include "variable.h"
#include "parser.h"

#pragma once

class Interpreter
{
public:
    Interpreter(std::string input_file) : parser(input_file) {}

private:
    // second table
    Parser parser;
    std::stack<Context> stack;
};