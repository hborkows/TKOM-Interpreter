//
// Created by hborkows on 05.04.19.
//

#include "Source.h"

Source::Source(const std::string &fileName) : fileName(fileName), firstNotConsumed()
{
    fin = std::fstream(fileName, std::fstream::in);
}

char Source::peek()
{
    return firstNotConsumed;
}

char Source::take()
{
    char tmp = firstNotConsumed;
    readCharFromFile();
    return tmp;
}

void Source::readCharFromFile()
{
    fin >> std::noskipws >> firstNotConsumed;
}