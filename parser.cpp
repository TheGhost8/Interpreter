//
// Created by ghost on 03.05.2020.
//

#include "parser.h"

#include <memory>

Parser::Parser(std::string file) : flex(file)
{
    current_line = 0;
    FillFunctionsTypes();
    current_token = flex.GetToken(&current_line);
    has_token = true;
}

void Parser::Start()
{
    Program();
    if ((flex.GetToken(&current_line).type != TokenEOF) || has_token)
    {
        Error("Line: " + std::to_string(current_line) + ";  Expected: no lexems after end");
    }
}

void Parser::TestOutput() const
{
    std::cout << "VARIABLES\n";
    //std::cout << "1. " << variables.at("y")->GetName() << " " << variables.at("y")->GetType() << std::endl;
    std::cout << "\n";
    for (int i = 0; i < commands.size(); ++i)
    {
        std::cout << i << ". " << commands[i]->GetType();
        if ((commands[i]->GetType() == TokenIf) || (commands[i]->GetType() == TokenGoTo))
        {
            std::cout << " " << static_cast<Go*>(commands[i].get())->GetIndex();
        }
        std::cout << std::endl;
    }
}

void Parser::FillFunctionsTypes()
{
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenBoolean, TokenAssign, TokenBoolean), std::make_shared<AssignmentOperation<BooleanVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenString, TokenAssign, TokenString), std::make_shared<AssignmentOperation<StringVariable, StringVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenAssign, TokenInteger), std::make_shared<AssignmentOperation<IntegerVariable, IntegerVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenDouble, TokenAssign, TokenDouble), std::make_shared<AssignmentOperation<DoubleVariable, DoubleVariable>>()));

    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenBoolean, TokenPlus, TokenBoolean), std::make_shared<PlusOperation<BooleanVariable, BooleanVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenString, TokenPlus, TokenString), std::make_shared<PlusOperation<StringVariable, StringVariable, StringVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenPlus, TokenInteger), std::make_shared<PlusOperation<IntegerVariable, IntegerVariable, IntegerVariable>>()));

    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenMinus, TokenInteger), std::make_shared<MinusOperation<IntegerVariable, IntegerVariable, IntegerVariable>>()));

    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenPlus, TokenDouble), std::make_shared<PlusOperation<IntegerVariable, DoubleVariable, DoubleVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenDouble, TokenPlus, TokenInteger), std::make_shared<PlusOperation<DoubleVariable, IntegerVariable, DoubleVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenDouble, TokenPlus, TokenDouble), std::make_shared<PlusOperation<DoubleVariable, DoubleVariable, DoubleVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenMinus, TokenDouble), std::make_shared<MinusOperation<IntegerVariable, DoubleVariable, DoubleVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenDouble, TokenMinus, TokenInteger), std::make_shared<MinusOperation<DoubleVariable, IntegerVariable, DoubleVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenDouble, TokenMinus, TokenDouble), std::make_shared<MinusOperation<DoubleVariable, DoubleVariable, DoubleVariable>>()));

    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenMultiply, TokenInteger), std::make_shared<MultiplyOperation<IntegerVariable, IntegerVariable, IntegerVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenDiv, TokenInteger), std::make_shared<DivOperation<IntegerVariable, IntegerVariable, IntegerVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenMod, TokenInteger), std::make_shared<ModOperation<IntegerVariable, IntegerVariable, IntegerVariable>>()));

    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenDivide, TokenInteger), std::make_shared<DivideOperation<IntegerVariable, IntegerVariable, DoubleVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenDivide, TokenDouble), std::make_shared<DivideOperation<IntegerVariable, DoubleVariable, DoubleVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenDouble, TokenDivide, TokenInteger), std::make_shared<DivideOperation<DoubleVariable, IntegerVariable, DoubleVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenDouble, TokenDivide, TokenDouble), std::make_shared<DivideOperation<DoubleVariable, DoubleVariable, DoubleVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenMultiply, TokenDouble), std::make_shared<MultiplyOperation<IntegerVariable, DoubleVariable, DoubleVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenDouble, TokenMultiply, TokenInteger), std::make_shared<MultiplyOperation<DoubleVariable, IntegerVariable, DoubleVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenDouble, TokenMultiply, TokenDouble), std::make_shared<MultiplyOperation<DoubleVariable, DoubleVariable, DoubleVariable>>()));

    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenBoolean, TokenEqual, TokenBoolean), std::make_shared<EqualOperation<BooleanVariable, BooleanVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenBoolean, TokenUnequal, TokenBoolean), std::make_shared<UnequalOperation<BooleanVariable, BooleanVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenBoolean, TokenMore, TokenBoolean), std::make_shared<MoreOperation<BooleanVariable, BooleanVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenBoolean, TokenLess, TokenBoolean), std::make_shared<LessOperation<BooleanVariable, BooleanVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenBoolean, TokenMoreOrEqual, TokenBoolean), std::make_shared<MoreOrEqualOperation<BooleanVariable, BooleanVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenBoolean, TokenLessOrEqual, TokenBoolean), std::make_shared<LessOrEqualOperation<BooleanVariable, BooleanVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenString, TokenEqual, TokenString), std::make_shared<EqualOperation<StringVariable, StringVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenString, TokenUnequal, TokenString), std::make_shared<UnequalOperation<StringVariable, StringVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenString, TokenMore, TokenString), std::make_shared<MoreOperation<StringVariable, StringVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenString, TokenLess, TokenString), std::make_shared<LessOperation<StringVariable, StringVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenString, TokenMoreOrEqual, TokenString), std::make_shared<MoreOrEqualOperation<StringVariable, StringVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenString, TokenLessOrEqual, TokenString), std::make_shared<LessOrEqualOperation<StringVariable, StringVariable, BooleanVariable>>()));

    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenEqual, TokenInteger), std::make_shared<EqualOperation<IntegerVariable, IntegerVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenUnequal, TokenInteger), std::make_shared<UnequalOperation<IntegerVariable, IntegerVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenMore, TokenInteger), std::make_shared<MoreOperation<IntegerVariable, IntegerVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenLess, TokenInteger), std::make_shared<LessOperation<IntegerVariable, IntegerVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenMoreOrEqual, TokenInteger), std::make_shared<MoreOrEqualOperation<IntegerVariable, IntegerVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenLessOrEqual, TokenInteger), std::make_shared<LessOrEqualOperation<IntegerVariable, IntegerVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenEqual, TokenDouble), std::make_shared<EqualOperation<IntegerVariable, DoubleVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenUnequal, TokenDouble), std::make_shared<UnequalOperation<IntegerVariable, DoubleVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenMore, TokenDouble), std::make_shared<MoreOperation<IntegerVariable, DoubleVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenLess, TokenDouble), std::make_shared<LessOperation<IntegerVariable, DoubleVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenMoreOrEqual, TokenDouble), std::make_shared<MoreOrEqualOperation<IntegerVariable, DoubleVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenInteger, TokenLessOrEqual, TokenDouble), std::make_shared<LessOrEqualOperation<IntegerVariable, DoubleVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenDouble, TokenEqual, TokenInteger), std::make_shared<EqualOperation<DoubleVariable, IntegerVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenDouble, TokenUnequal, TokenInteger), std::make_shared<UnequalOperation<DoubleVariable, IntegerVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenDouble, TokenMore, TokenInteger), std::make_shared<MoreOperation<DoubleVariable, IntegerVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenDouble, TokenLess, TokenInteger), std::make_shared<LessOperation<DoubleVariable, IntegerVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenDouble, TokenMoreOrEqual, TokenInteger), std::make_shared<MoreOrEqualOperation<DoubleVariable, IntegerVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenDouble, TokenLessOrEqual, TokenInteger), std::make_shared<LessOrEqualOperation<DoubleVariable, IntegerVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenDouble, TokenEqual, TokenDouble), std::make_shared<EqualOperation<DoubleVariable, DoubleVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenDouble, TokenUnequal, TokenDouble), std::make_shared<UnequalOperation<DoubleVariable, DoubleVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenDouble, TokenMore, TokenDouble), std::make_shared<MoreOperation<DoubleVariable, DoubleVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenDouble, TokenLess, TokenDouble), std::make_shared<LessOperation<DoubleVariable, DoubleVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenDouble, TokenMoreOrEqual, TokenDouble), std::make_shared<MoreOrEqualOperation<DoubleVariable, DoubleVariable, BooleanVariable>>()));
    functions_types.insert(std::pair<TupleOfTokens, DataPtr>(TupleOfTokens(TokenDouble, TokenLessOrEqual, TokenDouble), std::make_shared<LessOrEqualOperation<DoubleVariable, DoubleVariable, BooleanVariable>>()));
}

