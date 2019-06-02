//
// Created by hborkows on 02.06.19.
//

#ifndef TKOM_INTERPRETER_VARIABLE_H
#define TKOM_INTERPRETER_VARIABLE_H

#include <string>
#include "../AST/ASTNode.h"

namespace ir
{
    class Variable
    {
    public:
        explicit Variable(const std::string& name, const ASTNode::Type& type): name(name), type(type)
        {

        }

        virtual const std::string& getName() const
        {
            return name;
        }

        virtual void setName(const std::string& name)
        {
            Variable::name = name;
        }

        virtual ASTNode::Type getType() const
        {
            return type;
        }

        virtual void setType(ASTNode::Type type)
        {
            Variable::type = type;
        }

    private:
        std::string name;
        ASTNode::Type type;
        std::string stringValue;
        int intValue;

    };
}

#endif //TKOM_INTERPRETER_VARIABLE_H
