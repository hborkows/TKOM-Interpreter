//
// Created by hborkows on 05.05.19.
//

#include "Parser.h"

Parser::Parser(Lexer *lexer): bufferedToken(), tracer()
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

bool Parser::accept(const std::initializer_list<LexType> &acceptable)
{
    for(auto it: acceptable)
    {
        if(it == bufferedToken.type)
		{
			getNextToken();
			return true;
		}
    }

	//Throw error
	return false;
}

bool Parser::peek(const std::initializer_list<LexType>& acceptable)
{
    for(auto it: acceptable)
    {
        if(it == bufferedToken.type)
            return true;
    }
    return false;
}

StatementBlock *Parser::parseBlock()
{
    //TODO
}

Statement *Parser::parseStatement()
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

	node->setCollection(parseCollection());

	node->setBlock(parseStatement());
}

FunctionCall *Parser::parseFunCall(const std::string& id)
{
    FunctionCall* node = new FunctionCall();

    node->setName(id);

    accept({LexType::lbracket});

    if(peek({LexType::rbracket}))
    {
        accept({LexType::rbracket});
        return node;
    }

    while(true)
    {
        node->addArgument(parseAssignable());

        if(peek({LexType::rbracket}))
        {
            accept({LexType::rbracket});
            break;
        }
        if(peek({LexType::comma}))
        {
            accept({LexType::comma});
            continue;
        }
    }

    return node;
}

IfStatement *Parser::parseIfStatement()
{
    IfStatement* node = new IfStatement();

    accept({LexType::if_kw});

    accept({LexType::lbracket});

    node->setCondition(parseCondition());

    tracer->enterBlock();

    node->setTrueStatement(parseStatement());

    tracer->exitBlock();

    if(accept({LexType::else_kw}))
    {
        tracer->enterBlock();
        node->setFalseStatement(parseStatement());
        tracer->exitBlock();
    }

    return node;
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

LogVar* Parser::parseCollection()
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

	accept({LexType::lbracket});

	node->setCondition(parseCondition());

	accept({LexType::rbracket});

	node->setStatement(parseStatement());

	return node;
}
