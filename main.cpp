#include <iostream>
#include <fstream>
#include <unordered_map>
#include "flex.h"
#include "parser.h"
#include "interpreter.h"

int main(int argc, char* argv[])
{
    Interpreter interpreter(argv[1]);
    interpreter.Execute();
    return 0;
}
