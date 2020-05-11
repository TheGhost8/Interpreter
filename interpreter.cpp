//
// Created by ghost on 05.05.2020.
//

#include "interpreter.h"

void Interpreter::Execute()
{
    parser.Start();
    while (context.operation_index < parser.commands.size())
    {
        parser.commands[context.operation_index]->Do(context);
        ++context.operation_index;
    }
}

bool Interpreter::CheckValue(Type type)
{
    return (type == TokenBoolean) || (type == TokenString) || (type == TokenInteger) || (type == TokenDouble);
}