//
// Created by hborkows on 05.05.19.
//

#include "Parser.h"

std::string lexNames[] = {
        "empty",
        "plus_op", "minus_op", "mul_op", "div_op", "assign_op", "access_op",
        "and_op", "or_op", "not_op", "gt_op", "lt_op", "ge_op", "le_op", "equal_op", "not_equal_op",
        "lbracket", "rbracket", "lcurlbracket", "rcurlbracket",
        "for_kw", "while_kw", "in_kw",
        "if_kw", "else_kw", "elif_kw",
        "int_const", "text_const",
        "id",
        "int_kw", "log_kw", "string_kw", "void_kw",
        "return_kw",
        "start_define", "end_define",
        "semicolon", "comma", "end_of_code",
        "unknown"
};

Parser::Parser(Lexer *lexer): bufferedToken(), tracer()
{
    this->lexer = lexer;
}

Parser::~Parser()
{
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
            std::cout << "Got token: " << lexNames[bufferedToken.type] << std::endl;
			getNextToken();
			return true;
		}
    }

	std::cout << "Parser Error: Expected token: ";
    for(auto item: acceptable)
    {
        std::cout << lexNames[item] << " ";
    }
    std::cout << "at line: " << bufferedToken.position.line << " col: " << bufferedToken.position.column << std::endl;

    //todo: throw custom exception

    exit(EXIT_FAILURE);
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

    if(peek({LexType::lcurlbracket}))
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
        else if(peek({LexType::return_kw}))
        {
            node = parseReturnStatement();
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

    std::cout << "Parsing Assignable" << std::endl;

    if(peek({LexType::id}))
    {
        temp = bufferedToken;
        //accept({LexType::id});

        node = parseFunCall(temp.text);

        if(node == nullptr)
        {
            if(peek({LexType::gt_op, LexType::ge_op, LexType::lt_op, LexType::le_op, LexType::equal_op, LexType::not_equal_op}))
                node = parseCondition();
        }
        if(node == nullptr)
        {
            node = parseExpression();
        }
    }
    else if(peek({LexType::not_op}))
    {
        node = parseCondition();
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

    std::cout << "Parsing condition" << std::endl;

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
            Token temp = bufferedToken;

            accept({LexType::id});

            node->addOperand(parseVariableOrAccess(temp.text));
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

    std::cout << "Parsing expression" << std::endl;

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
        Token temp = bufferedToken;

        accept({LexType::id});

        Variable* node = parseVariableOrAccess(temp.text);

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

    std::cout << "Parsing literal" << std::endl;

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

    std::cout << "Parsing for" << std::endl;

	accept({LexType::for_kw});

	auto var = new VariableDeclaration();

	Token temp = bufferedToken;

	accept({LexType::id});

	var->setName(bufferedToken.text);
	var->setVarType(LexType::log_kw);

	node->setVariable(var);

	accept({LexType::in_kw});

	node->setCollection(parseCollection());

	node->setBlock(parseStatement());

	return node;
}

FunctionCall *Parser::parseFunCall(const std::string& id)
{
    auto node = new FunctionCall();

    std::cout << "Parsing function call" << std::endl;

    node->setName(id);

    accept({LexType::id});

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

    return node;
}

Statement* Parser::parseAssignmentOrFunctionCall()
{
    Statement* node;
    Token temp;

    std::cout << "AssignmentOrFunctionCall" << std::endl;

    if(peek({LexType::id}))
    {
        temp = bufferedToken;
    }

    node = parseFunCall(temp.text);

    if(node == nullptr)//we have to parse assignment, not a function call
    {
        auto assignmentNode = new Assignment();

        assignmentNode->setVariable(parseVariableOrAccess(temp.text));

        accept({LexType::assign_op});

        assignmentNode->setAssignable(parseAssignable());

        node = assignmentNode;
    }

    accept({LexType::semicolon});

    return node;
}

IfStatement *Parser::parseIfStatement()
{
    auto node = new IfStatement();

    std::cout << "Parsing if" << std::endl;

    accept({LexType::if_kw});

    accept({LexType::lbracket});

    node->setCondition(parseCondition());

    accept({LexType::rbracket});

    //tracer->enterBlock();

    node->setTrueStatement(parseStatement());

    //tracer->exitBlock();

    if(peek({LexType::else_kw}))
    {
        accept({LexType::else_kw});
        //tracer->enterBlock();
        node->setFalseStatement(parseStatement());
        //tracer->exitBlock();
    }

    return node;
}

ReturnStatement *Parser::parseReturnStatement()
{
    auto node = new ReturnStatement();

    std::cout << "Parsing return" << std::endl;

	accept({LexType::return_kw});

    node->setAssignableNode(parseAssignable());

	accept({LexType::semicolon});

	return node;
}

Variable *Parser::parseVariableOrAccess(const std::string& name)
{
    auto node = new Variable();

    std::cout << "Parsing Variable" << std::endl;

    node->setName(name);

    //accept({LexType::id});

    if(peek({LexType::access_op}))
    {
        auto accessNode = new FieldAccess();

        accessNode->setLogVar(node);

        accept({LexType::access_op});

        Token temp = bufferedToken;

        accept({LexType::id});

        accessNode->setFieldName(temp.text);

        return accessNode;
    }

    return node;
}

LogVar* Parser::parseCollection()
{
    auto node = new LogVar();

    std::cout << "Parsing collection" << std::endl;

    if(peek({LexType::id}))
    {
        node->setName(bufferedToken.text);
        accept({LexType::id});
    }

    return node;
}

VariableDeclaration *Parser::parseVariableDeclaration()
{
	auto node = new VariableDeclaration();

    std::cout << "Parsing Variable declaration" << std::endl;

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

    std::cout << "Parsing while" << std::endl;

	accept({LexType::while_kw});

	accept({LexType::lbracket});

	node->setCondition(parseCondition());

	accept({LexType::rbracket});

	node->setStatement(parseStatement());

	return node;
}
