//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_VARIABLE_H
#define TKOM_INTERPRETER_VARIABLE_H


#include <string>
#include "Assignable.h"
#include "Lvalue.h"

class Variable: public Lvalue
{
public:
    Type getType() const override {return Type::variable;}

    void setName(std::string name) {this->name = name;}

protected:
    std::string name;
};


#endif //TKOM_INTERPRETER_VARIABLE_H
