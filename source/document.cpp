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


#include "../include/error.h"
#include "../include/document.h"

#include <fstream>

#include "parser.h"
#include "dumper.h"


namespace tinyxml
{

int Document::LoadContent(const std::string &file)
{
    if (file.empty())
    {
        return ERROR_FileNameEmpty;
    }

    std::ifstream ifs(file.c_str());
    if (!ifs)
    {
        return ERROR_FileNotOpen;
    }
    ifs >> std::noskipws;

    ClearContent();

    Parser parser(element_, declare_, ifs);
    parser.Do();

    return SUCCESS;
}

int Document::DumpContent(const std::string &file)
{
    if (file.empty())
    {
        return ERROR_FileNameEmpty;
    }

    std::ofstream ofs(file.c_str());
    if (!ofs)
    {
        return ERROR_FileNotOpen;
    }

    Dumper dumper(element_, declare_, ofs);
    dumper.Do();

    return SUCCESS;
}

int Document::ClearContent()
{
    declare_.Clear();
    element_.Clear();
    return SUCCESS;
}

Declare Document::GetDeclear()
{
    return declare_;
}

Element Document::GetElement()
{
    return element_;
}

}
