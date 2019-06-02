//
// Created by hborkows on 02.06.19.
//

#ifndef TKOM_INTERPRETER_BLOCKIR_H
#define TKOM_INTERPRETER_BLOCKIR_H

#include <vector>
#include "Executable.h"

class BlockIr: public Executable
{
public:
    BlockIr() = default;

    void addInstruction(Executable* instruction)
    {
        instructions.push_back(instruction);
    }
private:
    std::vector<Executable*> instructions;
};


#endif //TKOM_INTERPRETER_BLOCKIR_H
