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
#include "Tracer.h"
#include "AST/FunctionDefinition.h"

class Parser
{
public:
    explicit Parser(Lexer* lexer);

    ~Parser();

    ASTNode* parse();

private:
    Lexer* lexer;

    Tracer* tracer;

    Token bufferedToken;

    void getNextToken();

    bool accept(const std::initializer_list<LexType>& acceptable);

    bool peek(const std::initializer_list<LexType>& acceptable);

    FunctionDefinition* parseFunctionDefinition();

    StatementBlock* parseBlock();

    Statement* parseStatement();

    Assignable* parseAssignable();

    Assignment* parseAssignment();

    Condition* parseCondition();

    Expression* parseExpression();

    ForStatement* parseForStatement();

    FunctionCall* parseFunCall(const std::string& id);

    Statement* parseAssignmentOrFunctionCall();

    IfStatement* parseIfStatement();

    ReturnStatement* parseReturnStatement();

    Variable* parseVariable(const std::string& name);

    LogVar* parseCollection();

    VariableDeclaration* parseVariableDeclaration();

    WhileStatement* parseWhileStatement();
};


#endif //TKOM_INTERPRETER_PARSER_H
