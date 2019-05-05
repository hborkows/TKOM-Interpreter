cmake_minimum_required(VERSION 3.12)
project(TKOM_Interpreter)

set(CMAKE_CXX_STANDARD 14)

add_executable(TKOM_Interpreter main.cpp Source.cpp Source.h Lexer.cpp Lexer.h AST/ASTNode.h AST/Lvalue.cpp AST/Lvalue.h
        AST/Assignable.cpp AST/Assignable.h AST/Variable.cpp AST/Variable.h AST/VariableDeclaration.cpp AST/VariableDeclaration.h
        AST/FunctionCall.cpp AST/FunctionCall.h AST/Assignment.h AST/ReturnStatement.h
        AST/WhileStatement.cpp AST/WhileStatement.h AST/ForStatement.cpp AST/ForStatement.h AST/IfStatement.cpp AST/IfStatement.h
        Tracer.cpp Tracer.h Parser.cpp Parser.h)