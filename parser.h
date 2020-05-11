//
// Created by ghost on 03.05.2020.
//

#include "flex.h"
#include "variable.h"
#include "operations.h"
#include "type_tables.h"

#pragma once

class Parser
{
public:
    std::vector<std::shared_ptr<Data>> commands;
    std::unordered_map<std::string, std::shared_ptr<AbstractVariable>> variables;

    explicit Parser(std::string file);

    void Start();

    void TestOutput() const;

private:
    bool has_token;
    Token current_token;
    Flex flex;
    std::unordered_map<TupleOfTokens, std::shared_ptr<Data>> functions_types;

    void FillFunctionsTypes();
    [[no_return]] void Error(std::string lexem) const;
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