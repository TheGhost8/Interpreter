//
// Created by ghost on 03.05.2020.
//

#include "flex.h"

Flex::Flex(std::string file)
{
    FillDFA();
    FillTypes(&all_types);
    input_file.open(file);
}

bool Flex::HasLexem()
{
    return input_file.peek() != EOF;
}

Token Flex::GetToken(u_int32_t* current_line)
{
    Token token;
    do
    {
        token = TakeToken();
        if (token.type == TokenEnter)
        {
            ++(*current_line);
        }
        token.line = *current_line;
    }
    while ((token.type == TokenUndefined) || (SpacesCheck(&token.lexem)));
    return token;
}

void Flex::AddLetters(std::unordered_map<std::string, std::string>* map, const std::string Destination)
{
    int shift = 'A' - 'a';
    for (char i = 'a'; i <= 'z'; i++)
    {
        map->insert(std::pair<std::string, std::string>(std::string(1, i), Destination));
        map->insert(std::pair<std::string, std::string>(std::string(1, i + shift), Destination));
    }
}

void Flex::AddNumbers(std::unordered_map<std::string, std::string>* map, const std::string Destination)
{
    for (char i = '0'; i <= '9'; i++)
    {
        map->insert(std::pair<std::string, std::string>(std::string(1, i), Destination));
    }
}

void Flex::AddSeparators(std::unordered_map<std::string, std::string>* map, const std::string Destination)
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

void Flex::AddSpaces(std::unordered_map<std::string, std::string>* map, const std::string Destination)
{
    map->insert(std::pair<std::string, std::string>(" ", Destination));
    map->insert(std::pair<std::string, std::string>("\t", Destination));
    map->insert(std::pair<std::string, std::string>("\r", Destination));
    map->insert(std::pair<std::string, std::string>("\n", Destination));
}

void Flex::FillDFA()
{
    std::unordered_map<std::string, std::string> mask;
    AddLetters(&mask, "Text");
    AddNumbers(&mask, "Integer");
    mask.insert(std::pair<std::string, std::string>("_", "Text"));
    mask.insert(std::pair<std::string, std::string>("'", "Quote"));
    mask.insert(std::pair<std::string, std::string>("{", "Comment"));
    AddSeparators(&mask, "Start");
    AddSpaces(&mask, "Start");
    transition_table.insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Start", mask));

    mask.clear();
    AddLetters(&mask, "Text");
    AddNumbers(&mask, "Text");
    mask.insert(std::pair<std::string, std::string>("_", "Text"));
    AddSeparators(&mask, "Start");
    AddSpaces(&mask, "Start");
    transition_table.insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Text", mask));

    mask.clear();
    mask.insert(std::pair<std::string, std::string>("'", "EndQuote"));
    transition_table.insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Quote", mask));

    mask.clear();
    mask.insert(std::pair<std::string, std::string>("'", "Quote"));
    AddSeparators(&mask, "Start");
    AddSpaces(&mask, "Start");
    transition_table.insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("EndQuote", mask));

    mask.clear();
    mask.insert(std::pair<std::string, std::string>("}", "Start"));
    transition_table.insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Comment", mask));

    mask.clear();
    AddNumbers(&mask, "Integer");
    mask.insert(std::pair<std::string, std::string>(".", "Double"));
    mask.insert(std::pair<std::string, std::string>("E", "E"));
    mask.insert(std::pair<std::string, std::string>("e", "E"));
    AddSeparators(&mask, "Start");
    AddSpaces(&mask, "Start");
    transition_table.insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Integer", mask));

    mask.clear();
    AddNumbers(&mask, "Decimal");
    transition_table.insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Double", mask));

    mask.clear();
    AddNumbers(&mask, "Decimal");
    mask.insert(std::pair<std::string, std::string>("E", "E"));
    mask.insert(std::pair<std::string, std::string>("e", "E"));
    AddSeparators(&mask, "Start");
    AddSpaces(&mask, "Start");
    transition_table.insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Decimal", mask));

    mask.clear();
    AddNumbers(&mask, "Exponent");
    mask.insert(std::pair<std::string, std::string>("+", "Exponent"));
    mask.insert(std::pair<std::string, std::string>("-", "Exponent"));
    transition_table.insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("E", mask));

    mask.clear();
    AddNumbers(&mask, "Exponent");
    AddSeparators(&mask, "Start");
    AddSpaces(&mask, "Start");
    transition_table.insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("Exponent", mask));
}

