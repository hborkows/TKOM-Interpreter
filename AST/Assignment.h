//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_ASSIGNMENT_H
#define TKOM_INTERPRETER_ASSIGNMENT_H

#include "Assignable.h"
#include "Variable.h"

class Assignment: public Assignable
{
public:
    Assignment() = default;

    ~Assignment() override {delete value; delete variable;};

    void setAssignable(Assignable* value) {this->value = value;}

    void setVariable(Variable* variable) {this->variable = variable;}

    Type getType() const override {return ASTNode::Type::assignment;}

protected:
    Assignable* value;
    Variable* variable;
};


#endif //TKOM_INTERPRETER_ASSIGNMENT_H