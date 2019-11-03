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


#ifndef tinyxml_ATTRIBUTE_H
#define tinyxml_ATTRIBUTE_H

#include <string>

namespace tinyxml
{

    class Attribute
    {
    public:
        Attribute();
        Attribute(const std::string& name, const std::string& value);
        Attribute(const Attribute& attri);
        Attribute& operator=(const Attribute& attri);

        void SetName(const std::string& name);
        void SetValue(const std::string& value);
        const std::string& GetName() const;
        const std::string& GetValue() const;

        bool IsNull() const;

    private:
        std::string name_;
        std::string value_;
    };

}

#endif
