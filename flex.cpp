//
// Created by ghost on 03.05.2020.
//

#include "flex.h"

void AddLetters(std::unordered_map<std::string, std::string>* map, const std::string Destination)
{
    int shift = 'A' - 'a';
    for (char i = 'a'; i <= 'z'; i++)
    {
        map->insert(std::pair<std::string, std::string>(std::string(1, i), Destination));
        map->insert(std::pair<std::string, std::string>(std::string(1, i + shift), Destination));
    }
}

void AddNumbers(std::unordered_map<std::string, std::string>* map, const std::string Destination)
{
    for (char i = '0'; i <= '9'; i++)
    {
        map->insert(std::pair<std::string, std::string>(std::string(1, i), Destination));
    }
}

void AddSeparators(std::unordered_map<std::string, std::string>* map, const std::string Destination)
{
    map->insert(std::pair<std::string, std::string>(":", Destination));
    map->insert(std::pair<std::string, std::string>(";", Destination));
    map->insert(std::pair<std::string, std::string>("=", Destination));
    map->insert(std::pair<std::string, std::string>(">", Destination));
    map->insert(std::pair<std::string, std::string>("<", Destination));
    map->insert(std::pair<std::string, std::string>(">=", Destination));
    map->insert(std::pair<std::string, std::string>("<=", Destination));
    map->insert(std::pair<std::string, std::string>("==", Destination));
    map->insert(std::pair<std::string, std::string>(":=", Destination));
    map->insert(std::pair<std::string, std::string>("<>", Destination));
    map->insert(std::pair<std::string, std::string>("-", Destination));
    map->insert(std::pair<std::string, std::string>("+", Destination));
    map->insert(std::pair<std::string, std::string>("(", Destination));
    map->insert(std::pair<std::string, std::string>(")", Destination));
    map->insert(std::pair<std::string, std::string>("[", Destination));
    map->insert(std::pair<std::string, std::string>("]", Destination));
    map->insert(std::pair<std::string, std::string>(".", Destination));
    map->insert(std::pair<std::string, std::string>(",", Destination));
}

void AddSpaces(std::unordered_map<std::string, std::string>* map, const std::string Destination)
{
    map->insert(std::pair<std::string, std::string>(" ", Destination));
    map->insert(std::pair<std::string, std::string>("\t", Destination));
    map->insert(std::pair<std::string, std::string>("\r", Destination));
    map->insert(std::pair<std::string, std::string>("\n", Destination));
}

void FillDFA(std::unordered_map<std::string, std::unordered_map<std::string, std::string>>* transition_table)
{
    std::unordered_map<std::string, std::string> mask;
    AddLetters(&mask, "Text");
    AddNumbers(&mask, "Integer");
    mask.insert(std::pair<std::string, std::string>("_", "Text"));
    mask.insert(std::pair<std::string, std::string>("'", "Quote"));
    mask.insert(std::pair<std::string, std::string>("{", "Comment"));
    AddSeparators(&mask, "Start");
    AddSpaces(&mask, "Start");
    transition_table->insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Start", mask));

    mask.clear();
    AddLetters(&mask, "Text");
    AddNumbers(&mask, "Text");
    mask.insert(std::pair<std::string, std::string>("_", "Text"));
    AddSeparators(&mask, "Start");
    AddSpaces(&mask, "Start");
    transition_table->insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Text", mask));

    mask.clear();
    mask.insert(std::pair<std::string, std::string>("'", "EndQuote"));
    transition_table->insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Quote", mask));

    mask.clear();
    mask.insert(std::pair<std::string, std::string>("'", "Quote"));
    AddSeparators(&mask, "Start");
    AddSpaces(&mask, "Start");
    transition_table->insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("EndQuote", mask));

    mask.clear();
    mask.insert(std::pair<std::string, std::string>("}", "Start"));
    transition_table->insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Comment", mask));

    mask.clear();
    AddNumbers(&mask, "Integer");
    mask.insert(std::pair<std::string, std::string>(".", "Double"));
    mask.insert(std::pair<std::string, std::string>("E", "E"));
    mask.insert(std::pair<std::string, std::string>("e", "E"));
    AddSeparators(&mask, "Start");
    AddSpaces(&mask, "Start");
    transition_table->insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Integer", mask));

    mask.clear();
    AddNumbers(&mask, "Decimal");
    transition_table->insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Double", mask));

    mask.clear();
    AddNumbers(&mask, "Decimal");
    mask.insert(std::pair<std::string, std::string>("E", "E"));
    mask.insert(std::pair<std::string, std::string>("e", "E"));
    AddSeparators(&mask, "Start");
    AddSpaces(&mask, "Start");
    transition_table->insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Decimal", mask));

    mask.clear();
    AddNumbers(&mask, "Exponent");
    mask.insert(std::pair<std::string, std::string>("+", "Exponent"));
    mask.insert(std::pair<std::string, std::string>("-", "Exponent"));
    transition_table->insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("E", mask));

    mask.clear();
    AddNumbers(&mask, "Exponent");
    AddSeparators(&mask, "Start");
    AddSpaces(&mask, "Start");
    transition_table->insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Exponent", mask));
}

