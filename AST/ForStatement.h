//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_FORSTATEMENT_H
#define TKOM_INTERPRETER_FORSTATEMENT_H


#include "ASTNode.h"
#include "Condition.h"
#include "StatementBlock.h"
#include "Variable.h"
#include "LogVar.h"
#include "VariableDeclaration.h"

class ForStatement: public Statement
{
public:
    ForStatement() = default;

    ~ForStatement() {delete statement;  delete variable;}

    void setBlock(Statement* statement) {this->statement = statement;}

    void setVariable(VariableDeclaration* var) {variable = var;}

    void setCollection(LogVar* collection) {this->collection = collection;}

    Type getType() const override {return ASTNode::Type::for_statement;}

protected:
    Statement* statement;
  	LogVar* collection;
    VariableDeclaration* variable;
};


#endif //TKOM_INTERPRETER_FORSTATEMENT_H
