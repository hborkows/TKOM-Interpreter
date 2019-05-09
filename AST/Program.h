//
// Created by hborkows on 09.05.19.
//

#ifndef TKOM_INTERPRETER_PROGRAM_H
#define TKOM_INTERPRETER_PROGRAM_H

#include "ASTNode.h"
#include "FunctionDefinition.h"
#include <vector>

class Program: public ASTNode
{
public:
    Program(): functions(), statements()
    {

    }

    void addFunction(FunctionDefinition* fun) {functions.push_back(fun);}

    void addStatement(Statement* statement) {statements.push_back(statement);}

    Type getType()const override {return Type::program;}

protected:
    std::vector<FunctionDefinition*> functions;
    std::vector<Statement*> statements;
};


#endif //TKOM_INTERPRETER_PROGRAM_H
