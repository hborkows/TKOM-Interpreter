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
    if(fin.is_open())
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
    if(fin.eof())
    {
        firstNotConsumed = '$';
        fin.close();
    }

    fin >> std::noskipws >> firstNotConsumed;

    position.column++;

    if (firstNotConsumed == '\n')
    {
        position.line++;
        position.column = 0;
    }
}