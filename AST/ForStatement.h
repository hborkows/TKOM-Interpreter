//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_FORSTATEMENT_H
#define TKOM_INTERPRETER_FORSTATEMENT_H


#include "ASTNode.h"
#include "Condition.h"
#include "StatementBlock.h"
#include "Variable.h"

class ForStatement: public ASTNode
{
public:
    ForStatement() = default;

    ~ForStatement() {delete block;  delete variable;}

    void setBlock(StatementBlock* block) {this->block = block;}

    void setVariable(Variable* var) {variable = var;}

    Type getType() const override {return ASTNode::Type::for_statement;}

protected:
    StatementBlock* block;
  	//TODO collection type
    Variable* variable;
};


#endif //TKOM_INTERPRETER_FORSTATEMENT_H
