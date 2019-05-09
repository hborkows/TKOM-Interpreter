//
// Created by hborkows on 05.05.19.
//

#include "Tracer.h"

void Tracer::enterBlock()
{
    level++;
}

void Tracer::exitBlock()
{
    level--;
}
