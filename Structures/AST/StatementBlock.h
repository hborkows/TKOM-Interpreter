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

    Type getType() const override {return ASTNode::Type::block;}

    void print(size_t level)const override
    {
        ParseTreePrinter::printIndent(level);

        std::cout << "Statement block: " << std::endl;

        for(auto statement: statements)
        {
            statement->print(level + 1);
        }
    }

protected:
    std::vector<Statement*> statements;
};


#endif //TKOM_INTERPRETER_STATEMENTBLOCK_H
