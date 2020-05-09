//
// Created by ghost on 03.05.2020.
//

#ifndef INTERPRETER_PARSER_H
#define INTERPRETER_PARSER_H

#endif //INTERPRETER_PARSER_H

#include "flex.h"
#include "variable.h"
#include "operations.h"

#pragma once

using TupleOfTokens = std::tuple<Token::Type, Token::Type, Token::Type>;

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

class Parser
{
public:
    explicit Parser(std::string file);

    void Start();

    void TestOutput() const;

private:
    bool has_token;
    Token current_token;
    Flex flex;
    std::unordered_map<TupleOfTokens, Token::Type> operations_type;
    std::unordered_map<std::string, std::shared_ptr<AbstractVariable>> variables;
    //OperationIndex operation_index;
    std::vector<std::shared_ptr<Context>> commands;

    void FillTypeOperands();
    void Error(std::string lexem) const;
    bool CheckToken(Token::Type required_type) const;
    bool TypeCheck() const;
    bool ConstantCheck() const;
    bool MultiplyCheck() const;
    bool RelationOperatorCheck() const;
    void NextToken();
    std::shared_ptr<AbstractVariable> ConstantConversion(Token constant);

    void Program();
    void VariableDeclarationBlock();
    void VariableDeclaration();
    void MainBlock();
    void Statement();
    void Writeln();
    void CompoundStatement();
    void AssignmentStatement();
    Token::Type Expression();
    Token::Type RelationOperator();
    Token::Type SimpleExpression();
    Token::Type Sign();
    Token::Type Term();
    Token::Type MultiplicationOperator();
    Token::Type Factor();
    void If();
    void While();
    void For();
    void ForList();
};