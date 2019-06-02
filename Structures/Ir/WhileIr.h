//
// Created by hborkows on 02.06.19.
//

#ifndef TKOM_INTERPRETER_WHILEIR_H
#define TKOM_INTERPRETER_WHILEIR_H


#include "Executable.h"
#include "BlockIr.h"
#include "ConditionIr.h"

class WhileIr: public Executable
{
public:
    WhileIr() = default;

    BlockIr* getBlock() const
    {
        return block;
    }

    void setBlock(BlockIr* block)
    {
        WhileIr::block = block;
    }

    ConditionIr* getCondition() const
    {
        return condition;
    }

    void setCondition(ConditionIr* condition)
    {
        WhileIr::condition = condition;
    }

private:
    BlockIr* block;
    ConditionIr* condition;
};


#endif //TKOM_INTERPRETER_WHILEIR_H
