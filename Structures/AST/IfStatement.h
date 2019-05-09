//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_IFSTATEMENT_H
#define TKOM_INTERPRETER_IFSTATEMENT_H

#include <vector>
#include "ASTNode.h"
#include "StatementBlock.h"
#include "Condition.h"

class IfStatement: public Statement
{
public:
    ~IfStatement() {delete trueStatement; delete falseStatement; delete condition;}

    void setTrueStatement(Statement* statement) {this->trueStatement = statement;}

    void setFalseStatement(Statement* statement) {this->falseStatement = statement;}

    void setCondition(Condition* condition) {this->condition = condition;}

    Type getType() const override {return ASTNode::Type::if_statement;}
protected:
    Statement* trueStatement;
    Statement* falseStatement;
    Condition* condition;
};


#endif //TKOM_INTERPRETER_IFSTATEMENT_H
