cmake_minimum_required(VERSION 3.9)
project(TKOM_Interpreter)

set(CMAKE_CXX_STANDARD 14)

add_executable(TKOM_Interpreter main.cpp Modules/Source.cpp Modules/Source.h Modules/Lexer.cpp Modules/Lexer.h Structures/AST/ASTNode.h
        Structures/AST/Assignable.h Structures/AST/Variable.h Structures/AST/VariableDeclaration.h
        Structures/AST/FunctionCall.h Structures/AST/Assignment.h Structures/AST/ReturnStatement.h
        Structures/AST/WhileStatement.h Structures/AST/ForStatement.h Structures/AST/IfStatement.h
        Modules/Tracer.cpp Modules/Tracer.h Modules/Parser.cpp Modules/Parser.h Structures/AST/Expression.h
        Structures/AST/StatementBlock.h Structures/AST/Condition.h Structures/AST/Statement.h Structures/AST/LogVar.h
        Structures/LogEntry.cpp Structures/LogEntry.h Structures/AST/FunctionDefinition.h Structures/AST/Literal.h Structures/AST/Program.h
        Structures/AST/FieldAccess.h ParseTreePrinter.cpp ParseTreePrinter.h Structures/AST/LexNames.h Modules/Interpreter.h Modules/Executor.cpp Modules/Executor.h Modules/SemanticChecker.cpp Modules/SemanticChecker.h Structures/Ir/Executable.h Structures/Ir/Scope.h Structures/Ir/Function.h Structures/Ir/AssignableIr.h Structures/Ir/ExpressionOperand.h Structures/Ir/ConditionOperand.h Structures/Ir/VariableIr.h Structures/Ir/StringVar.h Structures/Ir/IntVar.h Structures/Ir/CollectionVar.h Structures/Ir/Collection.h Structures/Ir/Literal.h Structures/Ir/AssignmentIr.h Structures/Ir/WhileIr.h Structures/Ir/ConditionIr.h Structures/Ir/ExpressionIr.h Structures/Ir/StatementIr.h Structures/Ir/BlockIr.h)