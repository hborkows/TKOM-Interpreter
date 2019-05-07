//
// Created by hborkows on 05.05.19.
//

#include "Parser.h"

Parser::Parser(Lexer *lexer): bufferedToken()
{
    this->lexer = lexer;
}

Parser::~Parser()
{
    delete lexer;
}

ASTNode *Parser::parse()
{
    auto* program = new StatementBlock();
	getNextToken();

}

void Parser::getNextToken()
{
    bufferedToken = lexer->nextToken();
}

void Parser::accept(const std::initializer_list<LexType> &acceptable)
{
    for(auto it: acceptable)
    {
        if(it == bufferedToken.type)
		{
			getNextToken();
			return;
		}
    }

	//Throw error
}

StatementBlock *Parser::parseBlock()
{
    //TODO
}

Assignable *Parser::parseAssignable()
{
    //TODO
}

Assignment *Parser::parseAssignment()
{
    //TODO
}

Condition *Parser::parseCondition()
{
    //TODO
}

Expression *Parser::parseExpression()
{
    //TODO
}

ForStatement *Parser::parseForStatement()
{
    ForStatement* node = new ForStatement();

	accept({LexType::for_kw});

	node->setVariable(parseVariable());

	accept({LexType::in_kw});

	//TODO
}

FunctionCall *Parser::parseFunCall()
{
    //TODO
}

IfStatement *Parser::parseIfStatement()
{
    //TODO
}

ReturnStatement *Parser::parseReturnStatement()
{
    ReturnStatement* node = new ReturnStatement();

	accept({LexType::return_kw});

    node->setAssignableNode(parseAssignable());

	accept({LexType::semicolon});

	return node;
}

Variable *Parser::parseVariable()
{
    //TODO
}

VariableDeclaration *Parser::parseVariableDeclaration()
{
	VariableDeclaration* node = new VariableDeclaration();

	accept({LexType::int_kw, LexType::string_kw, LexType::log_kw});

	//TODO
}

WhileStatement *Parser::parseWhileStatement()
{
    WhileStatement* node = new WhileStatement();

	accept({LexType::while_kw});

	accept({LexType::rbracket});

	node->setCondition(parseCondition());

	accept({LexType::lbracket});

	accept({LexType::rcurlbracket});

	node->setBlock(parseBlock());

	accept({LexType::lcurlbracket});

	return node;
}
