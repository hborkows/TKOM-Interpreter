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

    ~WhileStatement() {delete statement; delete condition;}

    void setStatement(Statement* statement) {this->statement = statement;}

    void setCondition(Condition* cond) {condition = cond;}

    Condition* getCondition() {return condition;}

    Statement* getStatement() {return statement;}

    Type getType() const override {return ASTNode::Type::while_statement;}

    void print(size_t level)const override
    {
        ParseTreePrinter::printIndent(level);

        std::cout << "While loop: " << std::endl;

        condition->print(level + 1);

        statement->print(level + 1);
    }

protected:
    Statement* statement;
    Condition* condition;
};


#endif //TKOM_INTERPRETER_WHILESTATEMENT_H
