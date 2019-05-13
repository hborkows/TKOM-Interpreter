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

Source::~Source()
{
    fin.close();
}

char Source::peek()
{
    if (firstNotConsumed == 0)
        readCharFromFile();

    return firstNotConsumed;
}

void Source::take()
{
    if (firstNotConsumed == 0)
        readCharFromFile();

    readCharFromFile();
}

void Source::readCharFromFile()
{
    fin >> std::noskipws >> firstNotConsumed;

    position.column++;

    if (firstNotConsumed == EOF)
        firstNotConsumed = '$';
    else if (firstNotConsumed == '\n')
    {
        position.line++;
        position.column = 1;
        readCharFromFile();
    }
}