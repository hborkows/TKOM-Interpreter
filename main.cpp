#include <iostream>
#include "Modules/Interpreter.h"

int main(int argc, char** argv)
{
	std::vector<std::string> arguments(argv + 1, argv + argc);

    Interpreter::runProgram(arguments);

    std::cout << "Done" << std::endl;

    return 0;
}