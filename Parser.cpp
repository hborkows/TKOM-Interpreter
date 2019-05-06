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
    auto* program = new StatementBlock();

}

void Parser::getNextToken()
{
    bufferedToken = lexer->nextToken();
}

bool Parser::accept(const Token &token, const std::initializer_list<Token> &acceptable)
{
    for(auto it: acceptable)
    {
        if(it.type == token.type)
            return true;
    }
    return false;
}

StatementBlock *Parser::parseBlock()
{
    //TODO
}

Assignable *Parser::parseAssignable()
{
    //TODO
}

Assignment *Parser::parseAssignment()
{
    //TODO
}

Condition *Parser::parseCondition()
{
    //TODO
}

Expression *Parser::parseExpression()
{
    //TODO
}

ForStatement *Parser::parseForStatement()
{
    //TODO
}

FunctionCall *Parser::parseFunCall()
{
    //TODO
}

IfStatement *Parser::parseIfStatement()
{
    //TODO
}

ReturnStatement *Parser::parseReturnStatement()
{
    //TODO
}

Variable *Parser::parseVariable()
{
    //TODO
}

VariableDeclaration *Parser::parseVariableDeclaration()
{
    //TODO
}

WhileStatement *Parser::parseWhileStatement()
{
    //TODO
}
