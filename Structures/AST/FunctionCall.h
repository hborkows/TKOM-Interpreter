//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_FUNCTIONCALL_H
#define TKOM_INTERPRETER_FUNCTIONCALL_H


#include <string>
#include <vector>
#include "Assignable.h"

class FunctionCall: public Assignable, public Statement
{
public:
    FunctionCall() {arguments = std::vector<Assignable*>();};

    void setName(std::string name) {this->name = name;}

    void addArgument(Assignable* arg) {arguments.push_back(arg);}

    Type getType() const override {return ASTNode::Type::function_call;}

    void print(size_t level)const override
    {
        ParseTreePrinter::printIndent(level);

        std::cout << "Function call: " << name << std::endl;

        ParseTreePrinter::printIndent(level);

        std::cout << "Arguments:" << std::endl;

        for(auto arg: arguments)
        {
            arg->print(level + 1);
        }
    }
protected:
    std::string name;
    std::vector<Assignable*> arguments;
};


#endif //TKOM_INTERPRETER_FUNCTIONCALL_H
