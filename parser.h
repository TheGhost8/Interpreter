//
// Created by ghost on 03.05.2020.
//

#ifndef INTERPRETER_PARSER_H
#define INTERPRETER_PARSER_H

#endif //INTERPRETER_PARSER_H

#include "flex.h"

#pragma once

class Parser
{
public:
    explicit Parser(std::string file);

    void Start();

private:
    bool has_token;
    Token current_token;
    Flex flex;

    void Error(std::string lexem) const;
    bool CheckToken(Token::Type required_type) const;
    bool TypeCheck() const;
    bool ConstantCheck() const;
    bool MultiplyCheck() const;
    bool RelationOperatorCheck() const;
    void NextToken();

    void Program();
    void VariableDeclarationBlock();
    void VariableDeclaration();
    void MainBlock();
    void Statement();
    void Writeln();
    void CompoundStatement();
    void AssignmentStatement();
    void Expression();
    void RelationOperator();
    void SimpleExpression();
    void Sign();
    void Term();
    void MultiplicationOperator();
    void Factor();
    void If();
    void While();
    void For();
    void ForList();
};