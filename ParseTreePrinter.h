//
// Created by hborkows on 15.05.19.
//

#ifndef TKOM_INTERPRETER_PARSETREEPRINTER_H
#define TKOM_INTERPRETER_PARSETREEPRINTER_H

#include <iostream>

class ASTNode;

class ParseTreePrinter
{
public:
    ParseTreePrinter() = default;

    //void printParseTree(ASTNode* root) const;

    static void printIndent(size_t level);

private:
};


#endif //TKOM_INTERPRETER_PARSETREEPRINTER_H
