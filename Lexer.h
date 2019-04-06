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
    plus_op, minus_op, mul_op, div_op, assign_op,
    and_op, or_op, not_op, gt_op, lt_op, ge_op, le_op, equal_op,
    lbracket, rbracket, lcurlbracket, rcurlbracket, comment_start,
    for_kw, while_kw,
    if_kw, else_kw, elif_kw,
    int_const, text_const,
    var_name, function_name,
    return_kw,
    semicolon, comma, end_of_code
};

struct Token
{
    LexType type;
    TextPosition position;
    std::string text;
    int value;
    bool error;

    Token();
};

class Lexer
{
public:
    Lexer(Source* source);

    Token nextToken();

private:
    Source* source;
};


#endif //TKOM_INTERPRETER_LEXER_H
