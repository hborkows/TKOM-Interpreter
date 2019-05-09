//
// Created by hborkows on 06.04.19.
//

#include "Lexer.h"

Token::Token() : value(), text(), type(), position()
{
    isError = false;
}

bool Token::initToken(LexType type, TextPosition position, std::string text, int value)
{
    this->type = type;
    this->position = position;
    this->text = std::move(text);
    this->value = value;

    return false;
}

Keyword::Keyword(const std::string &name, LexType type) : name(name), type(type)
{

}

Lexer::Lexer(Source *source) : source(source)
{
    keywords = {
            Keyword("int", int_kw), Keyword("log", log_kw), Keyword("string", string_kw),
            Keyword("for", for_kw), Keyword("while", while_kw), Keyword("in", in_kw),
            Keyword("and", and_op), Keyword("or", or_op),
            Keyword("if", if_kw), Keyword("else", else_kw), Keyword("elif", elif_kw),
            Keyword("return", return_kw), Keyword("void", void_kw),
            Keyword("#def", start_define), Keyword("#end_def", end_define)
    };
}

Lexer::~Lexer()
{
    delete source;
}

Token Lexer::nextToken()
{
    Token result;

    skipWhitespace();

    //check if comment or division operator when given '\'
    checkIfCommentOrDivision(result);

    //check if keyword or a variable name or a function name
    checkIfKeywordOrID(result);

    //check if numerical value
    checkIfNumber(result);

    //check if text constant
    checkIfString(result);
    
    checkIfTwoCharOperator(result);

    checkIfOneCharOperator(result);

    return result;
}

bool Lexer::isWhitespace(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

bool Lexer::isAlpha(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_';
}

bool Lexer::isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool Lexer::isAlphaNum(char c)
{
    return isAlpha(c) || isDigit(c);
}

int Lexer::isKeyword(std::string str)
{
    int position = 0;
    for (const auto &i: keywords)
    {
        if (str == i.name)
            return position;

        position++;
    }
    return -1;
}

void Lexer::skipLine()
{
    while (source->peek() != '\n')
    {
        source->take();
    }
}

void Lexer::skipWhitespace()
{
    while (isWhitespace(source->peek()))
    {
        source->take();
    }
}

void Lexer::checkIfCommentOrDivision(Token& token)
{
    TextPosition tokenStart = source->getPosition();
    if (source->peek() == '\\')
    {
        source->take();
        if (source->peek() == '\\')
        {
            skipLine();
        }
        else
        {
            token.initToken(div_op, tokenStart);
        }
        source->take();
    }
}

void Lexer::checkIfKeywordOrID(Token& token)
{
    char c = source->peek();
    std::string buffer = std::string();
    TextPosition tokenStart = source->getPosition();

    if (isAlpha(c))
    {
        buffer += c;
        source->take();
        c = source->peek();

        while (isAlphaNum(c))
        {
            buffer += c;
            source->take();
            c = source->peek();
        }

        int index = isKeyword(buffer);

        if (index != -1) //buffer contains a keyword identified by index
        {
            token.initToken(keywords[index].type, tokenStart);
        }
        else //buffer contains variable or function id
        {
            token.initToken(id, tokenStart, buffer);
        }
    }
}

void Lexer::checkIfNumber(Token& token)
{
    char c = source->peek();
    std::string buffer = std::string();
    TextPosition tokenStart = source->getPosition();

    if (isDigit(c))
    {
        buffer += c;
        source->take();
        c = source->peek();

        while (isDigit(c))
        {
            buffer += c;
            source->take();
            c = source->peek();
        }

        token.initToken(int_const, tokenStart, std::string(), std::stoi(buffer));
    }
}

void Lexer::checkIfString(Token& token)
{
    char c = source->peek();
    std::string buffer = std::string();
    TextPosition tokenStart = source->getPosition();

    if(c == '\"')
    {
        source->take();
        c = source->peek();
        while (c != '\"')
        {
            buffer += c;
            source->take();
            c = source->peek();
        }
        token.initToken(text_const, tokenStart, buffer);
    }
}

void Lexer::checkIfTwoCharOperator(Token &token)
{
    char c = source->peek();
    std::string buffer = std::string();
    TextPosition tokenStart = source->getPosition();
    
    switch(c)
    {
        case '>':
            source->take();
            c = source->peek();
            if (c == '=')
            {
                token.initToken(ge_op, tokenStart);
                source->take();
            }
            else
                token.initToken(gt_op, tokenStart);
            break;
        case '<':
            source->take();
            c = source->peek();
            if (c == '=')
            {
                token.initToken(le_op, tokenStart);
                source->take();
            }
            else
                token.initToken(lt_op, tokenStart);
            break;
        case '=':
            source->take();
            c = source->peek();
            if (c == '=')
            {
                token.initToken(equal_op, tokenStart);
                source->take();
            }
            else
                token.initToken(assign_op, tokenStart);
            break;
        case '!':
            source->take();
            c = source->peek();
            if(c == '=')
            {
                token.initToken(not_equal_op, tokenStart);
                source->take();
            }
            else
                token.initToken(not_op, tokenStart);
        default:
            break;
    }
}

void Lexer::checkIfOneCharOperator(Token &token)
{
    char c = source->peek();
    std::string buffer = std::string();
    TextPosition tokenStart = source->getPosition();
    
    switch(c)
    {
        case '+':
            token.initToken(plus_op, tokenStart);
            source->take();
            break;
        case '-':
            token.initToken(minus_op, tokenStart);
            source->take();
            break;
        case '*':
            token.initToken(mul_op, tokenStart);
            source->take();
            break;
        case '(':
            token.initToken(lbracket, tokenStart);
            source->take();
            break;
        case ')':
            token.initToken(rbracket, tokenStart);
            source->take();
            break;
        case '{':
            token.initToken(lcurlbracket, tokenStart);
            source->take();
            break;
        case '}':
            token.initToken(rcurlbracket, tokenStart);
            source->take();
            break;
        case ';':
            token.initToken(semicolon, tokenStart);
            source->take();
            break;
        case ',':
            token.initToken(comma, tokenStart);
            source->take();
            break;
        case '$':
            token.initToken(end_of_code, tokenStart);
            source->take();
            break;
        default: //not a part of the language => not a valid token, error
            token.initToken(unknown, tokenStart);
            token.isError = true;
            break;
    }
}
