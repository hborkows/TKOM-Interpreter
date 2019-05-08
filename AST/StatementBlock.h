//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_STATEMENTBLOCK_H
#define TKOM_INTERPRETER_STATEMENTBLOCK_H

#include <vector>
#include "ASTNode.h"
#include "Statement.h"

class StatementBlock: public Statement
{
public:
    void addStatement(Statement* statement) {statements.push_back(statement);}

    void setLevel(size_t level) {this->level = level;}

    Type getType() const override {return ASTNode::Type::block;}

protected:
    std::vector<Statement*> statements;
    size_t level;
};


#endif //TKOM_INTERPRETER_STATEMENTBLOCK_H
