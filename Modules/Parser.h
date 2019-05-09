//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_PARSER_H
#define TKOM_INTERPRETER_PARSER_H

#include <vector>
#include "Lexer.h"
#include "../Structures/AST/ASTNode.h"
#include "../Structures/AST/Assignable.h"
#include "../Structures/AST/Assignment.h"
#include "../Structures/AST/Condition.h"
#include "../Structures/AST/Expression.h"
#include "../Structures/AST/ForStatement.h"
#include "../Structures/AST/FunctionCall.h"
#include "../Structures/AST/IfStatement.h"
#include "../Structures/AST/ReturnStatement.h"
#include "../Structures/AST/VariableDeclaration.h"
#include "../Structures/AST/WhileStatement.h"
#include "Tracer.h"
#include "../Structures/AST/FunctionDefinition.h"
#include "../Structures/AST/Literal.h"
#include "../Structures/AST/Program.h"

class Parser
{
public:
    explicit Parser(Lexer* lexer);

    ~Parser();

    Program* parse();

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

    Condition* parseCondition();

    Condition* parseAndCondition();

    Condition* parseEqualCondition();

    Condition* parseRelationCondition();

    ASTNode* parsePrimaryCondition();

    Expression* parseExpression();

    Expression* parseMultiplicativeExpression();

    ASTNode* parsePrimaryExpression();

    Literal* parseLiteral();

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
