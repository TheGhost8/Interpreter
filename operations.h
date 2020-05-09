//
// Created by ghost on 06.05.2020.
//

#include "data.h"
#include "variable.h"

#pragma once

using DataPtr = std::shared_ptr<Data>;
using VariablePtr = std::shared_ptr<AbstractVariable>;

template <typename T1>
struct Print : Data
{
public:
    explicit Print() : Data(TokenWriteln) {}
    void Do(Context& context) final
    {
        T1* operand1 = static_cast<T1*>(context.stack.top().get());
        std::cout << operand1->GetValue() << std::endl;
    }
};

struct Go : Data
{
    Go(OperationIndex new_index, Type new_type);

    void Do(Context& context) override;
    OperationIndex GetIndex() const;

private:
    OperationIndex index;
};

struct IfGo : Go
{
    IfGo(OperationIndex new_index, Type new_type) : Go(new_index, new_type) {}

    void Do(Context& context) final;
};

template <typename T1, typename T2>
struct AssignmentOperation : Data
{
    AssignmentOperation() : Data(TokenAssign) {}
    virtual void Do(Context& context) final
    {
        DataPtr operand2 = context.stack.top();
        context.stack.pop();
        DataPtr operand1 = context.stack.top();
        context.stack.pop();
        static_cast<T1*>(operand1.get())->ChangeValue(static_cast<T2*>(operand2.get())->GetValue());
    }
};

struct MathOperation : Data
{
    explicit MathOperation(Type new_type) : Data(new_type) {}
    virtual ~MathOperation() {}
    virtual void Do(Context& context) final;
    virtual VariablePtr DoMath(VariablePtr operand1, VariablePtr operand2) const = 0;

private:
    bool CheckVariable(DataPtr variable) const;
};

template <typename T1, typename T2, typename T3>
struct PlusOperation : MathOperation
{
    PlusOperation() : MathOperation(TokenPlus) {}
    VariablePtr DoMath(VariablePtr operand1, VariablePtr operand2) const final
    {
        return VariablePtr(new T3("", operations_type.at(TupleOfTokens(operand1->GetType(), TokenPlus, operand2->GetType())), true, static_cast<T1*>(operand1.get())->GetValue() + static_cast<T2*>(operand2.get())->GetValue()));
    }
};

template <typename T1, typename T2, typename T3>
struct MinusOperation : MathOperation
{
    MinusOperation() : MathOperation(TokenMinus) {}
    VariablePtr DoMath(VariablePtr operand1, VariablePtr operand2) const final
    {
        return VariablePtr(new T3("", operations_type.at(TupleOfTokens(operand1->GetType(), TokenMinus, operand2->GetType())), true, static_cast<T1*>(operand1.get())->GetValue() - static_cast<T2*>(operand2.get())->GetValue()));
    }
};

template <typename T1, typename T2, typename T3>
struct MultiplyOperation : MathOperation
{
    MultiplyOperation() : MathOperation(TokenMultiply) {}
    VariablePtr DoMath(VariablePtr operand1, VariablePtr operand2) const final
    {
        return VariablePtr(new T3("", operations_type.at(TupleOfTokens(operand1->GetType(), TokenMultiply, operand2->GetType())), true, static_cast<T1*>(operand1.get())->GetValue() * static_cast<T2*>(operand2.get())->GetValue()));
    }
};

template <typename T1, typename T2, typename T3>
struct DivideOperation : MathOperation
{
    DivideOperation() : MathOperation(TokenDivide) {}
    VariablePtr DoMath(VariablePtr operand1, VariablePtr operand2) const final
    {
        return VariablePtr(new T3("", operations_type.at(TupleOfTokens(operand1->GetType(), TokenDivide, operand2->GetType())), true, static_cast<T1*>(operand1.get())->GetValue() / static_cast<T2*>(operand2.get())->GetValue()));
    }
};

