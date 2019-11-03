// Copyright (C) 2019, Walker
// Contact: walkerrrr@126.com
//
// This file is part of the tinyxml library. This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// Author: walkerrrr@126.com (Walker)


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

    tinyxml::Element elem = doc.GetElement();
    tinyxml::Element e = elem.GetFirstChildElement();
    while (!e.IsNull())
    {
        std::cout<<"Element: "<<e.GetTagName()<<std::endl;
        std::string str = e.GetAttribute(std::string("Name"));
        std::cout<<"\tAttribute [Name]="<<str<<std::endl;
        e = e.GetNextSiblingElement();
    }

    ret = doc.DumpContent(std::string("gamedump.xml"));

    return ret;
}
