//
// Created by ghost on 03.05.2020.
//

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

#ifndef INTERPRETER_FLEX_H
#define INTERPRETER_FLEX_H

#endif //INTERPRETER_FLEX_H

struct Token
{
    enum Type
    {
        TokenBooleanConst,
        TokenIntegerConst,
        TokenDoubleConst,
        TokenStringConst,
        TokenProgram,
        TokenBoolean,
        TokenInteger,
        TokenDouble,
        TokenString,
        TokenBegin,
        TokenEnd,
        TokenVar,
        TokenWriteln,
        TokenIf,
        TokenThen,
        TokenElse,
        TokenFor,
        TokenDo,
        TokenWhile,
// todo - перечислить остальные ключевые слова
        TokenSemicolon,
        TokenColon,
        TokenAssign,
        TokenMore,
        TokenLess,
        TokenEqual,
        TokenUnequal,
        TokenMoreOrEqual,
        TokenLessOrEqual,
        TokenPlus,
        TokenMinus,
        TokenLeftParenthesis,
        TokenRightParenthesis,
        TokenComma,
        TokenPoint,
        TokenLeftSquareBracket,
        TokenRightSquareBracket,
// todo - перечислить остальные разделители
        TokenIdentifier,
        TokenUndefined,
    };

    Type type;
    std::string lexem;
};

void AddLetters(std::unordered_map<std::string, std::string>* map, std::string Destination);

void AddNumbers(std::unordered_map<std::string, std::string>* map, std::string Destination);

void AddSeparators(std::unordered_map<std::string, std::string>* map, std::string Destination);

void AddSpaces(std::unordered_map<std::string, std::string>* map, std::string Destination);

void FillDFA(std::unordered_map<std::string, std::unordered_map<std::string, std::string>>* transition_table);

void FillTypes(std::unordered_map<std::string, Token::Type>* all_types);

bool SpacesCheck(const std::string* str);

bool ComparisonAssignmentCheck(std::string str);

bool ASCIICheck(std::string str);

void GetNextSymbol(std::ifstream* input_file, std::string* str);

void UngetNextSymbol(std::ifstream* input_file, std::string* str);

bool HasLexem(std::ifstream* input_file);

Token TakeToken(std::unordered_map<std::string, std::unordered_map<std::string, std::string>>* transition_table, std::unordered_map<std::string, Token::Type>* all_types, std::ifstream* input_file);

Token GetToken(std::unordered_map<std::string, std::unordered_map<std::string, std::string>>* transition_table, std::unordered_map<std::string, Token::Type>* all_types, std::ifstream* input_file);