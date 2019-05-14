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
    Tracer();

    void enter(const std::string& msg);

    void leave(const std::string& msg = " ");

    size_t getLevel() {return level;}

private:
    size_t level;

    void printIndent();
};


#endif //TKOM_INTERPRETER_TRACER_H