template <typename T1, typename T2, typename T3>
struct DivOperation : MathOperation
{
    DivOperation() : MathOperation(TokenDiv) {}
    VariablePtr DoMath(VariablePtr operand1, VariablePtr operand2) const final
    {
        return VariablePtr(new T3("", operations_type.at(TupleOfTokens(operand1->GetType(), TokenDiv, operand2->GetType())), true, static_cast<int>(static_cast<T1*>(operand1.get())->GetValue() / static_cast<T2*>(operand2.get())->GetValue())));
    }
};

template <typename T1, typename T2, typename T3>
struct ModOperation : MathOperation
{
    ModOperation() : MathOperation(TokenMod) {}
    VariablePtr DoMath(VariablePtr operand1, VariablePtr operand2) const final
    {
        return VariablePtr(new T3("", operations_type.at(TupleOfTokens(operand1->GetType(), TokenMod, operand2->GetType())), true, static_cast<T1*>(operand1.get())->GetValue() % static_cast<T2*>(operand2.get())->GetValue()));
    }
};

template <typename T1, typename T2, typename T3>
struct EqualOperation : MathOperation
{
    EqualOperation() : MathOperation(TokenEqual) {}
    VariablePtr DoMath(VariablePtr operand1, VariablePtr operand2) const final
    {
        return VariablePtr(new T3("", operations_type.at(TupleOfTokens(operand1->GetType(), TokenEqual, operand2->GetType())), true, static_cast<T1*>(operand1.get())->GetValue() == static_cast<T2*>(operand2.get())->GetValue()));
    }
};

template <typename T1, typename T2, typename T3>
struct UnequalOperation : MathOperation
{
    UnequalOperation() : MathOperation(TokenUnequal) {}
    VariablePtr DoMath(VariablePtr operand1, VariablePtr operand2) const final
    {
        return VariablePtr(new T3("", operations_type.at(TupleOfTokens(operand1->GetType(), TokenUnequal, operand2->GetType())), true, static_cast<T1*>(operand1.get())->GetValue() != static_cast<T2*>(operand2.get())->GetValue()));
    }
};

template <typename T1, typename T2, typename T3>
struct MoreOperation : MathOperation
{
    MoreOperation() : MathOperation(TokenMore) {}
    VariablePtr DoMath(VariablePtr operand1, VariablePtr operand2) const final
    {
        return VariablePtr(new T3("", operations_type.at(TupleOfTokens(operand1->GetType(), TokenMore, operand2->GetType())), true, static_cast<T1*>(operand1.get())->GetValue() > static_cast<T2*>(operand2.get())->GetValue()));
    }
};

template <typename T1, typename T2, typename T3>
struct LessOperation : MathOperation
{
    LessOperation() : MathOperation(TokenLess) {}
    VariablePtr DoMath(VariablePtr operand1, VariablePtr operand2) const final
    {
        return VariablePtr(new T3("", operations_type.at(TupleOfTokens(operand1->GetType(), TokenLess, operand2->GetType())), true, static_cast<T1*>(operand1.get())->GetValue() < static_cast<T2*>(operand2.get())->GetValue()));
    }
};

template <typename T1, typename T2, typename T3>
struct MoreOrEqualOperation : MathOperation
{
    MoreOrEqualOperation() : MathOperation(TokenMoreOrEqual) {}
    VariablePtr DoMath(VariablePtr operand1, VariablePtr operand2) const final
    {
        return VariablePtr(new T3("", operations_type.at(TupleOfTokens(operand1->GetType(), TokenMoreOrEqual, operand2->GetType())), true, static_cast<T1*>(operand1.get())->GetValue() >= static_cast<T2*>(operand2.get())->GetValue()));
    }
};

template <typename T1, typename T2, typename T3>
struct LessOrEqualOperation : MathOperation
{
    LessOrEqualOperation() : MathOperation(TokenLessOrEqual) {}
    VariablePtr DoMath(VariablePtr operand1, VariablePtr operand2) const final
    {
        return VariablePtr(new T3("", operations_type.at(TupleOfTokens(operand1->GetType(), TokenLessOrEqual, operand2->GetType())), true, static_cast<T1*>(operand1.get())->GetValue() <= static_cast<T2*>(operand2.get())->GetValue()));
    }
};