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
    delete tracer;
}

Program *Parser::parse()
{
    auto program = new Program();
	getNextToken();
	bool definitionBlockOpened = false;

	if(peek({LexType::start_define}))
    {
	    accept({LexType::start_define});
	    definitionBlockOpened = true;

        while (!peek({LexType::end_of_code, LexType::end_define}))
        {
            program->addFunction(parseFunctionDefinition());
        }
    }

	if(peek({LexType::end_of_code}))
    {
	    accept({LexType::end_of_code});
	    return program;
    }
	else if(definitionBlockOpened)
    {
        accept({LexType::end_define});
    }

	while(!peek({LexType::end_of_code}))
    {
	    program->addStatement(parseStatement());
    }

	accept({LexType::end_of_code});

    return program;
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
    auto node = new FunctionDefinition();

    if(peek({LexType::int_kw, LexType::string_kw, LexType::void_kw}))
    {
        node->setReturntype(bufferedToken.type);
        accept({LexType::int_kw, LexType::string_kw, LexType::void_kw});
    }
    else
    {
        return nullptr;
    }

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
    auto node = new StatementBlock();

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
    Statement* node;

    if(peek({LexType::rcurlbracket}))
    {
        node = parseBlock();
    }
    else
    {
        if(peek({LexType::while_kw}))
        {
            node = parseWhileStatement();
        }
        else if(peek({LexType::for_kw}))
        {
            node = parseForStatement();
        }
        else if(peek({LexType::id}))
        {
            node = parseAssignmentOrFunctionCall();
        }
        else if(peek({LexType::if_kw}))
        {
            node = parseIfStatement();
        }
        else if(peek({LexType::int_kw, LexType::string_kw, LexType::log_kw}))
        {
            node = parseVariableDeclaration();
        }
        else
        {
            node = nullptr;
        }
    }

    return node;
}

Assignable *Parser::parseAssignable()
{
    Assignable* node;
    Token temp;

    if(peek({LexType::id}))
    {
        temp = bufferedToken;
        accept({LexType::id});

        node = parseFunCall(temp.text);

        if(node == nullptr)
        {
            node = parseExpression();
        }
    }
    else
    {
        node = parseExpression();
    }

    return node;
}

Condition *Parser::parseCondition()
{
    auto node = new Condition();

    node->addOperand(parseAndCondition());

    while(peek({LexType::or_op}))
    {
        node->setOperation(LexType::or_op);
        accept({LexType::or_op});
        node->addOperand(parseAndCondition());
    }

    return node;
}

Condition* Parser::parseAndCondition()
{
    auto node = new Condition();

    node->addOperand(parseEqualCondition());

    while(peek({LexType::and_op}))
    {
        node->setOperation(LexType::and_op);
        accept({LexType::and_op});
        node->addOperand(parseEqualCondition());
    }

    return node;
}

Condition* Parser::parseEqualCondition()
{
    auto node = new Condition();

    node->addOperand(parseRelationCondition());

    while(peek({LexType::equal_op, LexType::not_equal_op}))
    {
        node->setOperation(bufferedToken.type);
        accept({LexType::equal_op, LexType::not_equal_op});
        node->addOperand(parseRelationCondition());
    }

    return node;
}

Condition* Parser::parseRelationCondition()
{
    auto node = new Condition();

    node->addOperand(parsePrimaryCondition());

    while(peek({LexType::ge_op, LexType::gt_op, LexType::le_op, LexType::lt_op}))
    {
        node->setOperation(bufferedToken.type);
        accept({LexType::ge_op, LexType::gt_op, LexType::le_op, LexType::lt_op});
        node->addOperand(parsePrimaryCondition());
    }

    return node;
}

ASTNode* Parser::parsePrimaryCondition()
{
    auto node = new Condition();

    if(peek({LexType::not_op}))
    {
        node->setNegated(true);
        accept({LexType::not_op});
    }

    if(peek({LexType::lbracket}))
    {
        accept({LexType::lbracket});
        node->addOperand(parseCondition());
        accept({LexType::rbracket});
    }
    else
    {
        if(peek({LexType::id}))
        {
            node->addOperand(parseVariable(bufferedToken.text));
        }
        else
        {
            node->addOperand(parseLiteral());
        }
    }

    return node;
}

Expression *Parser::parseExpression()
{
    auto node = new Expression();

    node->addOperand(parseMultiplicativeExpression());

    while(peek({LexType::plus_op, LexType::minus_op}))
    {
        node->addOperator(bufferedToken.type);

        accept({LexType::plus_op, LexType::minus_op});

        node->addOperand(parseMultiplicativeExpression());
    }

    return node;
}

Expression* Parser::parseMultiplicativeExpression()
{
    auto node = new Expression();

    node->addOperand(parsePrimaryExpression());

    while(peek({LexType::div_op, LexType::mul_op}))
    {
        node->addOperator(bufferedToken.type);

        accept({LexType::div_op, LexType::mul_op});

        node->addOperand(parsePrimaryExpression());
    }

    return node;
}

ASTNode* Parser::parsePrimaryExpression()
{
    if(peek({LexType::id}))
    {
        Variable* node = parseVariable(bufferedToken.text);

        return node;
    }
    else if(peek({LexType::lbracket}))
    {
        accept({LexType::lbracket});

        Expression* node = parseExpression();

        accept({LexType::rbracket});

        return node;
    }
    else
    {
        Literal* node = parseLiteral();

        return node;
    }
}

Literal* Parser::parseLiteral()
{
    auto node = new Literal();

    if(peek({LexType::text_const}))
    {
        node->setLiteralType(bufferedToken.type);
        node->setTextValue(bufferedToken.text);
        accept({LexType::text_const});
    }
    else if(peek({LexType::int_const}))
    {
        node->setLiteralType(bufferedToken.type);
        node->setIntValue(bufferedToken.value);
        accept({LexType::int_const});
    }

    return node;
}

ForStatement *Parser::parseForStatement()
{
    auto node = new ForStatement();

	accept({LexType::for_kw});

	node->setVariable(parseVariable(bufferedToken.text));

	accept({LexType::in_kw});

	node->setCollection(parseCollection());

	node->setBlock(parseStatement());
}

FunctionCall *Parser::parseFunCall(const std::string& id)
{
    auto node = new FunctionCall();

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
        auto assignmentNode = new Assignment();

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
    auto node = new IfStatement();

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
    auto node = new ReturnStatement();

	accept({LexType::return_kw});

    node->setAssignableNode(parseAssignable());

	accept({LexType::semicolon});

	return node;
}

Variable *Parser::parseVariable(const std::string& name)
{
    auto node = new Variable();

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
	auto node = new VariableDeclaration();

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
    auto node = new WhileStatement();

	accept({LexType::while_kw});

	accept({LexType::lbracket});

	node->setCondition(parseCondition());

	accept({LexType::rbracket});

	node->setStatement(parseStatement());

	return node;
}
