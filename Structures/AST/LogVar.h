//
// Created by hborkows on 08.05.19.
//

#ifndef TKOM_INTERPRETER_LOGVAR_H
#define TKOM_INTERPRETER_LOGVAR_H


#include "Variable.h"
#include "../LogEntry.h"
#include <vector>

class LogVar: public Variable
{
public:
    LogVar(): log()
    {

    }

    void addEntry(const LogEntry& entry) {log.push_back(entry);}

    void print(size_t level)const override
    {
        ParseTreePrinter::printIndent(level);

        std::cout << "Collection: " << name << std::endl;
    }
protected:
    std::vector<LogEntry> log;
};


#endif //TKOM_INTERPRETER_LOGVAR_H
