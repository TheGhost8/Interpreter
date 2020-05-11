//
// Created by ghost on 03.05.2020.
//

#include <iostream>
#include <fstream>
#include <memory>
#include <unordered_map>
#include <vector>
#include "type_tables.h"

#pragma once

struct Token
{
    Type type;
    std::string lexem;
    u_int32_t  line;
};

class Flex
{
public:
    explicit Flex(std::string file);

    bool HasLexem();

    Token GetToken(u_int32_t* current_line);

private:

    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> transition_table;
    std::unordered_map<std::string, Type> all_types;
    std::ifstream input_file;

    void AddLetters(std::unordered_map<std::string, std::string>* map, std::string Destination);

    void AddNumbers(std::unordered_map<std::string, std::string>* map, std::string Destination);

    void AddSeparators(std::unordered_map<std::string, std::string>* map, std::string Destination);

    void AddSpaces(std::unordered_map<std::string, std::string>* map, std::string Destination);

    void FillDFA();

    void FillTypes(std::unordered_map<std::string, Type>* all_types);

    bool SpacesCheck(const std::string* str);

    bool ComparisonAssignmentCheck(std::string str);

    bool ASCIICheck(std::string str);

    void GetNextSymbol(std::string* str);

    void UngetNextSymbol(std::string* str);

    Token TakeToken();
};