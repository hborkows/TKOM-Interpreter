//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_WHILESTATEMENT_H
#define TKOM_INTERPRETER_WHILESTATEMENT_H


#include "ASTNode.h"
#include "StatementBlock.h"
#include "Condition.h"

class WhileStatement: public Statement
{
public:
    WhileStatement() = default;

    ~WhileStatement() {delete block; delete condition;}

    void setBlock(Statement* block) {this->block = block;}

    void setCondition(Condition* cond) {condition = cond;}

    Type getType() const override {return ASTNode::Type::while_statement;}

protected:
    Statement* block;
    Condition* condition;
};


#endif //TKOM_INTERPRETER_WHILESTATEMENT_H