[[no_return]] void Parser::Error(std::string lexem)
{
    throw lexem;
}

bool Parser::CheckToken(Type required_type) const
{
    return current_token.type == required_type;
}

bool Parser::TypeCheck() const
{
    return CheckToken(TokenBoolean) || CheckToken(TokenString) || CheckToken(TokenInteger) || CheckToken(TokenDouble);
}

bool Parser::ConstantCheck() const
{
    return CheckToken(TokenBooleanConst) || CheckToken(TokenStringConst) || CheckToken(TokenIntegerConst) || CheckToken(TokenDoubleConst);
}

bool Parser::MultiplyCheck() const
{
    return CheckToken(TokenMultiply) || CheckToken(TokenDivide) || CheckToken(TokenDiv) || CheckToken(TokenMod);
}

bool Parser::RelationOperatorCheck() const
{
    return CheckToken(TokenEqual) || CheckToken(TokenUnequal) || CheckToken(TokenMore) || CheckToken(TokenLess) || CheckToken(TokenMoreOrEqual) || CheckToken(TokenLessOrEqual);
}

void Parser::NextToken()
{
    if (!has_token)
    {
        try
        {
            current_token = flex.GetToken(&current_line);
        }
        catch (const std::string& exc)
        {
            Error("Line: " + std::to_string(current_line) + ";  Expected: " + exc);
        }
        has_token = !has_token;
    }
}

