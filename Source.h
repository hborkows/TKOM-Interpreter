//
// Created by hborkows on 05.04.19.
//

#ifndef TKOM_INTERPRETER_SOURCE_H
#define TKOM_INTERPRETER_SOURCE_H

#include <string>
#include <fstream>

struct TextPosition
{
    int line;
    int column;
};

class Source
{
public:
    explicit Source(const std::string &fileName);

    char peek();
    char take();
    TextPosition getPosition() {return position;}

private:
    std::string fileName;
    std::fstream fin;
    char firstNotConsumed;
    TextPosition position;

    void readCharFromFile();
};


#endif //TKOM_INTERPRETER_SOURCE_H
