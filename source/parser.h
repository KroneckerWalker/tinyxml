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


#ifndef tinyxml_PARSER_H
#define tinyxml_PARSER_H

#include "../include/element.h"
#include "../include/declare.h"

#include <string>
#include <fstream>


namespace tinyxml
{

    class Parser
    {
    public:
        Parser(Element& elem, Declare& declare, std::ifstream& ifs);

    public:
        int Do();

    private:
        int ParseDeclare();
        int ParseElement(Element& element, const std::string& parentTag);
        int ParseAttribute(Attribute& attribute);
        int ParseComment();

        int ParseAttributeName(std::string& name);
        int ParseAttributeValue(std::string& value);

        void CountLines(char ch);

    private:
        Element& rootElement_;
        Declare& declare_;
        std::ifstream& ifs_;
        int line_;
    };

}

#endif
