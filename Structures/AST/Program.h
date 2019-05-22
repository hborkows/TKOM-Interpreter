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

    void print(size_t level)const override
    {
        ParseTreePrinter::printIndent(level);

        std::cout << "Program: " << std::endl;

        ParseTreePrinter::printIndent(level);

        std::cout << "Function definitions: " << std::endl;

        for(auto fun: functions)
        {
            fun->print(level + 1);
        }

        ParseTreePrinter::printIndent(level);

        std::cout << "Statements: " << std::endl;

        for(auto statement: statements)
        {
            statement->print(level + 1);
        }
    }

protected:
    std::vector<FunctionDefinition*> functions;
    std::vector<Statement*> statements;
};


#endif //TKOM_INTERPRETER_PROGRAM_H
