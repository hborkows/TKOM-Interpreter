//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_RETURNSTATEMENT_H
#define TKOM_INTERPRETER_RETURNSTATEMENT_H

#include "ASTNode.h"
#include "Assignable.h"

class ReturnStatement: public ASTNode
{
public:
    void setAssignableNode(Assignable* assignable) {assignableNode = assignable;}

    ~ReturnStatement() {delete assignableNode;}

    Type getType() const override {return ASTNode::Type::return_statement;}
protected:
    Assignable* assignableNode;
};


#endif //TKOM_INTERPRETER_RETURNSTATEMENT_H
