//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_FORSTATEMENT_H
#define TKOM_INTERPRETER_FORSTATEMENT_H


#include "ASTNode.h"
#include "Condition.h"
#include "StatementBlock.h"
#include "Variable.h"

class ForStatement: public Statement
{
public:
    ForStatement() = default;

    ~ForStatement() {delete statement;  delete variable;}

    void setBlock(Statement* statement) {this->statement = statement;}

    void setVariable(Variable* var) {variable = var;}

    Type getType() const override {return ASTNode::Type::for_statement;}

protected:
    Statement* statement;
  	//TODO collection type
    Variable* variable;
};


#endif //TKOM_INTERPRETER_FORSTATEMENT_H
