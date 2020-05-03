#include <iostream>
#include <fstream>
#include <unordered_map>
#include "flex.h"

int main(int argc, char* argv[])
{
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> transition_table;
    FillDFA(&transition_table);
    std::unordered_map<std::string, Token::Type> all_types;
    FillTypes(&all_types);
    std::ifstream input_file(argv[1]);
    int i = 1;
    Token token;
    while (HasLexem(&input_file))
    {
        token = GetToken(&transition_table, &all_types, &input_file);
        std::cout << i << ". " << token.lexem << "\n";
        i++;
    }
    return 0;
}
