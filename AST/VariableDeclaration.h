//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_VARIABLEDECLARATION_H
#define TKOM_INTERPRETER_VARIABLEDECLARATION_H

#include <string>
#include "Lvalue.h"
#include "Assignable.h"

class VariableDeclaration: public Lvalue
{
public:
    ~VariableDeclaration() {delete value;}

    void setName(std::string name) {this->name = name;}

    void setValue(Assignable* value) {this->value = value;}

    Type getType() const override {return ASTNode::Type::var_declaration;}
protected:
    Assignable* value;
    std::string name;
};


#endif //TKOM_INTERPRETER_VARIABLEDECLARATION_H
