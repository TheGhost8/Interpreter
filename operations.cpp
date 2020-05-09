//
// Created by ghost on 06.05.2020.
//

#include "operations.h"

OperationIndex Go::GetIndex() const
{
    return index;
}

Go::Go(OperationIndex new_index, Type new_type) : Data(new_type)
{
    index = new_index;
}

void Go::Do(Context &context)
{
    context.operation_index = index;
}

void IfGo::Do(Context &context)
{
    BooleanVariable* condition = static_cast<BooleanVariable*>(context.stack.top().get());
    context.stack.pop();
    if (!condition->GetValue())
    {
        Go::Do(context);
    }
}

void MathOperation::Do(Context& context)
{
    DataPtr operand2 = context.stack.top();
    context.stack.pop();
    if (!CheckVariable(operand2))
    {
        Error("correct type in operand 1 in poliz");
    }
    DataPtr operand1 = context.stack.top();
    context.stack.pop();
    if (!CheckVariable(operand1))
    {
        Error("correct type in operand 2 in poliz");
    }
    context.stack.push(DoMath(VariablePtr(static_cast<AbstractVariable*>(operand1.get())), VariablePtr(static_cast<AbstractVariable*>(operand2.get()))));
}

bool MathOperation::CheckVariable(DataPtr variable) const
{
    return (variable.get()->GetType() == TokenBoolean) || (variable.get()->GetType() == TokenString) || (variable.get()->GetType() == TokenInteger) || (variable.get()->GetType() == TokenDouble);
}