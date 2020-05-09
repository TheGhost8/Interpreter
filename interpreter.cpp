//
// Created by ghost on 05.05.2020.
//

#include "interpreter.h"

void Interpreter::Execute()
{
    parser.Start();
    while (program_stack.operation_index < parser.commands.size())
    {
        if (CheckValue(parser.commands[program_stack.operation_index]->GetType()))
        {
            program_stack.stack.emplace(parser.commands[program_stack.operation_index]);
        }
        else
        {
            parser.commands[program_stack.operation_index]->Do(program_stack);
        }
        ++program_stack.operation_index;
    }
}

bool Interpreter::CheckValue(Type type)
{
    return (type == TokenBoolean) || (type == TokenString) || (type == TokenInteger) || (type == TokenDouble);
}