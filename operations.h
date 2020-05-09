//
// Created by ghost on 06.05.2020.
//

#include "context.h"
#include "variable.h"

#pragma once

using VariablePtr = std::shared_ptr<AbstractVariable>;
using OperationIndex = std::size_t;

struct Print : Context
{
public:
    explicit Print() : Context(Token::TokenWriteln) {}
    void Output(VariablePtr operand1);
};

struct Go : Context
{
    Go(OperationIndex new_index, Token::Type new_type);

    void Do() const;
    OperationIndex GetIndex() const;

private:
    OperationIndex index;
};

struct IfGo : Go
{
    IfGo(OperationIndex new_index, Token::Type new_type) : Go(new_index, new_type) {}

    void Do() const;
};

struct MathOperation : Context
{
    explicit MathOperation(Token::Type new_type) : Context(new_type) {}
    virtual ~MathOperation() {}
    virtual VariablePtr Do(VariablePtr operand1, VariablePtr operand2) const = 0;
};

//template <typename T1, typename T2>
struct AssignmentOperation : MathOperation
{
    AssignmentOperation() : MathOperation(Token::TokenAssign) {}
    VariablePtr Do(VariablePtr operand1, VariablePtr operand2) const final {}
};

//template <typename T1, typename T2>
struct PlusOperation : MathOperation
{
    PlusOperation() : MathOperation(Token::TokenPlus) {}
    VariablePtr Do(VariablePtr operand1, VariablePtr operand2) const final {}
};

//template <typename T1, typename T2>
struct MinusOperation : MathOperation
{
    MinusOperation() : MathOperation(Token::TokenMinus) {}
    VariablePtr Do(VariablePtr operand1, VariablePtr operand2) const final {}
};

//template <typename T1, typename T2>
struct MultiplyOperation : MathOperation
{
    MultiplyOperation() : MathOperation(Token::TokenMultiply) {}
    VariablePtr Do(VariablePtr operand1, VariablePtr operand2) const final {}
};

//template <typename T1, typename T2>
struct DivideOperation : MathOperation
{
    DivideOperation() : MathOperation(Token::TokenDivide) {}
    VariablePtr Do(VariablePtr operand1, VariablePtr operand2) const final {}
};

//template <typename T1, typename T2>
struct DivOperation : MathOperation
{
    DivOperation() : MathOperation(Token::TokenDiv) {}
    VariablePtr Do(VariablePtr operand1, VariablePtr operand2) const final {}
};

//template <typename T1, typename T2>
struct ModOperation : MathOperation
{
    ModOperation() : MathOperation(Token::TokenMod) {}
    VariablePtr Do(VariablePtr operand1, VariablePtr operand2) const final {}
};

//template <typename T1, typename T2>
struct EqualOperation : MathOperation
{
    EqualOperation() : MathOperation(Token::TokenEqual) {}
    VariablePtr Do(VariablePtr operand1, VariablePtr operand2) const final {}
};

//template <typename T1, typename T2>
struct UnequalOperation : MathOperation
{
    UnequalOperation() : MathOperation(Token::TokenUnequal) {}
    VariablePtr Do(VariablePtr operand1, VariablePtr operand2) const final {}
};

//template <typename T1, typename T2>
struct MoreOperation : MathOperation
{
    MoreOperation() : MathOperation(Token::TokenMore) {}
    VariablePtr Do(VariablePtr operand1, VariablePtr operand2) const final {}
};

//template <typename T1, typename T2>
struct LessOperation : MathOperation
{
    LessOperation() : MathOperation(Token::TokenLess) {}
    VariablePtr Do(VariablePtr operand1, VariablePtr operand2) const final {}
};

//template <typename T1, typename T2>
struct MoreOrEqualOperation : MathOperation
{
    MoreOrEqualOperation() : MathOperation(Token::TokenMoreOrEqual) {}
    VariablePtr Do(VariablePtr operand1, VariablePtr operand2) const final {}
};

//template <typename T1, typename T2>
struct LessOrEqualOperation : MathOperation
{
    LessOrEqualOperation() : MathOperation(Token::TokenLessOrEqual) {}
    VariablePtr Do(VariablePtr operand1, VariablePtr operand2) const final {}
};