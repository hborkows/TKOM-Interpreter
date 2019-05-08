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
    lbracket, rbracket, lcurlbracket, rcurlbracket,
    for_kw, while_kw, in_kw,
    if_kw, else_kw, elif_kw,
    int_const, text_const,
    id,
    int_kw, log_kw, string_kw,
    return_kw,
    semicolon, comma, end_of_code,
    unknown
};


struct Token
{
    LexType type;
    TextPosition position;
    std::string text;
    int value;
    bool isError;

    Token();

    bool initToken(LexType type, TextPosition position, std::string text = std::string(), int value = 0);
};

struct Keyword
{
    std::string name;
    LexType type;

    Keyword(const std::string &name, LexType type);
};

class Lexer
{
public:
    explicit Lexer(Source *source);

    ~Lexer();

    Token nextToken();

private:
    Source *source;
    std::vector<Keyword> keywords;

    bool static isWhitespace(char c);

    bool static isAlpha(char c);

    bool static isDigit(char c);

    bool static isAlphaNum(char c);

    int isKeyword(std::string str);

    void skipLine();

    void skipWhitespace();

    void checkIfCommentOrDivision(Token& token);

    void checkIfKeywordOrID(Token& token);

    void checkIfNumber(Token& token);

    void checkIfString(Token& token);

    void checkIfTwoCharOperator(Token& token);

    void checkIfOneCharOperator(Token& token);
};


#endif //TKOM_INTERPRETER_LEXER_H
