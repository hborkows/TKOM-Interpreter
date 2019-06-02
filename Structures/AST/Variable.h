//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_VARIABLE_H
#define TKOM_INTERPRETER_VARIABLE_H


#include <string>
#include "Assignable.h"
#include "Statement.h"

class Variable: public Statement
{
public:
    Type getType() const override {return Type::variable;}

    void setName(std::string name) {this->name = name;}

    void print(size_t level)const override
    {
        ParseTreePrinter::printIndent(level);

        std::cout << "VariableIr: " << name << std::endl;
    }

protected:
    std::string name;
};


#endif //TKOM_INTERPRETER_VARIABLE_H
