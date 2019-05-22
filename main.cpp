#include <iostream>
#include "Modules/Source.h"
#include "Modules/Lexer.h"
#include "Modules/Parser.h"

int main()
{
    Source source("example1.txt");
    Lexer lexer(&source);
    std::vector<Token> tokens;
    Parser parser(&lexer);
    ParseTreePrinter printer;

    auto parseTree = parser.parse();

    //printer.printParseTree(parseTree);

    parseTree->print(0);

    std::cout << "Done" << std::endl;

    return 0;
}