void FillTypes(std::unordered_map<std::string, Token::Type>* all_types)
{
    (*all_types)["program"] = Token::TokenProgram;
    (*all_types)["boolean"] = Token::TokenBoolean;
    (*all_types)["integer"] = Token::TokenInteger;
    (*all_types)["double"] = Token::TokenDouble;
    (*all_types)["string"] = Token::TokenString;
    (*all_types)["begin"] = Token::TokenBegin;
    (*all_types)["end"] = Token::TokenEnd;
    (*all_types)["var"] = Token::TokenVar;
    (*all_types)["writeln"] = Token::TokenWriteln;
    (*all_types)["if"] = Token::TokenIf;
    (*all_types)["then"] = Token::TokenThen;
    (*all_types)["else"] = Token::TokenElse;
    (*all_types)["for"] = Token::TokenFor;
    (*all_types)["do"] = Token::TokenDo;
    (*all_types)["while"] = Token::TokenWhile;
    (*all_types)[";"] = Token::TokenSemicolon;
    (*all_types)[":"] = Token::TokenColon;
    (*all_types)[":="] = Token::TokenAssign;
    (*all_types)[">"] = Token::TokenMore;
    (*all_types)["<"] = Token::TokenLess;
    (*all_types)["="] = Token::TokenEqual;
    (*all_types)["<>"] = Token::TokenUnequal;
    (*all_types)[">="] = Token::TokenMoreOrEqual;
    (*all_types)["<="] = Token::TokenLessOrEqual;
    (*all_types)["+"] = Token::TokenPlus;
    (*all_types)["-"] = Token::TokenMinus;
    (*all_types)["("] = Token::TokenLeftParenthesis;
    (*all_types)[")"] = Token::TokenRightParenthesis;
    (*all_types)[","] = Token::TokenComma;
    (*all_types)["."] = Token::TokenPoint;
    (*all_types)["["] = Token::TokenLeftSquareBracket;
    (*all_types)["]"] = Token::TokenRightSquareBracket;
}

bool SpacesCheck(const std::string* str)
{
    return (*str == " ") || (*str == "\t") || (*str == "\n") || (*str == "\r");
}

bool ComparisonAssignmentCheck(const std::string str)
{
    return (str == "<=") || (str == ">=") || (str == "==") || (str == ":=") || (str == "<>");
}

bool ASCIICheck(const std::string str)
{
    for (char i : str)
    {
        if ((i < 0) || (i > 127))
        {
            return false;
        }
    }
    return true;
}

void GetNextSymbol(std::ifstream* input_file, std::string* buffer)
{
    *buffer += static_cast<char>(input_file->get());
    if (ComparisonAssignmentCheck(*buffer + static_cast<char>(input_file->peek())))
    {
        *buffer += static_cast<char>(input_file->get());
    }
}

void UngetNextSymbol(std::ifstream* input_file, std::string* buffer)
{
    for (int i = buffer->length() - 1; i >= 0; --i)
    {
        input_file->unget();
    }
}

bool HasLexem(std::ifstream* input_file)
{
    return input_file->peek() != EOF;
}

Token TakeToken(std::unordered_map<std::string, std::unordered_map<std::string, std::string>>* transition_table, std::unordered_map<std::string, Token::Type>* all_types, std::ifstream* input_file)
{
    std::string current_state = "Start";
    Token token;
    std::string buffer;
    GetNextSymbol(input_file, &buffer);
    while (((transition_table->at(current_state).count(buffer) != 0) || (current_state == "Comment") || (current_state == "Quote")) && (HasLexem(input_file)))
    {
        if (transition_table->at(current_state).count(buffer) != 0)
        {
            if (transition_table->at(current_state).at(buffer) == "Start")
            {
                break;
            }
            current_state = transition_table->at(current_state).at(buffer);
        }
        if ((current_state != "Comment") && (!SpacesCheck(&buffer)))
        {
            token.lexem += buffer;
        }
        buffer.clear();
        GetNextSymbol(input_file, &buffer);
    }
    if (current_state == "Start")
    {
        if (!SpacesCheck(&buffer))
        {
            token.lexem += buffer;
        }
    }
    else
    {
        UngetNextSymbol(input_file, &buffer);
    }
    if (all_types->count(token.lexem) != 0)
    {
        token.type = all_types->at(token.lexem);
        return token;
    }
    if ((token.lexem == "true") || (token.lexem == "false"))
    {
        token.type = Token::TokenBooleanConst;
        return token;
    }
    if (current_state == "EndQuote")
    {
        token.type = Token::TokenStringConst;
        return token;
    }
    if (current_state == "Integer")
    {
        token.type = Token::TokenIntegerConst;
        return token;
    }
    if ((current_state == "Decimal") || (current_state == "Exponent"))
    {
        token.type = Token::TokenDoubleConst;
        return token;
    }
    if (current_state == "Text")
    {
        token.type = Token::TokenIdentifier;
        return token;
    }
    token.type = Token::TokenUndefined;
    return token;
}

Token GetToken(std::unordered_map<std::string, std::unordered_map<std::string, std::string>>* transition_table, std::unordered_map<std::string, Token::Type>* all_types, std::ifstream* input_file)
{
    Token token;
    do
    {
        token = TakeToken(transition_table, all_types, input_file);
    }
    while ((token.type == Token::TokenUndefined) && (HasLexem(input_file)));
    return token;
}