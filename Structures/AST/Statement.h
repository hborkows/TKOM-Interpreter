//
// Created by hborkows on 08.05.19.
//

#ifndef TKOM_INTERPRETER_STATEMENT_H
#define TKOM_INTERPRETER_STATEMENT_H


#include "ASTNode.h"

class Statement: public ASTNode
{
public:
    Type getType() const override {return Type::statement;}

    void print(size_t level)const override = 0;
protected:

};


#endif //TKOM_INTERPRETER_STATEMENT_H
