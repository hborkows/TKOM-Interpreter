//
// Created by hborkows on 05.04.19.
//

#include "Source.h"

Source::Source(const std::string &fileName) : fileName(fileName), firstNotConsumed()
{
    fin.open(fileName, std::fstream::in);
    position.line = 1;
    position.column = 0;
}

char Source::peek()
{
    if(firstNotConsumed == 0)
        readCharFromFile();

    return firstNotConsumed;
}

char Source::take()
{
    if(firstNotConsumed == 0)
        readCharFromFile();

    char tmp = firstNotConsumed;
    readCharFromFile();
    return tmp;
}

void Source::readCharFromFile()
{
    fin >> std::noskipws >> firstNotConsumed;

    position.column++;

    if(firstNotConsumed == EOF)
        firstNotConsumed = '$';
    else if(firstNotConsumed == '\n')
    {
        position.line++;
        readCharFromFile();
    }
}