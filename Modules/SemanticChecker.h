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

class SemanticChecker
{
public:
private:
    Program* programTree;
    std::unordered_map<std::string, Function*> definedFunctions;

    Function* checkFunction(FunctionDefinition definition);

    void checkVariableDeclaration(Scope* scope, VariableDeclaration variableDeclaration);
    AssignmentIr* checkAssignment(Scope* scope, Assignment assignment);
    AssignableIr checkAssignable(Scope* scope, Assignable* assignable);
};


#endif //TKOM_INTERPRETER_SEMANTICCHECKER_H
