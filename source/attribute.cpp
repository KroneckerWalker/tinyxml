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


#include "../include/attribute.h"


namespace tinyxml
{

Attribute::Attribute() : name_("null"), value_("null")
{
}

Attribute::Attribute(const std::string& name, const std::string& value) : name_(name), value_(value)
{
}

Attribute::Attribute(const Attribute& attri) : name_(attri.name_), value_(attri.value_)
{
}

Attribute& Attribute::operator=(const Attribute& attri)
{
    name_ = attri.name_;
    value_ = attri.value_;
    return *this;
}

void Attribute::SetName(const std::string& name)
{
    name_ = name;
}

void Attribute::SetValue(const std::string& value)
{
    value_ = value;
}

const std::string& Attribute::GetName() const
{
    return name_;
}

const std::string& Attribute::GetValue() const
{
    return value_;
}

bool Attribute::IsNull() const
{
    return (0 == name_.compare("null"));
}

}
