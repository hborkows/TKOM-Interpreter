#include <iostream>
#include "Source.h"
#include "Lexer.h"

int main()
{
    Source source("/home/hubertborkowski/Studia/example1.txt");
    Lexer lexer(&source);
    std::vector<Token> tokens;

    bool done = false;

    while(!done)
    {
        tokens.push_back(lexer.nextToken());
        if(tokens.back().type == 33)
            done = true;
        std::cout << "working..." << tokens.back().type << " " << tokens.back().text << std::endl;
    }

    for(Token it: tokens)
    {
        int line = it.position.line;
        int col = it.position.column;
        std::cout << "Token at line: " << line << " column: " << col << std::endl;
    }

    return 0;
}