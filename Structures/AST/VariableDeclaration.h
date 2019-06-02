//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_VARIABLEDECLARATION_H
#define TKOM_INTERPRETER_VARIABLEDECLARATION_H

#include <string>
#include "Assignable.h"

class VariableDeclaration: public Statement
{
public:
    ~VariableDeclaration() {delete value;}

    void setName(std::string name) {this->name = name;}

    std::string getName() {return name;}

    void setValue(Assignable* value) {this->value = value;}

    void setVarType(const LexType& type)
    {
        if(type == LexType::int_kw)
        {
            varType = Type::int_var;
        }
        else if(type == LexType::string_kw)
        {
            varType = Type::string_var;
        }
        else if(type == LexType::log_kw)
        {
            varType = Type::log_var;
        }
    }

    Type getType() const override {return ASTNode::Type::var_declaration;}

    void print(size_t level)const override
    {
        ParseTreePrinter::printIndent(level);

        std::cout << "VariableIr declaration: ";

        if(varType == Type::log_var)
        {
            std::cout << "log ";
        }
        else if(varType == Type::int_var)
        {
            std::cout << "int ";
        }
        else
        {
            std::cout << "string ";
        }

        std::cout << name << std::endl;

        if(value != nullptr)
        {
            ParseTreePrinter::printIndent(level);

            std::cout << "Value: " << std::endl;

            value->print(level);
        }
    }
protected:
    Assignable* value;
    std::string name;
    Type varType;
};


#endif //TKOM_INTERPRETER_VARIABLEDECLARATION_H
