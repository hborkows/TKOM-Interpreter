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
protected:
    Assignable* value;
    std::string name;
    Type varType;
};


#endif //TKOM_INTERPRETER_VARIABLEDECLARATION_H
