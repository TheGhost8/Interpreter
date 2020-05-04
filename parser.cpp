//
// Created by ghost on 03.05.2020.
//

#include "parser.h"

Parser::Parser(std::string file) : flex(file)
{
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
    NextToken();
    while (CheckToken(Token::TokenComma))
    {
        has_token = !has_token;
        NextToken();
        if (!CheckToken(Token::TokenIdentifier))
        {
            Error("Identifier");
        }
        has_token = !has_token;
        NextToken();
    }
    if (CheckToken(Token::TokenColon))
    {
        has_token = !has_token;
        NextToken();
        if (TypeCheck())
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
    if (!CheckToken(Token::TokenIdentifier) && !(ConstantCheck()))
    {
        Error("identifier or constant");
    }
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
    NextToken();
    if (CheckToken(Token::TokenAssign))
    {
        has_token = !has_token;
        Expression();
        // Expression left token because of * in rule
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

void Parser::Expression()
{
    NextToken();
    SimpleExpression();
    while (RelationOperatorCheck())
    {
        RelationOperator();
        NextToken();
        SimpleExpression();
    }
}

void Parser::RelationOperator()
{
    has_token = !has_token;
    // = <> ...
}

void Parser::SimpleExpression()
{
    if (CheckToken(Token::TokenIdentifier) || ConstantCheck() || CheckToken(Token::TokenLeftParenthesis))
    {
        Term();
    }
    else if (CheckToken(Token::TokenPlus) || CheckToken(Token::TokenMinus))
    {
        Sign();
        NextToken();
        if (CheckToken(Token::TokenIdentifier) || ConstantCheck() || CheckToken(Token::TokenLeftParenthesis))
        {
            Term();
        }
        else
        {
            Error("term");
        }
    }
    else
    {
        Error("sign or term");
    }
    while (CheckToken(Token::TokenPlus) || CheckToken(Token::TokenMinus))
    {
        Sign();
        NextToken();
        if (CheckToken(Token::TokenIdentifier) || ConstantCheck() || CheckToken(Token::TokenLeftParenthesis))
        {
            Term();
        }
        else
        {
            Error("term");
        }
    }
}

void  Parser::Sign()
{
    has_token = !has_token;
    //signs + -
}

void Parser::Term()
{
    Factor();
    NextToken();
    while (MultiplyCheck())
    {
        MultiplicationOperator();
        NextToken();
        if (CheckToken(Token::TokenIdentifier) || ConstantCheck() || CheckToken(Token::TokenLeftParenthesis))
        {
            Factor();
        }
        else
        {
            Error("factor");
        }
        NextToken();
    }
}

void Parser::MultiplicationOperator()
{
    has_token = !has_token;
    // * / div mod
}

void Parser::Factor()
{
    has_token = !has_token;
    //identifiers and constants
    if (CheckToken(Token::TokenLeftParenthesis))
    {
        Expression();
        NextToken();
        if (!CheckToken(Token::TokenRightParenthesis))
        {
            Error(")");
        }
        has_token = !has_token;
    }
}

void Parser::If()
{
    Expression();
    if (CheckToken(Token::TokenThen))
    {
        has_token = !has_token;
        NextToken();
        Statement();
        NextToken();
        if (CheckToken(Token::TokenElse))
        {
            has_token = !has_token;
            NextToken();
            Statement();
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
    if (!CheckToken(Token::TokenWhile))
    {
        Error("while");
    }
    has_token = !has_token;
    NextToken();
    Expression();
    NextToken();
    if (!CheckToken(Token::TokenDo))
    {
        Error("do");
    }
    has_token = !has_token;
    NextToken();
    Statement();
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