void Flex::FillTypes(std::unordered_map<std::string, Type>* all_types)
{
    (*all_types)["program"] = TokenProgram;
    (*all_types)["boolean"] = TokenBoolean;
    (*all_types)["integer"] = TokenInteger;
    (*all_types)["double"] = TokenDouble;
    (*all_types)["string"] = TokenString;
    (*all_types)["begin"] = TokenBegin;
    (*all_types)["end"] = TokenEnd;
    (*all_types)["var"] = TokenVar;
    (*all_types)["writeln"] = TokenWriteln;
    (*all_types)["if"] = TokenIf;
    (*all_types)["then"] = TokenThen;
    (*all_types)["else"] = TokenElse;
    (*all_types)["for"] = TokenFor;
    (*all_types)["do"] = TokenDo;
    (*all_types)["while"] = TokenWhile;
    (*all_types)["to"] = TokenTo;
    (*all_types)["downto"] = TokenDownTo;
    (*all_types)[";"] = TokenSemicolon;
    (*all_types)[":"] = TokenColon;
    (*all_types)[":="] = TokenAssign;
    (*all_types)[">"] = TokenMore;
    (*all_types)["<"] = TokenLess;
    (*all_types)["="] = TokenEqual;
    (*all_types)["<>"] = TokenUnequal;
    (*all_types)[">="] = TokenMoreOrEqual;
    (*all_types)["<="] = TokenLessOrEqual;
    (*all_types)["+"] = TokenPlus;
    (*all_types)["-"] = TokenMinus;
    (*all_types)["("] = TokenLeftParenthesis;
    (*all_types)[")"] = TokenRightParenthesis;
    (*all_types)[","] = TokenComma;
    (*all_types)["."] = TokenPoint;
    (*all_types)["["] = TokenLeftSquareBracket;
    (*all_types)["]"] = TokenRightSquareBracket;
    (*all_types)["*"] = TokenMultiply;
    (*all_types)["\\"] = TokenDivide;
    (*all_types)["div"] = TokenDiv;
    (*all_types)["mod"] = TokenMod;
    (*all_types)[" "] = TokenSpace;
    (*all_types)["\t"] = TokenTab;
    (*all_types)["\n"] = TokenEnter;
    (*all_types)[std::string(1, EOF)] = TokenEOF;
}

bool Flex::SpacesCheck(const std::string* str)
{
    return (*str == " ") || (*str == "\t") || (*str == "\n") || (*str == "\r");
}

bool Flex::ComparisonAssignmentCheck(const std::string str)
{
    return (str == "<=") || (str == ">=") || (str == "==") || (str == ":=") || (str == "<>");
}

bool Flex::ASCIICheck(const std::string str)
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

void Flex::GetNextSymbol(std::string* buffer)
{
    *buffer += static_cast<char>(input_file.get());
    if (ComparisonAssignmentCheck(*buffer + static_cast<char>(input_file.peek())))
    {
        *buffer += static_cast<char>(input_file.get());
    }
}

void Flex::UngetNextSymbol(std::string* buffer)
{
    for (int i = buffer->length() - 1; i >= 0; --i)
    {
        input_file.unget();
    }
}

Token Flex::TakeToken()
{
    std::string current_state = "Start";
    Token token;
    std::string buffer;
    GetNextSymbol(&buffer);
    while (((transition_table.at(current_state).count(buffer) != 0) || (current_state == "Comment") || (current_state == "Quote")) && (HasLexem()))
    {
        if ((current_state == "Quote") && (buffer == "\n"))
        {
            break;
        }
        if (transition_table.at(current_state).count(buffer) != 0)
        {
            if (transition_table.at(current_state).at(buffer) == "Start")
            {
                break;
            }
            current_state = transition_table.at(current_state).at(buffer);
        }
        if (current_state != "Comment")
        {
            token.lexem += buffer;
        }
        buffer.clear();
        GetNextSymbol(&buffer);
    }
    if ((!HasLexem()) || ((current_state == "Quote") && (buffer == "\n")))
    {
        if (current_state == "Comment")
        {
            throw '}';
        } else if ((current_state == "Quote") && (buffer == "\n"))
        {
            throw '\'';
        }
    }
    if (current_state == "Start")
    {
        token.lexem += buffer;
    }
    else
    {
        UngetNextSymbol(&buffer);
    }
    if (all_types.count(token.lexem) != 0)
    {
        token.type = all_types.at(token.lexem);
        return token;
    }
    if ((token.lexem == "true") || (token.lexem == "false"))
    {
        token.type = TokenBooleanConst;
        return token;
    }
    if (current_state == "EndQuote")
    {
        token.type = TokenStringConst;
        return token;
    }
    if (current_state == "Integer")
    {
        token.type = TokenIntegerConst;
        return token;
    }
    if ((current_state == "Decimal") || (current_state == "Exponent"))
    {
        token.type = TokenDoubleConst;
        return token;
    }
    if (current_state == "Text")
    {
        token.type = TokenIdentifier;
        return token;
    }
    token.type = TokenUndefined;
    return token;
}