VariablePtr Parser::ConstantConversion(Token constant)
{
    if (constant.type == TokenBooleanConst)
    {
        BooleanVariable* new_variable = new BooleanVariable(constant.lexem, TokenBoolean, true, (constant.lexem == "true"));
        return VariablePtr(new_variable);
    }
    if (constant.type == TokenStringConst)
    {
        StringVariable* new_variable = new StringVariable(constant.lexem, TokenString, true, constant.lexem);
        return VariablePtr(new_variable);
    }
    if (constant.type == TokenIntegerConst)
    {
        IntegerVariable* new_variable = new IntegerVariable(constant.lexem, TokenInteger, true, std::stoi(constant.lexem));
        return VariablePtr(new_variable);
    }
    if (constant.type == TokenDoubleConst)
    {
        DoubleVariable* new_variable = new DoubleVariable(constant.lexem, TokenDouble, true, std::stod(constant.lexem));
        return VariablePtr(new_variable);
    }
}

void Parser::Program()
{
    if (current_token.type == TokenProgram)
    {
        has_token = !has_token;
        NextToken();
        if (!CheckToken(TokenIdentifier))
        {
            Error("Line: " + std::to_string(current_line) + ";  Expected: identifier");
        }
        has_token = !has_token;
        NextToken();
        if (!CheckToken(TokenSemicolon))
        {
            Error("Line: " + std::to_string(current_line) + ";  Expected: ;");
        }
        has_token = !has_token;
    }
    VariableDeclarationBlock();
    MainBlock();
}

void Parser::VariableDeclarationBlock()
{
    NextToken();
    if (CheckToken(TokenVar))
    {
        has_token = !has_token;
        NextToken();
        if (!CheckToken(TokenIdentifier))
        {
            Error("Line: " + std::to_string(current_line) + ";  Expected: identifier");
        }
        has_token = !has_token;
        VariableDeclaration();
        NextToken();
        while (CheckToken(TokenIdentifier))
        {
            has_token = !has_token;
            VariableDeclaration();
            NextToken();
        }
    }
}

void Parser::VariableDeclaration()
{
    std::vector<Token> variable_names;
    variable_names.emplace_back(current_token);
    NextToken();
    while (CheckToken(TokenComma))
    {
        has_token = !has_token;
        NextToken();
        if (!CheckToken(TokenIdentifier))
        {
            Error("Line: " + std::to_string(current_line) + ";  Expected: identifier");
        }
        variable_names.emplace_back(current_token);
        has_token = !has_token;
        NextToken();
    }
    if (CheckToken(TokenColon))
    {
        has_token = !has_token;
        NextToken();
        if (TypeCheck())
        {
            switch (current_token.type)
            {
                case TokenBoolean:
                    while (!variable_names.empty())
                    {
                        variables.insert(std::pair<std::string, VariablePtr>(variable_names.back().lexem, VariablePtr(new BooleanVariable(variable_names.back().lexem, TokenBoolean, false))));
                        variable_names.pop_back();
                    }
                    break;
                case TokenString:
                     while (!variable_names.empty())
                     {
                         variables.insert(std::pair<std::string, VariablePtr>(variable_names.back().lexem, VariablePtr(new StringVariable(variable_names.back().lexem, TokenString, false))));
                         variable_names.pop_back();
                     }
                    break;
                case TokenInteger:
                    while (!variable_names.empty())
                    {
                        variables.insert(std::pair<std::string, VariablePtr>(variable_names.back().lexem, VariablePtr(new IntegerVariable(variable_names.back().lexem, TokenInteger, false))));
                        variable_names.pop_back();
                    }
                    break;
                case TokenDouble:
                    while (!variable_names.empty())
                    {
                        variables.insert(std::pair<std::string, VariablePtr>(variable_names.back().lexem, VariablePtr(new DoubleVariable(variable_names.back().lexem, TokenDouble, false))));
                        variable_names.pop_back();
                    }
                    break;
            }
            has_token = !has_token;
            NextToken();
            if (!CheckToken(TokenSemicolon))
            {
                Error("Line: " + std::to_string(current_line) + ";  Expected: ;");
            }
            has_token = !has_token;
        }
        else
        {
            Error("Line: " + std::to_string(current_line) + ";  Expected: correct type");
        }
    }
    else
    {
        Error("Line: " + std::to_string(current_line) + ";  Expected: :");
    }
}

