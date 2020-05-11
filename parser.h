//
// Created by ghost on 03.05.2020.
//

#include "flex.h"
#include "variable.h"
#include "operations.h"
#include "type_tables.h"

#pragma once

using DataPtr = std::shared_ptr<Data>;

class Parser
{
public:
    std::vector<std::shared_ptr<Data>> commands;

    explicit Parser(std::string file);

    void Start();

    void TestOutput() const;

private:
    bool has_token;
    u_int32_t current_line;
    Token current_token;
    Flex flex;
    std::unordered_map<std::string, VariablePtr> variables;
    std::unordered_map<TupleOfTokens, std::shared_ptr<Data>> functions_types;

    void FillFunctionsTypes();
    void Error(std::string lexem);
    bool CheckToken(Type required_type) const;
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
    Type Expression();
    Type RelationOperator();
    Type SimpleExpression();
    Type Sign();
    Type Term();
    Type MultiplicationOperator();
    Type Factor();
    void If();
    void While();
    void For();
    void ForList();
};