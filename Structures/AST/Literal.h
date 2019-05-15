//
// Created by hborkows on 09.05.19.
//

#ifndef TKOM_INTERPRETER_LITERAL_H
#define TKOM_INTERPRETER_LITERAL_H


#include "ASTNode.h"
#include <string>

class Literal: public ASTNode
{
public:
    void setTextValue(const std::string& text) {textValue = text;}

    void setIntValue(const int& value) {intValue = value;}

    void setLiteralType(const LexType& type)
    {
        if(type == LexType::text_const)
        {
            literalType = Type::string_lit;
        }
        else if(type == LexType::int_const)
        {
            literalType = Type::int_lit;
        }
    }

    Type getType()const override {return Type::literal;}

    void print(size_t level)const override
    {
        ParseTreePrinter::printIndent(level);

        std::cout << "Literal: ";

        if(literalType == Type::string_lit)
        {
            std::cout << textValue << std::endl;
        }
        else
        {
            std::cout << intValue << std::endl;
        }
    }
protected:
    std::string textValue;
    int intValue;
    Type literalType;
};


#endif //TKOM_INTERPRETER_LITERAL_H
