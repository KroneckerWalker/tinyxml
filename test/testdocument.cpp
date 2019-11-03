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

TEST(DocumentTest, Declare)
{
    tinyxml::Document doc;
    tinyxml::Declare dec = doc.GetDeclare();
    EXPECT_EQ("null", dec.GetVersion());
    EXPECT_EQ("null", dec.GetEncoding());
    EXPECT_EQ("null", dec.GetStandalone());

    doc.SetDeclare("1.0", "UTF-8", "yes");
    dec = doc.GetDeclare();
    EXPECT_EQ("1.0", dec.GetVersion());
    EXPECT_EQ("UTF-8", dec.GetEncoding());
    EXPECT_EQ("yes", dec.GetStandalone());
}

TEST(DocumentTest, Element)
{
    tinyxml::Document doc;
    tinyxml::Element ele = doc.GetElement();
    EXPECT_EQ("null", ele.GetTagName());

    doc.SetElementTagName("GamePlayer");
    ele = doc.GetElement();
    EXPECT_EQ("GamePlayer", ele.GetTagName());
}

TEST(DocumentTest, ElementFunctions)
{
    tinyxml::Document doc;
    int ret = doc.LoadContent(std::string(""));
    EXPECT_EQ(ret, tinyxml::ERROR_FileNameEmpty);

    ret = doc.LoadContent(std::string("game.xml"));
    EXPECT_EQ(tinyxml::SUCCESS, ret);
    ret = doc.DumpContent(std::string("gamedump.xml"));
    EXPECT_EQ(tinyxml::SUCCESS, ret);
}