void Parser::MainBlock()
{
    if (CheckToken(TokenBegin))
    {
        has_token = !has_token;
        NextToken();
        while ((!CheckToken(TokenEnd)) && flex.HasLexem())
        {
            Statement();
            NextToken();
        }
        if (CheckToken(TokenEnd))
        {
            has_token = !has_token;
            NextToken();
            if (!CheckToken(TokenPoint))
            {
                Error("Line: " + std::to_string(current_line) + ";  Expected: . after end");
            }
            has_token = !has_token;
        }
        else
        {
            Error("Line: " + std::to_string(current_line) + ";  Expected: end");
        }
    }
    else
    {
        Error("Line: " + std::to_string(current_line) + ";  Expected: begin");
    }
}

void Parser::Statement()
{
    if (CheckToken(TokenFor))
    {
        has_token = !has_token;
        For();
    } else if (CheckToken(TokenWhile))
    {
        has_token = !has_token;
        While();
    } else if (CheckToken(TokenIf))
    {
        has_token = !has_token;
        If();
    } else if (CheckToken(TokenIdentifier))
    {
        has_token = !has_token;
        AssignmentStatement();
    } else if (CheckToken(TokenBegin))
    {
        has_token = !has_token;
        CompoundStatement();
    } else if (CheckToken(TokenWriteln))
    {
        has_token = !has_token;
        Writeln();
    } else
    {
        Error("Line: " + std::to_string(current_line) + ";  Expected: loop, or if, or assignment, or compound statement");
    }
}

void Parser::Writeln()
{
    NextToken();
    if (!CheckToken(TokenLeftParenthesis))
    {
        Error("Line: " + std::to_string(current_line) + ";  Expected: (");
    }
    has_token = !has_token;
    NextToken();
    if (!CheckToken(TokenIdentifier) && (!ConstantCheck()))
    {
        Error("Line: " + std::to_string(current_line) + ";  Expected: identifier or constant");
    }
    VariablePtr output_variable;
    if (CheckToken(TokenIdentifier))
    {
        output_variable = variables.at(current_token.lexem);
        commands.emplace_back(std::shared_ptr<Data>(new PushVariable(output_variable)));
    }
    else
    {
        output_variable = ConstantConversion(current_token);
        commands.emplace_back(DataPtr(new PushVariable(output_variable)));
    }
    switch (output_variable->GetType())
    {
        case TokenBoolean:
            commands.emplace_back(std::make_shared<Print<BooleanVariable>>());
            break;
        case TokenString:
            commands.emplace_back(std::make_shared<Print<StringVariable>>());
            break;
        case TokenInteger:
            commands.emplace_back(std::make_shared<Print<IntegerVariable>>());
            break;
        case TokenDouble:
            commands.emplace_back(std::make_shared<Print<DoubleVariable>>());
            break;
    }
    has_token = !has_token;
    NextToken();
    if (!CheckToken(TokenRightParenthesis))
    {
        Error("Line: " + std::to_string(current_line) + ";  Expected: )");
    }
    has_token = !has_token;
    NextToken();
    if (!CheckToken(TokenSemicolon))
    {
        Error("Line: " + std::to_string(current_line) + ";  Expected: ;");
    }
    has_token = !has_token;
}

