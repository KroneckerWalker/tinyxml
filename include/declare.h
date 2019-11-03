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


#ifndef tinyxml_DECLARE_H
#define tinyxml_DECLARE_H

#include "attribute.h"

namespace tinyxml
{

    class Declare
    {
    public:
        Declare();

    public:
        void SetVersion(const std::string& version);
        void SetEncoding(const std::string& encoding);
        void SetStandalone(const std::string& standalone);
        std::string GetVersion() const;
        std::string GetEncoding() const;
        std::string GetStandalone() const;

        void Clear();

    private:
        Attribute version_;
        Attribute encoding_;
        Attribute standalone_;
    };

}

#endif
