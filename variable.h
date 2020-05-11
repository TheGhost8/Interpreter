//
// Created by ghost on 05.05.2020.
//

#include "flex.h"

#pragma once

struct AbstractVariable
{
    using VariablePtr = std::shared_ptr<AbstractVariable>;

public:
    AbstractVariable(std::string new_name, Type new_type, bool if_constant);
    std::string GetName() const;
    Type GetType() const;
    bool Constant() const;

private:
    Type type;
    std::string name;
    bool constant;
};

struct BooleanVariable : AbstractVariable
{
public:
    BooleanVariable(std::string new_name, Type new_type, bool if_constant, bool new_value = false);
    bool GetValue() const;
    bool ChangeValue(bool new_value);

private:
    bool value;
};

struct StringVariable : AbstractVariable
{
public:
    StringVariable(std::string new_name, Type new_type, bool if_constant, std::string new_value = "");
    std::string GetValue() const;
    bool ChangeValue(std::string new_value);

private:
    std::string value;
};

struct IntegerVariable : AbstractVariable
{
public:
    IntegerVariable(std::string new_name, Type new_type, bool if_constant, int new_value = 0);
    int GetValue() const;
    bool ChangeValue(int new_value);

private:
    int value;
};

struct DoubleVariable : AbstractVariable
{
public:
    DoubleVariable(std::string new_name, Type new_type, bool if_constant, double new_value = 0);
    double GetValue() const;
    bool ChangeValue(double new_value);

private:
    double value;
};