//
// Created by hubertborkowski on 31.05.19.
//

#ifndef TKOM_INTERPRETER_INTERPRETER_H
#define TKOM_INTERPRETER_INTERPRETER_H


#include "Lexer.h"
#include "Parser.h"
#include "SemanticChecker.h"
#include "Executor.h"

class Interpreter
{
public:
  static void runProgram(std::vector<std::string> arguments)
  {
	  if(arguments.size() == 0)
	  {
		  std::cout << "No source file specified!" << std::endl;
		  return;
	  }

	  Source source(arguments.at(0));
	  Lexer lexer(&source);
	  Parser parser(&lexer);
	  SemanticChecker semanticChecker;
	  Executor executor;

	  auto programTree = parser.parse();
  }
};


#endif //TKOM_INTERPRETER_INTERPRETER_H
