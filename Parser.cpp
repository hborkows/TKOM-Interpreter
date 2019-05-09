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
    auto* program = new Statement();
	getNextToken();

}

void Parser::getNextToken()
{
    bufferedToken = lexer->nextToken();
}

bool Parser::accept(const std::initializer_list<LexType>& acceptable)
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

FunctionDefinition* Parser::parseFunctionDefinition()
{
    FunctionDefinition* node = new FunctionDefinition();

    if(peek({LexType::id}))
    {
        node->setName(bufferedToken.text);
        accept({LexType::id});
    }
    else
    {
        return nullptr;
    }

    accept({LexType::lbracket});

    if(peek({LexType::rbracket}))
    {
        accept({LexType::rbracket});

        node->setStatement(parseStatement());

        return node;
    }

    while(true)
    {
        if (peek({LexType::id}))
        {
            node->addParameter(bufferedToken.text);
            accept({LexType::id});
        }
        else if (peek({LexType::comma}))
        {
            accept({LexType::comma});
            continue;
        }
        else if (peek({LexType::rbracket}))
        {
            break;
        }
    }

    node->setStatement(parseStatement());

    return node;
}

StatementBlock *Parser::parseBlock()
{
    StatementBlock* node = new StatementBlock();

    accept({LexType::lcurlbracket});

    while(true)
    {
        if(peek({LexType::while_kw}))
        {
            node->addStatement(parseWhileStatement());
            continue;
        }
        else if(peek({LexType::for_kw}))
        {
            node->addStatement(parseForStatement());
            continue;
        }
        else if(peek({LexType::id}))
        {
            node->addStatement(parseAssignmentOrFunctionCall());
            continue;
        }
        else if(peek({LexType::if_kw}))
        {
            node->addStatement(parseIfStatement());
            continue;
        }
        else if(peek({LexType::int_kw, LexType::string_kw, LexType::log_kw}))
        {
            node->addStatement(parseVariableDeclaration());
            continue;
        }
        else if(peek({LexType::rcurlbracket}))
        {
            accept({LexType::rcurlbracket});
            break;
        }
    }

    return node;
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

	node->setVariable(parseVariable(bufferedToken.text));

	accept({LexType::in_kw});

	node->setCollection(parseCollection());

	node->setBlock(parseStatement());
}

FunctionCall *Parser::parseFunCall(const std::string& id)
{
    FunctionCall* node = new FunctionCall();

    node->setName(id);

    if(!peek({LexType::lbracket})) //not a function call
    {
        delete node;
        return nullptr;
    }

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

    accept({LexType::semicolon});

    return node;
}

Statement* Parser::parseAssignmentOrFunctionCall()
{
    Statement* node;
    Token temp;

    if(peek({LexType::id}))
    {
        temp = bufferedToken;
        accept({LexType::id});
    }

    node = parseFunCall(temp.text);

    if(node == nullptr)//we have to parse assignment, not a function call
    {
        Assignment* assignmentNode = new Assignment();

        assignmentNode->setVariable(parseVariable(temp.text));

        accept({LexType::assign_op});

        assignmentNode->setAssignable(parseAssignable());

        accept({LexType::semicolon});

        node = assignmentNode;
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

Variable *Parser::parseVariable(const std::string& name)
{
    Variable* node = new Variable();

    node->setName(name);

    accept({LexType::id});

    return node;
}

LogVar* Parser::parseCollection()
{
    //TODO
}

VariableDeclaration *Parser::parseVariableDeclaration()
{
	VariableDeclaration* node = new VariableDeclaration();

	Token temp;

	if(peek({LexType::int_kw, LexType::string_kw, LexType::log_kw}))
    {
	    temp = bufferedToken;
        accept({LexType::int_kw, LexType::string_kw, LexType::log_kw});
    }

	node->setVarType(temp.type);

	if(peek({LexType::id}))
    {
	    node->setName(bufferedToken.text);
	    accept({LexType::id});
    }

	if(peek({LexType::assign_op}))
    {
	    accept({LexType::assign_op});

	    node->setValue(parseAssignable());
    }

	accept({LexType::semicolon});

	return node;
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
