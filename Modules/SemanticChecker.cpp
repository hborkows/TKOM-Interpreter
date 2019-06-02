//
// Created by hubertborkowski on 31.05.19.
//

#include "SemanticChecker.h"

std::vector<Executable*> SemanticChecker::check(Program* parseTree)
{
    programTree = parseTree;

    return traverseTree();
}

std::vector<Executable*> SemanticChecker::traverseTree()
{
    std::vector<Executable*> instructions;
    Scope* topLevelScope = new Scope(nullptr);

    for(Statement* statement: programTree->getStatements())
    {
        if(statement->getType() == ASTNode::Type::block)
        {
            instructions.push_back(checkBlock(topLevelScope, dynamic_cast<StatementBlock*>(statement)));
        }
        else if(statement->getType() == ASTNode::Type::while_statement)
        {
            instructions.push_back(checkWhileStatement(topLevelScope, dynamic_cast<WhileStatement*>(statement)));
        }
        else if(statement->getType() == ASTNode::Type::var_declaration)
        {
            if(!topLevelScope->addVariable(checkVariableDeclaration(topLevelScope, dynamic_cast<VariableDeclaration*>(statement))))
            {
                std::cout << "Redeclaration of variable: " << dynamic_cast<VariableDeclaration*>(statement)->getName() << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }

    return instructions;
}

VariableIr* SemanticChecker::checkVariableDeclaration(Scope* scope, VariableDeclaration* variableDeclaration)
{

}

AssignmentIr* SemanticChecker::checkAssignment(Scope* scope, Assignment* assignment)
{
    return nullptr;
}

AssignableIr* SemanticChecker::checkAssignable(Scope* scope, Assignable* assignable)
{
    return nullptr;
}

WhileIr* SemanticChecker::checkWhileStatement(Scope* scope, WhileStatement* whileStatement)
{
    WhileIr* result = new WhileIr();

    result->setCondition(checkCondition(scope, whileStatement->getCondition()));
    result->setBlock(checkBlock(scope, ))
}

VariableIr* SemanticChecker::checkVariable(Scope* scope, Variable* variable)
{
    return nullptr;
}

ConditionIr* SemanticChecker::checkCondition(Scope* scope, Condition* condition)
{
    return nullptr;
}

ExpressionIr* SemanticChecker::checkExpression(Scope* scope, Expression* expression)
{
    return nullptr;
}

BlockIr* SemanticChecker::checkBlock(Scope* scope, StatementBlock* statementBlock)
{
    return nullptr;
}
