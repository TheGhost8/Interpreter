#include <iostream>
#include <fstream>
#include <unordered_map>
#include "flex.h"
#include "parser.h"

int main(int argc, char* argv[])
{
    /*std::unordered_map<std::string, std::unordered_map<std::string, std::string>> transition_table;

    std::unordered_map<std::string, Token::Type> all_types;

    std::ifstream input_file(argv[1]);*/
    /*Flex flex(argv[1]);
    int i = 1;
    Token token = flex.GetToken();
    while (token.type != Token::TokenEOF)
    {
        std::cout << i << ". " << token.lexem << "\n";
        i++;
        token = flex.GetToken();
    }*/
    Parser parser(argv[1]);
    parser.Start();
    parser.TestOutput();
    return 0;
}
