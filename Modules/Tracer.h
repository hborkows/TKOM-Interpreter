//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_TRACER_H
#define TKOM_INTERPRETER_TRACER_H

#include <string>
#include <iostream>

class Tracer
{
public:
    Tracer() = default;

    void enterBlock(const std::string& msg);

    void exitBlock(const std::string& msg = "Leaving");

    size_t getLevel() {return level;}

private:
    size_t level;

    void printIndent();
};


#endif //TKOM_INTERPRETER_TRACER_H
