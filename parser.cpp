//
// Created by ghost on 03.05.2020.
//

#include "parser.h"

Parser::Parser(std::string file) : flex(file)
{
    FillTypeOperands();
    current_token = flex.GetToken();
    has_token = true;
}

void Parser::Start()
{
    Program();
    if ((flex.GetToken().type != Token::TokenEOF) || has_token)
    {
        Error("no lexems after end");
    }
}

void Parser::TestOutput() const
{
    std::cout << "VARIABLES\n";
    std::cout << "1. " << variables.at("x")->GetName() << " " << variables.at("x")->GetType() << std::endl;
    std::cout << "1. " << variables.at("y")->GetName() << " " << variables.at("y")->GetType() << std::endl;
    std::cout << "1. " << variables.at("z")->GetName() << " " << variables.at("z")->GetType() << std::endl;
    std::cout << "\n";
    for (int i = 0; i < commands.size(); ++i)
    {
        std::cout << i << ". " << commands[i]->GetType();
        if ((commands[i]->GetType() == Token::TokenIf) || (commands[i]->GetType() == Token::TokenGoTo))
        {
            std::cout << " " << static_cast<Go*>(commands[i].get())->GetIndex();
        }
        std::cout << std::endl;
    }
}

void Parser::FillTypeOperands()
{
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenBoolean, Token::TokenAssign, Token::TokenBoolean), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenString, Token::TokenAssign, Token::TokenString), Token::TokenString));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenAssign, Token::TokenInteger), Token::TokenInteger));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenAssign, Token::TokenDouble), Token::TokenDouble));

    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenString, Token::TokenPlus, Token::TokenString), Token::TokenString));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenPlus, Token::TokenInteger), Token::TokenInteger));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenPlus, Token::TokenDouble), Token::TokenDouble));

    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenMinus, Token::TokenInteger), Token::TokenInteger));

    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenPlus, Token::TokenDouble), Token::TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenMinus, Token::TokenDouble), Token::TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenPlus, Token::TokenInteger), Token::TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenMinus, Token::TokenInteger), Token::TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenPlus, Token::TokenDouble), Token::TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenMinus, Token::TokenDouble), Token::TokenDouble));

    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenMultiply, Token::TokenInteger), Token::TokenInteger));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenDiv, Token::TokenInteger), Token::TokenInteger));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenMod, Token::TokenInteger), Token::TokenInteger));

    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenDivide, Token::TokenInteger), Token::TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenDivide, Token::TokenDouble), Token::TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenMultiply, Token::TokenDouble), Token::TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenDivide, Token::TokenInteger), Token::TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenMultiply, Token::TokenInteger), Token::TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenDivide, Token::TokenDouble), Token::TokenDouble));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenMultiply, Token::TokenDouble), Token::TokenDouble));

    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenBoolean, Token::TokenEqual, Token::TokenBoolean), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenBoolean, Token::TokenUnequal, Token::TokenBoolean), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenBoolean, Token::TokenLess, Token::TokenBoolean), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenBoolean, Token::TokenMore, Token::TokenBoolean), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenBoolean, Token::TokenLessOrEqual, Token::TokenBoolean), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenBoolean, Token::TokenMoreOrEqual, Token::TokenBoolean), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenString, Token::TokenEqual, Token::TokenString), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenString, Token::TokenUnequal, Token::TokenString), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenString, Token::TokenLess, Token::TokenString), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenString, Token::TokenMore, Token::TokenString), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenString, Token::TokenLessOrEqual, Token::TokenString), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenString, Token::TokenMoreOrEqual, Token::TokenString), Token::TokenBoolean));

    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenEqual, Token::TokenInteger), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenUnequal, Token::TokenInteger), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenLess, Token::TokenInteger), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenMore, Token::TokenInteger), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenLessOrEqual, Token::TokenInteger), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenMoreOrEqual, Token::TokenInteger), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenEqual, Token::TokenDouble), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenUnequal, Token::TokenDouble), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenLess, Token::TokenDouble), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenMore, Token::TokenDouble), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenLessOrEqual, Token::TokenDouble), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenInteger, Token::TokenMoreOrEqual, Token::TokenDouble), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenEqual, Token::TokenInteger), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenUnequal, Token::TokenInteger), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenLess, Token::TokenInteger), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenMore, Token::TokenInteger), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenLessOrEqual, Token::TokenInteger), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenMoreOrEqual, Token::TokenInteger), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenEqual, Token::TokenDouble), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenUnequal, Token::TokenDouble), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenLess, Token::TokenDouble), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenMore, Token::TokenDouble), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenLessOrEqual, Token::TokenDouble), Token::TokenBoolean));
    operations_type.insert(std::pair<TupleOfTokens, Token::Type>(TupleOfTokens(Token::TokenDouble, Token::TokenMoreOrEqual, Token::TokenDouble), Token::TokenBoolean));
}

