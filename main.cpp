#include <iostream>
#include <unordered_map>
#include "interpreter.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Error. Expected only filename.";
        return 1;
    }
    try
    {
        Interpreter interpreter(argv[1]);
        interpreter.Execute();
    }
    catch (const std::string exc)
    {
        std::cout << exc << std::endl;
        return 1;
    }
    return 0;
}
