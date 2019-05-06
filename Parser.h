//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_PARSER_H
#define TKOM_INTERPRETER_PARSER_H

#include <vector>
#include "Lexer.h"
#include "AST/ASTNode.h"
#include "AST/Assignable.h"
#include "AST/Assignment.h"
#include "AST/Condition.h"
#include "AST/Expression.h"
#include "AST/ForStatement.h"
#include "AST/FunctionCall.h"
#include "AST/IfStatement.h"
#include "AST/ReturnStatement.h"
#include "AST/VariableDeclaration.h"
#include "AST/WhileStatement.h"

class Parser
{
public:
    explicit Parser(Lexer* lexer);

    ~Parser();

    ASTNode* parse();

private:
    Lexer* lexer;

    Token bufferedToken;

    bool accept(const Token& token, const std::initializer_list<Token>& acceptable);

    Assignable* parseAssignable();

    Assignment* parseAssignment();

    Condition* parseCondition();

    Expression* parseExpression();

    ForStatement* parseForStatement();

    FunctionCall* parseFunCall();

    IfStatement* parseIfStatement();

    ReturnStatement* parseReturnStatement();

    Variable* parseVariable();

    VariableDeclaration* parseVariableDeclaration();

    WhileStatement* parseWhileStatement();
};


#endif //TKOM_INTERPRETER_PARSER_H