void Parser::CompoundStatement()
{
    NextToken();
    while ((!CheckToken(TokenEnd)) && flex.HasLexem())
    {
        Statement();
        NextToken();
    }
    if (CheckToken(TokenEnd))
    {
        has_token = !has_token;
        NextToken();
        if (!CheckToken(TokenSemicolon))
        {
            Error("Line: " + std::to_string(current_line) + ";  Expected: ; after end");
        }
        has_token = !has_token;
    }
    else
    {
        Error("Line: " + std::to_string(current_line) + ";  Expected: end");
    }
}

void Parser::AssignmentStatement()
{
    if (variables.count(current_token.lexem) == 0)
    {
        Error("Line: " + std::to_string(current_line) + ";  Undefined identifier");
    }
    commands.emplace_back(DataPtr(new PushVariable(variables.at(current_token.lexem))));
    Type first_type = variables.at(current_token.lexem)->GetType();
    NextToken();
    if (CheckToken(TokenAssign))
    {
        has_token = !has_token;
        Type second_type = Expression();
        TupleOfTokens current_operation(first_type, TokenAssign, second_type);
        if (operations_type.count(current_operation) == 0)
        {
            Error("Line: " + std::to_string(current_line) + ";  Expected: correct types of operands in assignment");
        }
        commands.emplace_back(functions_types.at(current_operation));
        NextToken();
        if (!CheckToken(TokenSemicolon))
        {
            Error("Line: " + std::to_string(current_line) + ";  Expected: ;");
        }
        has_token = !has_token;
    }
    else
    {
        Error("Line: " + std::to_string(current_line) + ";  Expected: :=");
    }
}

Type Parser::Expression()
{
    Type return_type, operation_type, second_operand;
    NextToken();
    return_type = SimpleExpression();
    NextToken();
    while (RelationOperatorCheck())
    {
        operation_type = RelationOperator();
        NextToken();
        second_operand = SimpleExpression();
        TupleOfTokens current_operation(return_type, operation_type, second_operand);
        if (operations_type.count(current_operation) == 0)
        {
            Error("Line: " + std::to_string(current_line) + ";  Expected: correct types of operands in relation operation");
        }
        return_type = operations_type.at(current_operation);
        commands.emplace_back(functions_types.at(current_operation));
        NextToken();
    }
    return return_type;
}

Type Parser::RelationOperator()
{
    has_token = !has_token;
    return current_token.type;
}

Type Parser::SimpleExpression()
{
    Type return_type, operation_type, second_operand;
    if (CheckToken(TokenIdentifier) || ConstantCheck() || CheckToken(TokenLeftParenthesis))
    {
        return_type = Term();
    }
    else if (CheckToken(TokenPlus) || CheckToken(TokenMinus))
    {
        Token unary_zero;
        unary_zero.lexem = "0";
        unary_zero.type = TokenIntegerConst;
        commands.emplace_back(DataPtr(new PushVariable(ConstantConversion(unary_zero))));
        operation_type = Sign();
        NextToken();
        if (CheckToken(TokenIdentifier) || ConstantCheck() || CheckToken(TokenLeftParenthesis))
        {
            return_type = Term();
        }
        else
        {
            Error("Line: " + std::to_string(current_line) + ";  Expected: term");
        }
        TupleOfTokens current_operation(TokenInteger, operation_type, return_type);
        commands.emplace_back(functions_types.at(current_operation));
    }
    else
    {
        Error("Line: " + std::to_string(current_line) + ";  Expected: sign or term");
    }
    NextToken();
    while (CheckToken(TokenPlus) || CheckToken(TokenMinus))
    {
        operation_type = Sign();
        NextToken();
        if (CheckToken(TokenIdentifier) || ConstantCheck() || CheckToken(TokenLeftParenthesis))
        {
            second_operand = Term();
        }
        else
        {
            Error("Line: " + std::to_string(current_line) + ";  Expected: term");
        }
        TupleOfTokens current_operation(return_type, operation_type, second_operand);
        if (operations_type.count(current_operation) == 0)
        {
            Error("Line: " + std::to_string(current_line) + ";  Expected: correct types of operands in plus/minus operation");
        }
        return_type = operations_type.at(current_operation);
        commands.emplace_back(functions_types.at(current_operation));
        NextToken();
    }
    return return_type;
}

Type Parser::Sign()
{
    has_token = !has_token;
    return current_token.type;
}

