//
// Created by hborkows on 08.05.19.
//

#ifndef TKOM_INTERPRETER_INTVAR_H
#define TKOM_INTERPRETER_INTVAR_H


#include "Variable.h"

class IntVar: public Variable
{
public:
    void setValue(int value) {this->value = value;}

protected:
    int value;
};


#endif //TKOM_INTERPRETER_INTVAR_H
