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


#include "gtest/gtest.h"
#include "../include/tinyxml.h"

TEST(AttributeTest, InitValue)
{
    tinyxml::Attribute attri1;
    EXPECT_EQ("null", attri1.GetName());
    EXPECT_EQ("null", attri1.GetValue());

    tinyxml::Attribute attri2("Film", "Harry Pottor");
    EXPECT_EQ("Film", attri2.GetName());
    EXPECT_EQ("Harry Pottor", attri2.GetValue());

    tinyxml::Attribute attri3(attri2);
    EXPECT_EQ("Film", attri3.GetName());
    EXPECT_EQ("Harry Pottor", attri3.GetValue());

    attri1 = attri2;
    EXPECT_EQ("Film", attri1.GetName());
    EXPECT_EQ("Harry Pottor", attri1.GetValue());
}

TEST(AttributeTest, SetGetValue)
{
    tinyxml::Attribute attri;
    attri.SetName("MusicEnabled");
    attri.SetValue("1");

    EXPECT_EQ("MusicEnabled", attri.GetName());
    EXPECT_EQ("1", attri.GetValue());
}
