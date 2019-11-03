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


TEST(DeclareTest, InitValue)
{
    tinyxml::Declare dec;
    EXPECT_EQ("null", dec.GetVersion());
    EXPECT_EQ("null", dec.GetEncoding());
}

TEST(DeclareTest, SetGetValue)
{
    tinyxml::Declare dec;
    dec.SetVersion("2.0");
    dec.SetEncoding("ISO-8859-1");
    EXPECT_EQ("2.0", dec.GetVersion());
    EXPECT_EQ("ISO-8859-1", dec.GetEncoding());
}
