//
// Created by hborkows on 06.04.19.
//

#include "Lexer.h"

Token::Token() : value(), text(), type(), position()
{
    error = false;
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
        result.position = source->getPosition();

        switch(c)
        {
            //1-character operators
            case '+':
                result.type = plus_op;
                source->take();
                tokenNotBuilt = false;
                break;
            case '-':
                result.type = minus_op;
                source->take();
                tokenNotBuilt = false;
                break;
            case '*':
                result.type = mul_op;
                source->take();
                tokenNotBuilt = false;
                break;
            case '/':
                result.type = div_op;
                source->take();
                tokenNotBuilt = false;
                break;
            case '>':
                result.type = gt_op;
                source->take();
                tokenNotBuilt = false;
                break;
            case '<':
                result.type = lt_op;
                source->take();
                tokenNotBuilt = false;
                break;
            case '(':
                result.type = lbracket;
                source->take();
                tokenNotBuilt = false;
                break;
            case ')':
                result.type = rbracket;
                source->take();
                tokenNotBuilt = false;
                break;
            case '{':
                result.type = lcurlbracket;
                source->take();
                tokenNotBuilt = false;
                break;
            case '}':
                result.type = rcurlbracket;
                source->take();
                tokenNotBuilt = false;
                break;
            case '!':
                result.type = not_op;
                source->take();
                tokenNotBuilt = false;
                break;
            case '=':
                result.type = assign_op;
                source->take();
                tokenNotBuilt = false;
                break;
            case ';':
                result.type = semicolon;
                source->take();
                tokenNotBuilt = false;
                break;
            case ',':
                result.type = comma;
                source->take();
                tokenNotBuilt = false;
                break;
            case '$':
                result.type = end_of_code;
                source->take();
                tokenNotBuilt = false;
                break;
            default:
                break;
        }
    }

    return result;
}