Type Parser::Term()
{
    Type return_type = Factor();
    NextToken();
    while (MultiplyCheck())
    {
        Type operation_type = MultiplicationOperator();
        NextToken();
        Type second_operand;
        if (CheckToken(TokenIdentifier) || ConstantCheck() || CheckToken(TokenLeftParenthesis))
        {
             second_operand = Factor();
        }
        else
        {
            Error("Line: " + std::to_string(current_line) + ";  Expected: factor");
        }
        TupleOfTokens current_operation(return_type, operation_type, second_operand);
        if (operations_type.count(current_operation) == 0)
        {
            Error("Line: " + std::to_string(current_line) + ";  Expected: correct types of operands in multiplication operation");
        }
        return_type = operations_type.at(current_operation);
        commands.emplace_back(functions_types.at(current_operation));
        NextToken();
    }
    return return_type;
}

Type Parser::MultiplicationOperator()
{
    has_token = !has_token;
    return current_token.type;
}

Type Parser::Factor()
{
    if (CheckToken(TokenIdentifier))
    {
        has_token = !has_token;
        if (variables.count(current_token.lexem) == 0)
        {
            Error("Line: " + std::to_string(current_line) + ";  Undefined identifier");
        }
        commands.emplace_back(DataPtr(new PushVariable(variables.at(current_token.lexem))));
        return variables.at(current_token.lexem)->GetType();
    }
    if (ConstantCheck())
    {
        has_token = !has_token;
        std::shared_ptr<AbstractVariable> temporary_ptr = ConstantConversion(current_token);
        commands.emplace_back(new PushVariable(temporary_ptr));
        return temporary_ptr->GetType();
    }
    if (CheckToken(TokenLeftParenthesis))
    {
        has_token = !has_token;
        Type return_type = Expression();
        NextToken();
        if (!CheckToken(TokenRightParenthesis))
        {
            Error("Line: " + std::to_string(current_line) + ";  Expected: )");
        }
        has_token = !has_token;
        return return_type;
    }
    Error("Line: " + std::to_string(current_line) + ";  Expected: identifier or constant or expression");
}

void Parser::If()
{
    Type condition_type = Expression();
    if (condition_type != TokenBoolean)
    {
        Error("Line: " + std::to_string(current_line) + ";  Expected: boolean expression in if");
    }
    OperationIndex remember_position = commands.size();
    commands.emplace_back(std::shared_ptr<Data>(new Data()));
    if (CheckToken(TokenThen))
    {
        has_token = !has_token;
        NextToken();
        Statement();
        commands[remember_position] = std::shared_ptr<Data>(new IfGo(commands.size(), TokenIf));
        NextToken();
        if (CheckToken(TokenElse))
        {
            remember_position = commands.size();
            commands.emplace_back(std::shared_ptr<Data>(new Data()));
            has_token = !has_token;
            NextToken();
            Statement();
            commands[remember_position] = std::shared_ptr<Data>(new Go(commands.size(), TokenGoTo));
        }
    }
    else
    {
        Error("Line: " + std::to_string(current_line) + ";  Expected: then");
    }

}

void Parser::While()
{
    OperationIndex start_position = commands.size();
    NextToken();
    Expression();
    OperationIndex if_position = commands.size();
    commands.emplace_back(std::shared_ptr<Data>(new Data()));
    NextToken();
    if (!CheckToken(TokenDo))
    {
        Error("Line: " + std::to_string(current_line) + ";  Expected: do");
    }
    has_token = !has_token;
    NextToken();
    Statement();
    commands.emplace_back(std::shared_ptr<Data>(new Go(start_position, TokenGoTo)));
    commands[if_position] = std::shared_ptr<Data>(new IfGo(commands.size(), TokenIf));
}

void Parser::For()
{
    NextToken();
    if (CheckToken(TokenIdentifier))
    {
        has_token = !has_token;
        NextToken();
        if (!CheckToken(TokenAssign))
        {
            Error("Line: " + std::to_string(current_line) + ";  Expected: :=");
        }
        has_token = !has_token;
        NextToken();
        ForList();
        NextToken();
        if (!CheckToken(TokenDo))
        {
            Error("Line: " + std::to_string(current_line) + ";  Expected: do");
        }
        has_token = !has_token;
        NextToken();
        Statement();
    }
    else
    {
        Error("Line: " + std::to_string(current_line) + ";  Expected: identifier");
    }
}

void Parser::ForList()
{
    Expression();
    NextToken();
    if (CheckToken(TokenTo) || CheckToken(TokenDownTo))
    {
        has_token = !has_token;
        NextToken();
        Expression();
    }
    else
    {
        Error("Line: " + std::to_string(current_line) + ";  Expected: to or downto");
    }
}