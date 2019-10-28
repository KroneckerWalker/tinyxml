#include <iostream>
#include "../include/tinyxml.h"

int main(int argc, char* argv[])
{
    tinyxml::Document doc;

    int ret = doc.LoadContent(std::string("game.xml"));
    if (ret != tinyxml::SUCCESS)
    {
        return ret;
    }

    ret = doc.DumpContent(std::string("gamedump.xml"));

    return ret;
}
