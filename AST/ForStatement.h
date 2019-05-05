//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_FORSTATEMENT_H
#define TKOM_INTERPRETER_FORSTATEMENT_H


#include "ASTNode.h"
#include "Condition.h"
#include "StatementBlock.h"

class ForStatement: public ASTNode
{
public:
    ForStatement() = default;

    ~ForStatement() {delete block; delete condition;}

    void setBlock(StatementBlock* block) {this->block = block;}

    void setCondition(Condition* cond) {condition = cond;}

    Type getType() const override {return ASTNode::Type::for_statement;}
protected:
    StatementBlock* block;
    Condition* condition;
};


#endif //TKOM_INTERPRETER_FORSTATEMENT_H
