#include <iostream>
#include <fstream>
#include <unordered_map>
#include "flex.h"
#include "parser.h"
#include "interpreter.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Error. Expected only filename.";
        exit(0);
    }
    Interpreter interpreter(argv[1]);
    interpreter.Execute();
    return 0;
}
