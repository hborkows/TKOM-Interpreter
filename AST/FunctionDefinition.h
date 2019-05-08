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

    Type getType()const override {return Type::function_definition;}
protected:
    std::string name;
    std::vector<std::string> parameters;
    Statement* statement;
};


#endif //TKOM_INTERPRETER_FUNCTIONDEFINITION_H
