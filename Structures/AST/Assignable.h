//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_ASSIGNABLE_H
#define TKOM_INTERPRETER_ASSIGNABLE_H


#include "ASTNode.h"

class Assignable : public ASTNode
{
public:
    Assignable() = default;

    virtual ~Assignable() = default;
};


#endif //TKOM_INTERPRETER_ASSIGNABLE_H
