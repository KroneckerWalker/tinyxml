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


#ifndef tinyxml_DOCUMENT_H
#define tinyxml_DOCUMENT_H

#include <string>
#include "declare.h"
#include "element.h"

namespace tinyxml
{

    class Document
    {
    public:
        int LoadContent(const std::string &file);
        int DumpContent(const std::string &file);
        int ClearContent();

        Declare GetDeclare();
        Element GetElement();

        void SetDeclare(const std::string& version, const std::string& encoding, const std::string& standalone);
        void SetElementTagName(const std::string& tagName);

    private:
        Element element_;
        Declare declare_;
    };

}

#endif
