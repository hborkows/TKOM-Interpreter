cmake_minimum_required(VERSION 3.12)
project(TKOM_Interpreter)

set(CMAKE_CXX_STANDARD 14)

add_executable(TKOM_Interpreter main.cpp Source.cpp Source.h Lexer.cpp Lexer.h AST/ASTNode.h AST/Lvalue.cpp AST/Lvalue.h
        AST/Assignable.cpp AST/Assignable.h AST/Variable.cpp AST/Variable.h AST/VariableDeclaration.h
        AST/FunctionCall.h AST/Assignment.h AST/ReturnStatement.h
        AST/WhileStatement.h AST/ForStatement.h AST/IfStatement.h
        Tracer.cpp Tracer.h Parser.cpp Parser.h AST/Expression.h AST/StatementBlock.h AST/Condition.h)