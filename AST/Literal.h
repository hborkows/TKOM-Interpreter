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

    Type getType()const override {return Type::literal;}
protected:
    std::string textValue;
    int intValue;
};


#endif //TKOM_INTERPRETER_LITERAL_H
