//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_EXPRESSION_H
#define TKOM_INTERPRETER_EXPRESSION_H

#include <vector>
#include "Assignable.h"
#include "../../Modules/Lexer.h"

class Expression: public Assignable
{
public:
    Expression()
    {
        operands = std::vector<ASTNode*>();
        operators = std::vector<LexType>();
    }

    void addOperator(const LexType& op) {operators.push_back(op);}

    void addOperand(ASTNode* operand) {operands.push_back(operand);}

    Type getType() const override {return ASTNode::Type::expression;}
protected:
    std::vector<ASTNode*> operands;
    std::vector<LexType> operators;
};


#endif //TKOM_INTERPRETER_EXPRESSION_H
