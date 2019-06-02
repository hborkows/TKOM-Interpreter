//
// Created by hubertborkowski on 31.05.19.
//

#ifndef TKOM_INTERPRETER_SEMANTICCHECKER_H
#define TKOM_INTERPRETER_SEMANTICCHECKER_H

#include <unordered_map>
#include <string>
#include "Parser.h"
#include "../Structures/Ir/Function.h"
#include "../Structures/Ir/Executable.h"
#include "../Structures/Ir/AssignmentIr.h"
#include "../Structures/Ir/AssignableIr.h"
#include "../Structures/Ir/WhileIr.h"
#include "../Structures/Ir/VariableIr.h"
#include "../Structures/Ir/ConditionIr.h"
#include "../Structures/Ir/ExpressionIr.h"
#include "../Structures/Ir/BlockIr.h"
#include "../Structures/Ir/Scope.h"

class SemanticChecker
{
public:
    std::vector<Executable*> check(Program* parseTree);
private:
    Program* programTree;
    std::unordered_map<std::string, Function*> definedFunctions;

    //Function* checkFunction(FunctionDefinition definition);
    std::vector<Executable*> traverseTree();

    VariableIr* checkVariableDeclaration(Scope* scope, VariableDeclaration* variableDeclaration);
    AssignmentIr* checkAssignment(Scope* scope, Assignment* assignment);
    AssignableIr* checkAssignable(Scope* scope, Assignable* assignable);
    WhileIr* checkWhileStatement(Scope* scope, WhileStatement* whileStatement);
    VariableIr* checkVariable(Scope* scope, Variable* variable);
    ConditionIr* checkCondition(Scope* scope, Condition* condition);
    ExpressionIr* checkExpression(Scope* scope, Expression* expression);
    BlockIr* checkBlock(Scope* scope, StatementBlock* statementBlock);
};


#endif //TKOM_INTERPRETER_SEMANTICCHECKER_H
