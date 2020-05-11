//
// Created by ghost on 09.05.2020.
//

#include <iostream>
#include <memory>
#include <unordered_map>

#pragma once

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
    TokenGoTo,
    TokenThen,
    TokenElse,
    TokenFor,
    TokenDo,
    TokenWhile,
    TokenTo,
    TokenDownTo,
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
    TokenMultiply,
    TokenDivide,
    TokenDiv,
    TokenMod,
    TokenIdentifier,
    TokenSpace,
    TokenTab,
    TokenEnter,
    TokenEOF,
    TokenUndefined,
};

using TupleOfTokens = std::tuple<Type, Type, Type>;

namespace std
{
    template <>
    struct hash<TupleOfTokens>
    {
        std::size_t operator()(const TupleOfTokens& tuple) const
        {
            using std::size_t;
            using std::hash;

            return hash<unsigned int>()(std::get<0>(tuple)) ^ (hash<unsigned int>()(std::get<0>(tuple))) ^ (hash<unsigned int>()(std::get<0>(tuple)));
        }
    };
}

std::unordered_map<TupleOfTokens, Type> FillTypeOperands();
static std::unordered_map<TupleOfTokens, Type> operations_type = FillTypeOperands();

class TypeTables
{
public:
    TypeTables();
    static std::unordered_map<TupleOfTokens, Type> operations_type;

private:
    //void FillTypeOperands();
};
