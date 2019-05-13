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

    //auto parseTree = parser.parse();

    //std::cout << "Done" << std::endl;

    bool done = false;

    while(!done)
    {
        tokens.push_back(lexer.nextToken());

        std::cout << "working..." << tokens.back().type << " " << tokens.back().text << std::endl;
        if(tokens.back().type == end_of_code)
        {
            done = true;
            std::cout << "Done" << std::endl;
        }
    }

    for(Token it: tokens)
    {
        int line = it.position.line;
        int col = it.position.column;
        std::cout << "Token at line: " << line << " column: " << col << std::endl;
    }

    return 0;
}