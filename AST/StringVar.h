//
// Created by hborkows on 08.05.19.
//

#ifndef TKOM_INTERPRETER_STRINGVAR_H
#define TKOM_INTERPRETER_STRINGVAR_H


#include "Variable.h"

class StringVar: public Variable
{
public:
    void setValue(std::string value) {this->value = value;}
protected:
    std::string value;
};


#endif //TKOM_INTERPRETER_STRINGVAR_H
