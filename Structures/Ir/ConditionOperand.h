//
// Created by hborkows on 02.06.19.
//

#ifndef TKOM_INTERPRETER_CONDITIONOPERAND_H
#define TKOM_INTERPRETER_CONDITIONOPERAND_H


#include "Executable.h"

class ConditionOperand: virtual public Executable
{
public:
    virtual bool isTruth()
    {
        return false;
    }
};


#endif //TKOM_INTERPRETER_CONDITIONOPERAND_H
