//
// Created by hborkows on 08.05.19.
//

#ifndef TKOM_INTERPRETER_FUNCTIONDEFINITION_H
#define TKOM_INTERPRETER_FUNCTIONDEFINITION_H

#include <string>
#include <vector>
#include "ASTNode.h"
#include "Statement.h"

class FunctionDefinition: public ASTNode
{
public:
    FunctionDefinition(): parameters()
    {

    }

    ~FunctionDefinition() {delete statement;}

    void setName(const std::string& name) {this->name = name;}

    void addParameter(const std::string& param) {parameters.push_back(param);}

    void setStatement(Statement* statement) {this->statement = statement;}

    void setReturntype(const LexType& type)
    {
        if(type == LexType::string_kw)
        {
            returnType = Type::string_var;
        }
        else if(type == LexType::int_kw)
        {
            returnType = Type::int_var;
        }
        else if(type == LexType::void_kw)
        {
            returnType = Type::void_var;
        }
    }

    Type getType()const override {return Type::function_definition;}

    void print(size_t level)const override
    {
        ParseTreePrinter::printIndent(level);

        std::cout << "Function definition: " << name << std::endl;

        ParseTreePrinter::printIndent(level);

        std::cout << "Parameters:" ;

        for(auto param: parameters)
        {
            std::cout << param << std::endl;
        }

        statement->print(level + 1);
    }
protected:
    std::string name;
    std::vector<std::string> parameters;
    Statement* statement;
    Type returnType;
};


#endif //TKOM_INTERPRETER_FUNCTIONDEFINITION_H
