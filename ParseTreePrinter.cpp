//
// Created by hborkows on 15.05.19.
//

#include "ParseTreePrinter.h"

//void ParseTreePrinter::printParseTree(ASTNode* root) const
//{
//    root->print(0);
//}

void ParseTreePrinter::printIndent(size_t level)
{
    std::cout << "|";
    for(int i = level - 1; i > 0; --i)
    {
        std::cout << "--";
    }
    std::cout << "|";
}
