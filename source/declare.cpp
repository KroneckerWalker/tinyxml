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


#include "../include/declare.h"


namespace tinyxml
{

Declare::Declare() 
: version_(std::string("version"), std::string("null")),
  encoding_(std::string("encoding"), std::string("null")),
  standalone_(std::string("standalone"), std::string("null"))
{
}

void Declare::SetVersion(const std::string& version)
{
    version_.SetValue(version);
}

void Declare::SetEncoding(const std::string& encoding)
{
    encoding_.SetValue(encoding);
}

void Declare::SetStandalone(const std::string& standalone)
{
    standalone_.SetValue(standalone);
}

std::string Declare::GetVersion() const
{
    return version_.GetValue();
}

std::string Declare::GetEncoding() const
{
    return encoding_.GetValue();
}

std::string Declare::GetStandalone() const
{
    return standalone_.GetValue();
}

void Declare::Clear()
{
    version_.SetValue(std::string("null"));
    encoding_.SetValue(std::string("null"));
    standalone_.SetValue(std::string("null"));
}

}
