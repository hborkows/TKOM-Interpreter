//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_IFSTATEMENT_H
#define TKOM_INTERPRETER_IFSTATEMENT_H

#include <vector>
#include "ASTNode.h"
#include "StatementBlock.h"
#include "Condition.h"

class IfStatement: public ASTNode
{
public:
    IfStatement()
    {
        blocks = std::vector<StatementBlock*>();
        conditions = std::vector<Condition*>();
    }

    void addBlock(StatementBlock* block) {blocks.push_back(block);}

    void addCondition(Condition* condition) {conditions.push_back(condition);}

    Type getType() const override {return ASTNode::Type::if_statement;}
protected:
    std::vector<StatementBlock*> blocks;
    std::vector<Condition*> conditions;
};


#endif //TKOM_INTERPRETER_IFSTATEMENT_H
