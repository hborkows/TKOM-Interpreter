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
    this->text = text;
    this->value = value;

    return false;
}

Lexer::Lexer(Source* source) : source(source)
{

}

Token Lexer::nextToken()
{
    Token result;
    bool tokenNotBuilt = true;
    char c;

    while(tokenNotBuilt)
    {
        c = source->peek();

        //Skip whitespaces
        while(isWhitespace(c))
        {
            source->take();
            c = source->peek();
        }

        //check if comment or division operator when given '\'
        if(c == '\\')
        {
            source->take();
            c = source->peek();
            if(c == '\\')
            {
                skipLine(c);
            }
            else
            {
                tokenNotBuilt = result.initToken(div_op, source->getPosition());
            }
            source->take();
        }

        switch(c)
        {
            //1-character operators
            //----------------------------------------------------------------------------------------------------------
            case '+':
                tokenNotBuilt = result.initToken(plus_op, source->getPosition());
                source->take();
                break;
            case '-':
                tokenNotBuilt = result.initToken(minus_op, source->getPosition());
                source->take();
                break;
            case '*':
                tokenNotBuilt = result.initToken(mul_op, source->getPosition());
                source->take();
                break;
            case '>':
                tokenNotBuilt = result.initToken(gt_op, source->getPosition());
                source->take();
                break;
            case '<':
                tokenNotBuilt = result.initToken(lt_op, source->getPosition());
                source->take();
                break;
            case '(':
                tokenNotBuilt = result.initToken(lbracket, source->getPosition());
                source->take();
                break;
            case ')':
                tokenNotBuilt = result.initToken(rbracket, source->getPosition());
                source->take();
                break;
            case '{':
                tokenNotBuilt = result.initToken(lcurlbracket, source->getPosition());
                source->take();
                break;
            case '}':
                tokenNotBuilt = result.initToken(rcurlbracket, source->getPosition());
                source->take();
                break;
            case '!':
                tokenNotBuilt = result.initToken(not_op, source->getPosition());
                source->take();
                break;
            case '=':
                tokenNotBuilt = result.initToken(assign_op, source->getPosition());
                source->take();
                break;
            case ';':
                tokenNotBuilt = result.initToken(semicolon, source->getPosition());
                source->take();
                break;
            case ',':
                tokenNotBuilt = result.initToken(comma, source->getPosition());
                source->take();
                break;
            case '$':
                tokenNotBuilt = result.initToken(end_of_code, source->getPosition());
                source->take();
                break;
                //------------------------------------------------------------------------------------------------------
                //
            default:
                break;
        }
    }

    return result;
}

bool Lexer::isWhitespace(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

void Lexer::skipLine(char &c)
{
    while(c != '\n')
    {
        source->take();
        c = source->peek();
    }
}

