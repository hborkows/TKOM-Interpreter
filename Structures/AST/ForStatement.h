//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_FORSTATEMENT_H
#define TKOM_INTERPRETER_FORSTATEMENT_H


#include "ASTNode.h"
#include "Condition.h"
#include "StatementBlock.h"
#include "Variable.h"
#include "LogVar.h"
#include "VariableDeclaration.h"

class ForStatement: public Statement
{
public:
    ForStatement() = default;

    ~ForStatement() {delete statement;  delete variable;}

    void setBlock(Statement* statement) {this->statement = statement;}

    void setVariable(VariableDeclaration* var) {variable = var;}

    void setCollection(LogVar* collection) {this->collection = collection;}

    Type getType() const override {return ASTNode::Type::for_statement;}

    void print(size_t level)const override
    {
        ParseTreePrinter::printIndent(level);

        std::cout << "For loop" << std::endl;

        variable->print(level + 1);

        collection->print(level + 1);

        statement->print(level + 1);
    }

protected:
    Statement* statement;
  	LogVar* collection;
    VariableDeclaration* variable;
};


#endif //TKOM_INTERPRETER_FORSTATEMENT_H