void Parser::Error(std::string lexem) const
{
    std::cout << "Expected: " << lexem; // TODO: errors
    exit(0);
}

bool Parser::CheckToken(Token::Type required_type) const
{
    return current_token.type == required_type;
}

bool Parser::TypeCheck() const
{
    return CheckToken(Token::TokenBoolean) || CheckToken(Token::TokenString) || CheckToken(Token::TokenInteger) || CheckToken(Token::TokenDouble);
}

bool Parser::ConstantCheck() const
{
    return CheckToken(Token::TokenBooleanConst) || CheckToken(Token::TokenStringConst) || CheckToken(Token::TokenIntegerConst) || CheckToken(Token::TokenDoubleConst);
}

bool Parser::MultiplyCheck() const
{
    return CheckToken(Token::TokenMultiply) || CheckToken(Token::TokenDivide) || CheckToken(Token::TokenDiv) || CheckToken(Token::TokenMod);
}

bool Parser::RelationOperatorCheck() const
{
    return CheckToken(Token::TokenEqual) || CheckToken(Token::TokenUnequal) || CheckToken(Token::TokenMore) || CheckToken(Token::TokenLess) || CheckToken(Token::TokenMoreOrEqual) || CheckToken(Token::TokenLessOrEqual);
}

void Parser::NextToken()
{
    if (!has_token)
    {
        current_token = flex.GetToken();
        has_token = !has_token;
    }
}

std::shared_ptr<AbstractVariable> Parser::ConstantConversion(Token constant)
{
    if (constant.type == Token::TokenBooleanConst)
    {
        BooleanVariable* new_variable = new BooleanVariable(&constant.lexem, Token::TokenBoolean, true, (constant.lexem == "true"));
        return std::shared_ptr<AbstractVariable>(new_variable);
    }
    if (constant.type == Token::TokenStringConst)
    {
        StringVariable* new_variable = new StringVariable(&constant.lexem, Token::TokenString, true, constant.lexem);
        return std::shared_ptr<AbstractVariable>(new_variable);
    }
    if (constant.type == Token::TokenIntegerConst)
    {
        IntegerVariable* new_variable = new IntegerVariable(&constant.lexem, Token::TokenInteger, true, std::stoi(constant.lexem));
        return std::shared_ptr<AbstractVariable>(new_variable);
    }
    if (constant.type == Token::TokenDoubleConst)
    {
        DoubleVariable* new_variable = new DoubleVariable(&constant.lexem, Token::TokenDouble, true, std::stod(constant.lexem));
        return std::shared_ptr<AbstractVariable>(new_variable);
    }
}

void Parser::Program()
{
    if (current_token.type == Token::TokenProgram)
    {
        has_token = !has_token;
        NextToken();
        if (!CheckToken(Token::TokenIdentifier))
        {
            Error("Identifier");
        }
        has_token = !has_token;
        NextToken();
        if (!CheckToken(Token::TokenSemicolon))
        {
            Error(";");
        }
        has_token = !has_token;
    }
    VariableDeclarationBlock();
    MainBlock();
}

