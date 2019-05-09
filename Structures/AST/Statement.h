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
protected:

};


#endif //TKOM_INTERPRETER_STATEMENT_H
