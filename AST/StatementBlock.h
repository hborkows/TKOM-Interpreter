//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_STATEMENTBLOCK_H
#define TKOM_INTERPRETER_STATEMENTBLOCK_H

#include <vector>
#include "ASTNode.h"

class StatementBlock: public ASTNode
{
public:
    void addStatement(ASTNode* statement) {statements.push_back(statement);}

    void setLevel(size_t level) {this->level = level;}

    Type getType() const override {return ASTNode::Type::block;}

protected:
    std::vector<ASTNode*> statements;
    size_t level;
};


#endif //TKOM_INTERPRETER_STATEMENTBLOCK_H
