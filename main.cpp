#include <iostream>
#include "Source.h"

int main()
{
    Source source("test.txt");
    for(int i = 0; i < 50; i++)
    {
        std::cout << source.peek() << " " << source.getPosition().line << ", " << source.getPosition().column << std::endl;
        source.take();
    }
    return 0;
}