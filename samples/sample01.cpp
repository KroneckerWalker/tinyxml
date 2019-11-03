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


#include "../include/tinyxml.h"

int main(int argc, char* argv[])
{
    tinyxml::Document doc;
    doc.SetDeclare("1.0", "UTF-8", "yes");
    doc.SetElementTagName("GameProfile");

    tinyxml::Element ele = doc.GetElement();
    ele.AppendChildElement(tinyxml::Element("Player"));
    tinyxml::Element child1 = ele.GetLastChildElement();
    child1.SetAttribute(std::string("Name"), std::string("Nancy"));
    child1.SetAttribute(std::string("Gender"), std::string("Female"));
    child1.SetAttribute(std::string("Age"), std::string("23"));

    ele.AppendChildElement(tinyxml::Element("Player"));
    tinyxml::Element child2 = ele.GetLastChildElement();
    child2.SetAttribute(std::string("Name"), std::string("Maria"));
    child2.SetAttribute(std::string("Gender"), std::string("Female"));
    child2.SetAttribute(std::string("Age"), std::string("12"));

    child2.AppendChildElement(tinyxml::Element("Hobby"));
    tinyxml::Element child3 = child2.GetLastChildElement();
    child3.SetAttribute(std::string("Name"), std::string("Draw"));
    child3.SetAttribute(std::string("Period"), std::string("Weekly"));

    doc.DumpContent(std::string("game.xml"));

    return 1;
}
