//
// Created by hborkows on 05.05.19.
//

#include "Parser.h"

Parser::Parser(Lexer *lexer): bufferedToken()
{
    this->lexer = lexer;
}

Parser::~Parser()
{
    delete lexer;
}

ASTNode *Parser::parse()
{
    return nullptr;
}

bool Parser::accept(const Token &token, const std::initializer_list<Token> &acceptable)
{
    return false;
}

Assignable *Parser::parseAssignable()
{
    return nullptr;
}

Assignment *Parser::parseAssignment()
{
    return nullptr;
}

Condition *Parser::parseCondition()
{
    return nullptr;
}

Expression *Parser::parseExpression()
{
    return nullptr;
}

ForStatement *Parser::parseForStatement()
{
    return nullptr;
}

FunctionCall *Parser::parseFunCall()
{
    return nullptr;
}

IfStatement *Parser::parseIfStatement()
{
    return nullptr;
}

ReturnStatement *Parser::parseReturnStatement()
{
    return nullptr;
}

Variable *Parser::parseVariable()
{
    return nullptr;
}

VariableDeclaration *Parser::parseVariableDeclaration()
{
    return nullptr;
}

WhileStatement *Parser::parseWhileStatement()
{
    return nullptr;
}
