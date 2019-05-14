//
// Created by hborkows on 05.05.19.
//

#include "Tracer.h"

void Tracer::enterBlock(const std::string& msg)
{
    level++;

    printIndent();

    std::cout << msg << std::endl;
}

void Tracer::exitBlock(const std::string& msg)
{
    if(level == 0)
    {
        std::cout << "Cant leave level 0!" << std::endl;
        return;
    }

    level--;

    printIndent();

    std::cout << msg <<std::endl;
}

void Tracer::printIndent()
{
    for(int i = level - 1; i > 0; --i)
    {
        std::cout << "| ";
    }
    std::cout << "|-";
}
