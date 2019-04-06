//
// Created by hborkows on 06.04.19.
//

#ifndef TKOM_INTERPRETER_LEXER_H
#define TKOM_INTERPRETER_LEXER_H

#include <vector>
#include <string>
#include "Source.h"

enum LexType
{

};

class Lexeme
{
public:

private:
    LexType type;
    std::string text;
    int value;


};

class Lexer
{
public:
    Lexer(Source* source);

private:
    Source* source;
    std::vector<LexType> lexemes;
};


#endif //TKOM_INTERPRETER_LEXER_H