void Parser::VariableDeclarationBlock()
{
    NextToken();
    if (CheckToken(Token::TokenVar))
    {
        has_token = !has_token;
        NextToken();
        if (!CheckToken(Token::TokenIdentifier))
        {
            Error("Identifier");
        }
        has_token = !has_token;
        VariableDeclaration();
        NextToken();
        while (CheckToken(Token::TokenIdentifier))
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
    while (CheckToken(Token::TokenComma))
    {
        has_token = !has_token;
        NextToken();
        if (!CheckToken(Token::TokenIdentifier))
        {
            Error("Identifier");
        }
        variable_names.emplace_back(current_token);
        has_token = !has_token;
        NextToken();
    }
    if (CheckToken(Token::TokenColon))
    {
        has_token = !has_token;
        NextToken();
        if (TypeCheck())
        {
            switch (current_token.type)
            {
                case Token::TokenBoolean:
                    while (!variable_names.empty())
                    {
                        variables.insert(std::pair<std::string, std::shared_ptr<AbstractVariable>>(variable_names.back().lexem, std::shared_ptr<AbstractVariable>(
                                static_cast<AbstractVariable*>(new BooleanVariable(&variable_names.back().lexem, Token::TokenBoolean, false)))));
                        variable_names.pop_back();
                    }
                    break;
                case Token::TokenString:
                     while (!variable_names.empty())
                     {
                         variables.insert(std::pair<std::string, std::shared_ptr<AbstractVariable>>(variable_names.back().lexem, std::shared_ptr<AbstractVariable>(
                                 static_cast<AbstractVariable*>(new StringVariable(&variable_names.back().lexem, Token::TokenString, false)))));
                         variable_names.pop_back();
                     }
                    break;
                case Token::TokenInteger:
                    while (!variable_names.empty())
                    {
                        variables.insert(std::pair<std::string, std::shared_ptr<AbstractVariable>>(variable_names.back().lexem, std::shared_ptr<AbstractVariable>(
                                static_cast<AbstractVariable*>(new IntegerVariable(&variable_names.back().lexem, Token::TokenInteger, false)))));
                        variable_names.pop_back();
                    }
                    break;
                case Token::TokenDouble:
                    while (!variable_names.empty())
                    {
                        variables.insert(std::pair<std::string, std::shared_ptr<AbstractVariable>>(variable_names.back().lexem, std::shared_ptr<AbstractVariable>(
                                static_cast<AbstractVariable*>(new DoubleVariable(&variable_names.back().lexem, Token::TokenDouble, false)))));
                        variable_names.pop_back();
                    }
                    break;
            }
            has_token = !has_token;
            NextToken();
            if (!CheckToken(Token::TokenSemicolon))
            {
                Error(";");
            }
            has_token = !has_token;
        }
        else
        {
            Error("correct type");
        }
    }
    else
    {
        Error(":");
    }
}

void Parser::MainBlock()
{
    if (CheckToken(Token::TokenBegin))
    {
        has_token = !has_token;
        NextToken();
        while ((!CheckToken(Token::TokenEnd)) && flex.HasLexem())
        {
            Statement();
            NextToken();
        }
        if (CheckToken(Token::TokenEnd))
        {
            has_token = !has_token;
            NextToken();
            if (!CheckToken(Token::TokenPoint))
            {
                Error(".");
            }
            has_token = !has_token;
        }
        else
        {
    void FillTypeOperands();
            Error("end");
        }
    }
    else
    {
        Error("begin");
    }
}

void Parser::Statement()
{
    if (CheckToken(Token::TokenFor))
    {
        has_token = !has_token;
        For();
    } else if (CheckToken(Token::TokenWhile))
    {
        has_token = !has_token;
        While();
    } else if (CheckToken(Token::TokenIf))
    {
        has_token = !has_token;
        If();
    } else if (CheckToken(Token::TokenIdentifier))
    {
        has_token = !has_token;
        AssignmentStatement();
    } else if (CheckToken(Token::TokenBegin))
    {
        has_token = !has_token;
        CompoundStatement();
    } else if (CheckToken(Token::TokenWriteln))
    {
        has_token = !has_token;
        Writeln();
    } else
    {
        Error("loop, or if, or assignment, or compound statement");
    }
}

void Parser::Writeln()
{
    NextToken();
    if (!CheckToken(Token::TokenLeftParenthesis))
    {
        Error("(");
    }
    has_token = !has_token;
    NextToken();
    if (!CheckToken(Token::TokenIdentifier) && (!ConstantCheck()))
    {
        Error("identifier or constant");
    }
    if (CheckToken(Token::TokenIdentifier))
    {
        commands.emplace_back(variables.at(current_token.lexem));
    }
    else
    {
        commands.emplace_back(ConstantConversion(current_token));
    }
    commands.emplace_back(std::shared_ptr<Context>(new Print()));
    has_token = !has_token;
    NextToken();
    if (!CheckToken(Token::TokenRightParenthesis))
    {
        Error(")");
    }
    has_token = !has_token;
    NextToken();
    if (!CheckToken(Token::TokenSemicolon))
    {
        Error(";");
    }
    has_token = !has_token;
}

void Parser::CompoundStatement()
{
    NextToken();
    while ((!CheckToken(Token::TokenEnd)) && flex.HasLexem())
    {
        Statement();
        NextToken();
    }
    if (CheckToken(Token::TokenEnd))
    {
        has_token = !has_token;
        NextToken();
        if (!CheckToken(Token::TokenSemicolon))
        {
            Error(";");
        }
        has_token = !has_token;
    }
    else
    {
        Error("end");
    }
}

void Parser::AssignmentStatement()
{
    commands.emplace_back(variables.at(current_token.lexem));
    Token::Type first_type = variables.at(current_token.lexem)->GetType();
    NextToken();
    if (CheckToken(Token::TokenAssign))
    {
        has_token = !has_token;
        Token::Type second_type = Expression();
        if (operations_type.count(TupleOfTokens(first_type, Token::TokenAssign, second_type)) == 0)
        {
            Error("correct types of operands in assignment");
        }
        commands.emplace_back(std::shared_ptr<Context>(new AssignmentOperation()));
        NextToken();
        if (!CheckToken(Token::TokenSemicolon))
        {
            Error(";");
        }
        has_token = !has_token;
    }
    else
    {
        Error(":=");
    }
}

Token::Type Parser::Expression()
{
    Token::Type return_type, operation_type, second_operand;
    NextToken();
    return_type = SimpleExpression();
    NextToken();
    while (RelationOperatorCheck())
    {
        operation_type = RelationOperator();
        NextToken();
        second_operand = SimpleExpression();
        if (operations_type.count(TupleOfTokens(return_type, operation_type, second_operand)) == 0)
        {
            Error("correct types of operands in relation operation");
        }
        return_type = operations_type.at(TupleOfTokens(return_type, operation_type, second_operand));
        switch (operation_type)
        {
            case Token::TokenEqual:
                commands.emplace_back(std::shared_ptr<Context>(new EqualOperation()));
                break;
            case Token::TokenUnequal:
                commands.emplace_back(std::shared_ptr<Context>(new UnequalOperation()));
                break;
            case Token::TokenMore:
                commands.emplace_back(std::shared_ptr<Context>(new MoreOperation()));
                break;
            case Token::TokenLess:
                commands.emplace_back(std::shared_ptr<Context>(new LessOperation()));
                break;
            case Token::TokenMoreOrEqual:
                commands.emplace_back(std::shared_ptr<Context>(new MoreOrEqualOperation()));
                break;
            case Token::TokenLessOrEqual:
                commands.emplace_back(std::shared_ptr<Context>(new LessOrEqualOperation()));
                break;
        }
        NextToken();
    }
    return return_type;
}

Token::Type Parser::RelationOperator()
{
    has_token = !has_token;
    return current_token.type;
}

Token::Type Parser::SimpleExpression()
{
    Token::Type return_type, operation_type, second_operand;
    if (CheckToken(Token::TokenIdentifier) || ConstantCheck() || CheckToken(Token::TokenLeftParenthesis))
    {
        return_type = Term();
    }
    else if (CheckToken(Token::TokenPlus) || CheckToken(Token::TokenMinus))
    {
        Token unary_zero;
        unary_zero.lexem = "0";
        unary_zero.type = Token::TokenIntegerConst;
        commands.emplace_back(ConstantConversion(unary_zero));
        operation_type = Sign();
        NextToken();
        if (CheckToken(Token::TokenIdentifier) || ConstantCheck() || CheckToken(Token::TokenLeftParenthesis))
        {
            return_type = Term();
        }
        else
        {
            Error("term");
        }
        switch (operation_type)
        {
            case Token::TokenPlus:
                commands.emplace_back(std::shared_ptr<Context>(new PlusOperation()));
                break;
            case Token::TokenMinus:
                commands.emplace_back(std::shared_ptr<Context>(new MinusOperation()));
                break;
        }
    }
    else
    {
        Error("sign or term");
    }
    NextToken();
    while (CheckToken(Token::TokenPlus) || CheckToken(Token::TokenMinus))
    {
        operation_type = Sign();
        NextToken();
        if (CheckToken(Token::TokenIdentifier) || ConstantCheck() || CheckToken(Token::TokenLeftParenthesis))
        {
            second_operand = Term();
        }
        else
        {
            Error("term");
        }
        if (operations_type.count(TupleOfTokens(return_type, operation_type, second_operand)) == 0)
        {
            Error("correct types of operands in plus/minus operation");
        }
        return_type = operations_type.at(TupleOfTokens(return_type, operation_type, second_operand));
        switch (operation_type)
        {
            case Token::TokenPlus:
                commands.emplace_back(std::shared_ptr<Context>(new PlusOperation()));
                break;
            case Token::TokenMinus:
                commands.emplace_back(std::shared_ptr<Context>(new MinusOperation()));
                break;
        }
        NextToken();
    }
    return return_type;
}

Token::Type Parser::Sign()
{
    has_token = !has_token;
    return current_token.type;
}

Token::Type Parser::Term()
{
    Token::Type return_type = Factor();
    NextToken();
    while (MultiplyCheck())
    {
        Token::Type operation_type = MultiplicationOperator();
        NextToken();
        Token::Type second_operand;
        if (CheckToken(Token::TokenIdentifier) || ConstantCheck() || CheckToken(Token::TokenLeftParenthesis))
        {
             second_operand = Factor();
        }
        else
        {
            Error("factor");
        }
        if (operations_type.count(TupleOfTokens(return_type, operation_type, second_operand)) == 0)
        {
            Error("correct types of operands in multiplication operation");
        }
        return_type = operations_type.at(TupleOfTokens(return_type, operation_type, second_operand));
        switch (operation_type)
        {
            case Token::TokenMultiply:
                commands.emplace_back(std::shared_ptr<Context>(new MultiplyOperation()));
                break;
            case Token::TokenDivide:
                commands.emplace_back(std::shared_ptr<Context>(new DivideOperation()));
                break;
            case Token::TokenDiv:
                commands.emplace_back(std::shared_ptr<Context>(new DivOperation()));
                break;
            case Token::TokenMod:
                commands.emplace_back(std::shared_ptr<Context>(new ModOperation()));
                break;
        }
        NextToken();
    }
    return return_type;
}

Token::Type Parser::MultiplicationOperator()
{
    has_token = !has_token;
    return current_token.type;
}

Token::Type Parser::Factor()
{
    if (CheckToken(Token::TokenIdentifier))
    {
        has_token = !has_token;
        commands.emplace_back(variables.at(current_token.lexem));
        return variables.at(current_token.lexem)->GetType();
    }
    if (ConstantCheck())
    {
        has_token = !has_token;
        std::shared_ptr<AbstractVariable> temporary_ptr = ConstantConversion(current_token);
        commands.emplace_back(temporary_ptr);
        return temporary_ptr->GetType();
    }
    if (CheckToken(Token::TokenLeftParenthesis))
    {
        has_token = !has_token;
        Token::Type return_type = Expression();
        NextToken();
        if (!CheckToken(Token::TokenRightParenthesis))
        {
            Error(")");
        }
        has_token = !has_token;
        return return_type;
    }
    else
    {
        Error("WTF!?");
    }
}

void Parser::If()
{
    Token::Type condition_type = Expression();
    if (condition_type != Token::TokenBoolean)
    {
        Error("boolean expression in if");
    }
    OperationIndex remember_position = commands.size();
    commands.emplace_back(std::shared_ptr<Context>(new Context()));
    if (CheckToken(Token::TokenThen))
    {
        has_token = !has_token;
        NextToken();
        Statement();
        commands[remember_position] = std::shared_ptr<Context>(new IfGo(commands.size(), Token::TokenIf));
        NextToken();
        if (CheckToken(Token::TokenElse))
        {
            commands[remember_position] = std::shared_ptr<Context>(new IfGo(commands.size() + 1, Token::TokenIf));
            remember_position = commands.size();
            commands.emplace_back(std::shared_ptr<Context>(new Context()));
            has_token = !has_token;
            NextToken();
            Statement();
            commands[remember_position] = std::shared_ptr<Context>(new Go(commands.size(), Token::TokenGoTo));
        }
    }
    else
    {
        Error("then");
    }

}

void Parser::While()
{
    NextToken();
    Expression();
    OperationIndex remember_position = commands.size();
    commands.emplace_back(std::shared_ptr<Context>(new Context()));
    NextToken();
    if (!CheckToken(Token::TokenDo))
    {
        Error("do");
    }
    has_token = !has_token;
    NextToken();
    Statement();
    commands.emplace_back(std::shared_ptr<Context>(new Go(remember_position, Token::TokenGoTo)));
    commands[remember_position] = std::shared_ptr<Context>(new IfGo(commands.size(), Token::TokenIf));
}

void Parser::For()
{
    NextToken();
    if (CheckToken(Token::TokenIdentifier))
    {
        has_token = !has_token;
        NextToken();
        if (!CheckToken(Token::TokenAssign))
        {
            Error(":=");
        }
        has_token = !has_token;
        NextToken();
        ForList();
        NextToken();
        if (!CheckToken(Token::TokenDo))
        {
            Error("do");
        }
        has_token = !has_token;
        NextToken();
        Statement();
    }
    else
    {
        Error("Identifier");
    }
}

void Parser::ForList()
{
    Expression();
    NextToken();
    if (CheckToken(Token::TokenTo) || CheckToken(Token::TokenDownTo))
    {
        has_token = !has_token;
        NextToken();
        Expression();
    }
    else
    {
        Error("to or downto");
    }
}