//
// Created by ghost on 06.05.2020.
//

#include "data.h"
#include "variable.h"

#pragma once

struct PushVariable : Data
{
public:
    explicit PushVariable(VariablePtr new_variable) : variable(new_variable), Data(new_variable->GetType()) {}
    void Do(Context& context) final
    {
        context.stack.push(variable);
    }

private:
    VariablePtr variable;
};

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
        VariablePtr operand2 = context.stack.top();
        context.stack.pop();
        VariablePtr operand1 = context.stack.top();
        context.stack.pop();
        static_cast<T1*>(operand1.get())->ChangeValue(static_cast<T2*>(operand2.get())->GetValue());
    }
};

struct MathOperation : Data
{
    explicit MathOperation(Type new_type) : Data(new_type) {}
    virtual ~MathOperation() {}
    virtual void Do(Context& context) final;
    virtual AbstractVariable* DoMath(const AbstractVariable& operand1, const AbstractVariable& operand2) const = 0;
};

template <typename T1, typename T2, typename T3>
struct PlusOperation : MathOperation
{
    PlusOperation() : MathOperation(TokenPlus) {}
    AbstractVariable* DoMath(const AbstractVariable& operand1, const AbstractVariable& operand2) const final
    {
        return new T3("", operations_type.at(TupleOfTokens(operand1.GetType(), TokenPlus, operand2.GetType())), true, static_cast<const T1&>(operand1).GetValue() + static_cast<const T2&>(operand2).GetValue());
    }
};

template <typename T1, typename T2, typename T3>
struct MinusOperation : MathOperation
{
    MinusOperation() : MathOperation(TokenMinus) {}
    AbstractVariable* DoMath(const AbstractVariable& operand1, const AbstractVariable& operand2) const final
    {
        return new T3("", operations_type.at(TupleOfTokens(operand1.GetType(), TokenMinus, operand2.GetType())), true, static_cast<const T1&>(operand1).GetValue() - static_cast<const T2&>(operand2).GetValue());
    }
};

template <typename T1, typename T2, typename T3>
struct MultiplyOperation : MathOperation
{
    MultiplyOperation() : MathOperation(TokenMultiply) {}
    AbstractVariable* DoMath(const AbstractVariable& operand1, const AbstractVariable& operand2) const final
    {
        return new T3("", operations_type.at(TupleOfTokens(operand1.GetType(), TokenMultiply, operand2.GetType())), true, static_cast<const T1&>(operand1).GetValue() * static_cast<const T2&>(operand2).GetValue());
    }
};

template <typename T1, typename T2, typename T3>
struct DivideOperation : MathOperation
{
    DivideOperation() : MathOperation(TokenDivide) {}
    AbstractVariable* DoMath(const AbstractVariable& operand1, const AbstractVariable& operand2) const final
    {
        return new T3("", operations_type.at(TupleOfTokens(operand1.GetType(), TokenDivide, operand2.GetType())), true, static_cast<const T1&>(operand1).GetValue() / static_cast<const T2&>(operand2).GetValue());
    }
};

template <typename T1, typename T2, typename T3>
struct DivOperation : MathOperation
{
    DivOperation() : MathOperation(TokenDiv) {}
    AbstractVariable* DoMath(const AbstractVariable& operand1, const AbstractVariable& operand2) const final
    {
        return new T3("", operations_type.at(TupleOfTokens(operand1.GetType(), TokenDiv, operand2.GetType())), true, static_cast<int>(static_cast<const T1&>(operand1).GetValue() / static_cast<const T2&>(operand2).GetValue()));
    }
};

template <typename T1, typename T2, typename T3>
struct ModOperation : MathOperation
{
    ModOperation() : MathOperation(TokenMod) {}
    AbstractVariable* DoMath(const AbstractVariable& operand1, const AbstractVariable& operand2) const final
    {
        return new T3("", operations_type.at(TupleOfTokens(operand1.GetType(), TokenMod, operand2.GetType())), true, static_cast<const T1&>(operand1).GetValue() % static_cast<const T2&>(operand2).GetValue());
    }
};

template <typename T1, typename T2, typename T3>
struct EqualOperation : MathOperation
{
    EqualOperation() : MathOperation(TokenEqual) {}
    AbstractVariable* DoMath(const AbstractVariable& operand1, const AbstractVariable& operand2) const final
    {
        return new T3("", operations_type.at(TupleOfTokens(operand1.GetType(), TokenEqual, operand2.GetType())), true, static_cast<const T1&>(operand1).GetValue() == static_cast<const T2&>(operand2).GetValue());
    }
};

template <typename T1, typename T2, typename T3>
struct UnequalOperation : MathOperation
{
    UnequalOperation() : MathOperation(TokenUnequal) {}
    AbstractVariable* DoMath(const AbstractVariable& operand1, const AbstractVariable& operand2) const final
    {
        return new T3("", operations_type.at(TupleOfTokens(operand1.GetType(), TokenUnequal, operand2.GetType())), true, static_cast<const T1&>(operand1).GetValue() != static_cast<const T2&>(operand2).GetValue());
    }
};

template <typename T1, typename T2, typename T3>
struct MoreOperation : MathOperation
{
    MoreOperation() : MathOperation(TokenMore) {}
    AbstractVariable* DoMath(const AbstractVariable& operand1, const AbstractVariable& operand2) const final
    {
        return new T3("", operations_type.at(TupleOfTokens(operand1.GetType(), TokenMore, operand2.GetType())), true, static_cast<const T1&>(operand1).GetValue() > static_cast<const T2&>(operand2).GetValue());
    }
};

template <typename T1, typename T2, typename T3>
struct LessOperation : MathOperation
{
    LessOperation() : MathOperation(TokenLess) {}
    AbstractVariable* DoMath(const AbstractVariable& operand1, const AbstractVariable& operand2) const final
    {
        return new T3("", operations_type.at(TupleOfTokens(operand1.GetType(), TokenLess, operand2.GetType())), true, static_cast<const T1&>(operand1).GetValue() < static_cast<const T2&>(operand2).GetValue());
    }
};

template <typename T1, typename T2, typename T3>
struct MoreOrEqualOperation : MathOperation
{
    MoreOrEqualOperation() : MathOperation(TokenMoreOrEqual) {}
    AbstractVariable* DoMath(const AbstractVariable& operand1, const AbstractVariable& operand2) const final
    {
        return new T3("", operations_type.at(TupleOfTokens(operand1.GetType(), TokenMoreOrEqual, operand2.GetType())), true, static_cast<const T1&>(operand1).GetValue() >= static_cast<const T2&>(operand2).GetValue());
    }
};

template <typename T1, typename T2, typename T3>
struct LessOrEqualOperation : MathOperation
{
    LessOrEqualOperation() : MathOperation(TokenLessOrEqual) {}
    AbstractVariable* DoMath(const AbstractVariable& operand1, const AbstractVariable& operand2) const final
    {
        return new T3("", operations_type.at(TupleOfTokens(operand1.GetType(), TokenLessOrEqual, operand2.GetType())), true, static_cast<const T1&>(operand1).GetValue() <= static_cast<const T2&>(operand2).GetValue());
    }
};