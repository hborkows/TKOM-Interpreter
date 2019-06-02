//
// Created by hborkows on 02.06.19.
//

#ifndef TKOM_INTERPRETER_VARIABLEIR_H
#define TKOM_INTERPRETER_VARIABLEIR_H

#include <string>
#include "../AST/ASTNode.h"


class VariableIr
{
public:
    explicit VariableIr(const std::string& name, const ASTNode::Type& type): name(name), type(type)
    {

    }

    virtual const std::string& getName() const
    {
        return name;
    }

    virtual void setName(const std::string& name)
    {
        VariableIr::name = name;
    }

    virtual ASTNode::Type getType() const
    {
        return type;
    }

    virtual void setType(ASTNode::Type type)
    {
        VariableIr::type = type;
    }

private:
    std::string name;
    ASTNode::Type type;
    std::string stringValue;
    int intValue;

};


#endif //TKOM_INTERPRETER_VARIABLEIR_H
