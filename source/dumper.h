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


#ifndef tinyxml_DUMPER_H
#define tinyxml_DUMPER_H

#include "../include/element.h"
#include "../include/declare.h"

#include <fstream>


namespace tinyxml
{

    class Dumper
    {
    public:
        Dumper(Element& elem, Declare& declare, std::ofstream& ofs);

    public:
        int Do();

    private:
        int DumpDeclare();
        int DumpElement();
        int DumpChildElement(Element& elem, int rank);

    private:
        Element& rootElement_;
        Declare& declare_;
        std::ofstream& ofs_;
    };

}

#endif
