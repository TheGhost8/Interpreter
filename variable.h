//
// Created by ghost on 05.05.2020.
//

#include "flex.h"
#include "context.h"

#pragma once

#ifndef INTERPRETER_VARIABLE_H
#define INTERPRETER_VARIABLE_H

#endif //INTERPRETER_VARIABLE_H

struct AbstractVariable : Context
{
public:
    AbstractVariable(const std::string* new_name, Token::Type new_type, bool if_constant);
    std::string GetName() const;
    bool Constant() const;

private:
    std::string name;
    bool constant;
};

struct BooleanVariable : AbstractVariable
{
public:
    BooleanVariable(const std::string* new_name, Token::Type new_type, bool if_constant, bool new_value = false);
    bool GetValue() const;
    bool ChangeValue(bool new_value);

private:
    bool value;
};

struct StringVariable : AbstractVariable
{
public:
    StringVariable(const std::string* new_name, Token::Type new_type, bool if_constant, std::string new_value = "");
    std::string GetValue() const;
    bool ChangeValue(const std::string* new_value);

private:
    std::string value;
};

struct IntegerVariable : AbstractVariable
{
public:
    IntegerVariable(const std::string* new_name, Token::Type new_type, bool if_constant, int new_value = 0);
    int GetValue() const;
    bool ChangeValue(const int* new_value);

private:
    int value;
};

struct DoubleVariable : AbstractVariable
{
public:
    DoubleVariable(const std::string* new_name, Token::Type new_type, bool if_constant, double new_value = 0);
    double GetValue() const;
    bool ChangeValue(const double* new_value);

private:
    double value;
};