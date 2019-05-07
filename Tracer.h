//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_TRACER_H
#define TKOM_INTERPRETER_TRACER_H


#include <glob.h>

class Tracer
{
public:
    Tracer() = default;

    void enterBlock();

    void exitBlock();

    size_t getLevel() {return level;}

private:
    size_t level;


};


#endif //TKOM_INTERPRETER_TRACER_H
