//
// Created by ghost on 05.05.2020.
//

#include "variable.h"

AbstractVariable::AbstractVariable(const std::string new_name, Type new_type, bool if_constant) : Data(new_type)
{
    name = new_name;
    constant = if_constant;
}

std::string AbstractVariable::GetName() const
{
    return name;
}

bool AbstractVariable::Constant() const
{
    return constant;
}

void AbstractVariable::Do(Context& context)
{
    context.stack.emplace(VariablePtr(this));
}

BooleanVariable::BooleanVariable(const std::string new_name, Type new_type, bool if_constant, bool new_value) : AbstractVariable(new_name, new_type, if_constant)
{
      value = new_value;
}

bool BooleanVariable::GetValue() const
{
    return value;
}

bool BooleanVariable::ChangeValue(const bool new_value)
{
    if (!Constant())
    {
        value = new_value;
    }
    return !Constant();
}

StringVariable::StringVariable(const std::string new_name, Type new_type, bool if_constant, const std::string new_value) : AbstractVariable(new_name, new_type, if_constant)
{
    value = new_value;
}

std::string StringVariable::GetValue() const
{
    return value;
}

bool StringVariable::ChangeValue(const std::string new_value)
{
    if (!Constant())
    {
        value = new_value;
    }
    return !Constant();
}

IntegerVariable::IntegerVariable(const std::string new_name, Type new_type, bool if_constant, const int new_value) : AbstractVariable(new_name, new_type, if_constant)
{
    value = new_value;
}

int IntegerVariable::GetValue() const
{
    return value;
}

bool IntegerVariable::ChangeValue(const int new_value)
{
    if (!Constant())
    {
        value = new_value;
    }
    return !Constant();
}

DoubleVariable::DoubleVariable(const std::string new_name, Type new_type, bool if_constant, const double new_value) : AbstractVariable(new_name, new_type, if_constant)
{
    value = new_value;
}

double DoubleVariable::GetValue() const
{
    return value;
}

bool DoubleVariable::ChangeValue(const double new_value)
{
    if (!Constant())
    {
        value = new_value;
    }
    return !Constant();
}