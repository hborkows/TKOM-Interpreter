//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_CONDITION_H
#define TKOM_INTERPRETER_CONDITION_H


#include "Assignable.h"
#include "../../Modules/Lexer.h"

class Condition: public Assignable
{
public:
    Condition() = default;

    void setNegated(bool flag) {negated = flag;}

    void setOperation(const LexType& operation) {this->operation = operation;}

    void addOperand(ASTNode* operand) {operands.push_back(operand);}

    Type getType() const override {return ASTNode::Type::condition;}

    void print(size_t level)const override
    {
        ParseTreePrinter::printIndent(level);

        std::cout << "Condition" << std::endl;

        ParseTreePrinter::printIndent(level);

        std::cout << "Operator: " << lexNames[operation] << std::endl;

        level++;

        for(auto operand: operands)
        {
            operand->print(level);
        }
    }

protected:
    bool negated;
    LexType operation;
    std::vector<ASTNode*> operands;
};


#endif //TKOM_INTERPRETER_CONDITION_H
