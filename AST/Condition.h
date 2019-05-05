//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_CONDITION_H
#define TKOM_INTERPRETER_CONDITION_H

#include <vector>
#include "Assignable.h"
#include "../Lexer.h"

class Condition: public Assignable
{
public:
    Condition()
    {
        operands = std::vector<ASTNode*>();
        operators = std::vector<LexType>();
    }

    void addOperator(const LexType& op) {operators.push_back(op);}

    void addOperand(ASTNode* operand) {operands.push_back(operand);}

    Type getType() const override {return ASTNode::Type::condition;}
protected:
    std::vector<ASTNode*> operands;
    std::vector<LexType> operators;
};


#endif //TKOM_INTERPRETER_CONDITION_H
