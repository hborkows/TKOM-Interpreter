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

Keyword::Keyword(const std::string& name, LexType type) : name(name), type(type)
{

}

Lexer::Lexer(Source* source) : source(source)
{
    keywords = {
            Keyword("int", int_kw), Keyword("log", log_kw), Keyword("string", string_kw),
            Keyword("for", for_kw), Keyword("while", while_kw), Keyword("in", in_kw),
            Keyword("and", and_op), Keyword("or", or_op),
            Keyword("if", if_kw), Keyword("else", else_kw), Keyword("elif", elif_kw),
            Keyword("return", return_kw)
    };
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

        //check if keyword or a variable name or a function name
        else if(isAlpha(c))
        {
            std::string buffer(1,c);
            source->take();
            c = source->peek();

            while(isAphaNum(c))
            {
                buffer += c;
                source->take();
                c = source->peek();
            }

            int index = isKeyword(buffer);

            if(index != -1) //buffer contains a keyword identified by index
            {
                tokenNotBuilt = result.initToken(keywords[index].type, source->getPosition());
            }
            else //buffer contains variable or function id
            {
                tokenNotBuilt = result.initToken(id, source->getPosition(), buffer);
            }
        }

        //check if numerical value
        else if(isDigit(c))
        {
            std::string buffer(1,c);
            source->take();
            c = source->peek();

            while(isDigit(c))
            {
                buffer += c;
                source->take();
                c = source->peek();
            }

            tokenNotBuilt = result.initToken(int_const, source->getPosition(), std::string(), std::stoi(buffer));
        }
        else
        {
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
    }

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

bool Lexer::isAphaNum(char c)
{
    return isAlpha(c) || isDigit(c);
}

int Lexer::isKeyword(std::string str)
{
    int position = 0;
    for(const auto& i: keywords)
    {
        if(str == i.name)
            return position;

        position++;
    }
    return -1;
}

void Lexer::skipLine(char &c)
{
    while(c != '\n')
    {
        source->take();
        c = source->peek();
    }
}

