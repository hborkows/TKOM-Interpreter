//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_VARIABLE_H
#define TKOM_INTERPRETER_VARIABLE_H


#include "Rvalue.h"
#include "Lvalue.h"

class Variable: public Rvalue, public Lvalue
{

};


#endif //TKOM_INTERPRETER_VARIABLE_H
