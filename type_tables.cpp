//
// Created by ghost on 09.05.2020.
//

#include "type_tables.h"

TypeTables::TypeTables()
{
    //FillTypeOperands();
}

std::unordered_map<TupleOfTokens, Type> FillTypeOperands()
{
    std::unordered_map<TupleOfTokens, Type> operations_type;
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenBoolean, TokenAssign, TokenBoolean), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenString, TokenAssign, TokenString), TokenString));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenAssign, TokenInteger), TokenInteger));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenDouble, TokenAssign, TokenDouble), TokenDouble));

    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenString, TokenPlus, TokenString), TokenString));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenPlus, TokenInteger), TokenInteger));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenBoolean, TokenPlus, TokenBoolean), TokenBoolean));

    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenMinus, TokenInteger), TokenInteger));

    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenPlus, TokenDouble), TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenMinus, TokenDouble), TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenDouble, TokenPlus, TokenInteger), TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenDouble, TokenMinus, TokenInteger), TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenDouble, TokenPlus, TokenDouble), TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenDouble, TokenMinus, TokenDouble), TokenDouble));

    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenMultiply, TokenInteger), TokenInteger));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenDiv, TokenInteger), TokenInteger));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenMod, TokenInteger), TokenInteger));

    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenDivide, TokenInteger), TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenDivide, TokenDouble), TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenMultiply, TokenDouble), TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenDouble, TokenDivide, TokenInteger), TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenDouble, TokenMultiply, TokenInteger), TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenDouble, TokenDivide, TokenDouble), TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenDouble, TokenMultiply, TokenDouble), TokenDouble));

    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenBoolean, TokenEqual, TokenBoolean), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenBoolean, TokenUnequal, TokenBoolean), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenBoolean, TokenLess, TokenBoolean), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenBoolean, TokenMore, TokenBoolean), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenBoolean, TokenLessOrEqual, TokenBoolean), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenBoolean, TokenMoreOrEqual, TokenBoolean), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenString, TokenEqual, TokenString), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenString, TokenUnequal, TokenString), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenString, TokenLess, TokenString), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenString, TokenMore, TokenString), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenString, TokenLessOrEqual, TokenString), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenString, TokenMoreOrEqual, TokenString), TokenBoolean));

    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenEqual, TokenInteger), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenUnequal, TokenInteger), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenLess, TokenInteger), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenMore, TokenInteger), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenLessOrEqual, TokenInteger), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenMoreOrEqual, TokenInteger), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenEqual, TokenDouble), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenUnequal, TokenDouble), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenLess, TokenDouble), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenMore, TokenDouble), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenLessOrEqual, TokenDouble), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenInteger, TokenMoreOrEqual, TokenDouble), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenDouble, TokenEqual, TokenInteger), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenDouble, TokenUnequal, TokenInteger), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenDouble, TokenLess, TokenInteger), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenDouble, TokenMore, TokenInteger), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenDouble, TokenLessOrEqual, TokenInteger), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenDouble, TokenMoreOrEqual, TokenInteger), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenDouble, TokenEqual, TokenDouble), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenDouble, TokenUnequal, TokenDouble), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenDouble, TokenLess, TokenDouble), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenDouble, TokenMore, TokenDouble), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenDouble, TokenLessOrEqual, TokenDouble), TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Type>(TupleOfTokens(TokenDouble, TokenMoreOrEqual, TokenDouble), TokenBoolean));
    return operations_type;
}