//
// Created by hborkows on 05.05.19.
//

#ifndef TKOM_INTERPRETER_TRACER_H
#define TKOM_INTERPRETER_TRACER_H


#include <glob.h>
#include <string>

class Tracer
{
public:
    Tracer() = default;

    void print(const std::string& msg);

    void enterBlock();

    void exitBlock();

    size_t getLevel() {return level;}

private:
    size_t level;


};


#endif //TKOM_INTERPRETER_TRACER_H
