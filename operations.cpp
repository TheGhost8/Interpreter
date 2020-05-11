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
    VariablePtr operand2 = context.stack.top();
    context.stack.pop();
    VariablePtr operand1 = context.stack.top();
    context.stack.pop();
    context.stack.push(VariablePtr(DoMath(*operand1.get(), *operand2.get())));
}