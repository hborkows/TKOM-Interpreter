//
// Created by hborkows on 05.04.19.
//

#ifndef TKOM_INTERPRETER_SOURCE_H
#define TKOM_INTERPRETER_SOURCE_H

#include <string>
#include <fstream>


class Source
{
public:
    explicit Source(const std::string &fileName);

    char peek();
    char take();

private:
    std::string fileName;
    std::fstream fin;
    char firstNotConsumed;

    void readCharFromFile();
};


#endif //TKOM_INTERPRETER_SOURCE_H
