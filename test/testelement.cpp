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


TEST(ElementTest, InitValue)
{
    tinyxml::Element ele1;
    EXPECT_EQ("null", ele1.GetTagName());

    tinyxml::Element ele2("SoundProfile");
    EXPECT_EQ("SoundProfile", ele2.GetTagName());

    tinyxml::Element ele3(ele2);
    EXPECT_EQ("SoundProfile", ele3.GetTagName());

    ele1 = ele2;
    EXPECT_EQ("SoundProfile", ele1.GetTagName());

    ele1.SetTagName("Sound");
    EXPECT_EQ("Sound", ele1.GetTagName());
}

TEST(ElementTest, AttributeFunctions)
{
    tinyxml::Element ele("Test");
    ele.SetAttributeNode(tinyxml::Attribute("Name","Mike"));
    ele.SetAttributeNode(tinyxml::Attribute("Gender","Male"));
    ele.SetAttributeNode(tinyxml::Attribute("Age","23"));

    EXPECT_TRUE(ele.HasAttribute("Name"));
    EXPECT_TRUE(ele.HasAttribute("Gender"));
    EXPECT_TRUE(ele.HasAttribute("Age"));
    EXPECT_FALSE(ele.HasAttribute("Hobby"));

    tinyxml::Attribute attri;

    attri = ele.GetAttributeNode("Name");
    EXPECT_EQ("Name", attri.GetName());
    EXPECT_EQ("Mike", attri.GetValue());

    attri = ele.GetAttributeNode("Gender");
    EXPECT_EQ("Gender", attri.GetName());
    EXPECT_EQ("Male", attri.GetValue());

    attri = ele.GetAttributeNode("Age");
    EXPECT_EQ("Age", attri.GetName());
    EXPECT_EQ("23", attri.GetValue());

    attri = ele.GetAttributeNode("Hobby");
    EXPECT_EQ("null", attri.GetName());
    EXPECT_EQ("null", attri.GetValue());

    ele.SetAttribute("Name", "Nancy");
    ele.SetAttribute("Gender", "Female");
    ele.SetAttribute("Age", "18");
    EXPECT_EQ("Nancy", ele.GetAttribute("Name"));
    EXPECT_EQ("Female", ele.GetAttribute("Gender"));
    EXPECT_EQ("18", ele.GetAttribute("Age"));
    EXPECT_EQ("", ele.GetAttribute("Hobby"));


    ele.RemoveAttribute("Gender");
    EXPECT_TRUE(ele.HasAttribute("Name"));
    EXPECT_FALSE(ele.HasAttribute("Gender"));
    EXPECT_TRUE(ele.HasAttribute("Age"));

    ele.RemoveAttribute("Age");
    EXPECT_TRUE(ele.HasAttribute("Name"));
    EXPECT_FALSE(ele.HasAttribute("Gender"));
    EXPECT_FALSE(ele.HasAttribute("Age"));

    ele.RemoveAttribute("Name");
    EXPECT_FALSE(ele.HasAttribute("Name"));
    EXPECT_FALSE(ele.HasAttribute("Gender"));
    EXPECT_FALSE(ele.HasAttribute("Age"));
}

TEST(ElementTest, ElementFunctions)
{
    tinyxml::Element ele("Test");

    ele.AppendChildElement(tinyxml::Element("Player"));
    ele.AppendChildElement(tinyxml::Element("NPC"));
    ele.AppendChildElement(tinyxml::Element("RPG"));

    tinyxml::Element e1 = ele.GetFirstChildElement();
    EXPECT_EQ("Player", e1.GetTagName());
    tinyxml::Element e2 = ele.GetLastChildElement();
    EXPECT_EQ("RPG", e2.GetTagName());

    tinyxml::Element e3 = e1.GetParentElement();
    EXPECT_EQ("Test", e3.GetTagName());
    tinyxml::Element e4 = e2.GetParentElement();
    EXPECT_EQ("Test", e4.GetTagName());

    tinyxml::Element e5 = e1.GetPreviousSiblingElement();
    EXPECT_EQ("null", e5.GetTagName());
    tinyxml::Element e6 = e1.GetNextSiblingElement();
    EXPECT_EQ("NPC", e6.GetTagName());
    tinyxml::Element e7 = e2.GetPreviousSiblingElement();
    EXPECT_EQ("NPC", e7.GetTagName());
    tinyxml::Element e8 = e2.GetNextSiblingElement();
    EXPECT_EQ("null", e8.GetTagName());

    e1.AppendChildElement(tinyxml::Element("Mary"));
    e1.AppendChildElement(tinyxml::Element("Nancy"));
    e6.AppendChildElement(tinyxml::Element("Roge"));
    e6.AppendChildElement(tinyxml::Element("Akara"));
    e2.AppendChildElement(tinyxml::Element("Avatar"));
    e2.AppendChildElement(tinyxml::Element("Artemis"));

    ele.RemoveChildElement(e6);
    tinyxml::Element e9 = ele.GetFirstChildElement();
    EXPECT_EQ("Player", e9.GetTagName());
    tinyxml::Element ea = ele.GetLastChildElement();
    EXPECT_EQ("RPG", ea.GetTagName());
    tinyxml::Element eb = ea.GetPreviousSiblingElement();
    EXPECT_EQ("Player", eb.GetTagName());
    tinyxml::Element ec = e9.GetNextSiblingElement();
    EXPECT_EQ("RPG", ec.GetTagName());
}


class CC
{
public:
    CC(){c_++;}
    CC(CC& o){c_++;};
    CC& operator=(CC& o){c_++;}
    ~CC(){c_--;}
    int GetC(){return c_;}
private:
    static int c_;
};
int CC::c_ = 0;

TEST(ElementTest, ContentPtr)
{
    tinyxml::ContentPtr<CC> t0;
    EXPECT_EQ(1, t0->GetC());
    EXPECT_EQ(1, (*t0).GetC());

    {
        tinyxml::ContentPtr<CC> t1;
        EXPECT_EQ(2, t0->GetC());
        EXPECT_EQ(2, (*t0).GetC());
        EXPECT_EQ(2, t1->GetC());
        EXPECT_EQ(2, (*t1).GetC());

        {
            tinyxml::ContentPtr<CC> t2(t0);
            EXPECT_EQ(2, t0->GetC());
            EXPECT_EQ(2, (*t0).GetC());
            EXPECT_EQ(2, t1->GetC());
            EXPECT_EQ(2, (*t1).GetC());
            EXPECT_EQ(2, t2->GetC());
            EXPECT_EQ(2, (*t2).GetC());

            t2 = t1;
            EXPECT_EQ(2, t0->GetC());
            EXPECT_EQ(2, (*t0).GetC());
            EXPECT_EQ(2, t1->GetC());
            EXPECT_EQ(2, (*t1).GetC());
            EXPECT_EQ(2, t2->GetC());
            EXPECT_EQ(2, (*t2).GetC());

            {
                tinyxml::ContentPtr<CC> t3(t1);
                EXPECT_EQ(2, t0->GetC());
                EXPECT_EQ(2, (*t0).GetC());
                EXPECT_EQ(2, t1->GetC());
                EXPECT_EQ(2, (*t1).GetC());
                EXPECT_EQ(2, t2->GetC());
                EXPECT_EQ(2, (*t2).GetC());
                EXPECT_EQ(2, t3->GetC());
                EXPECT_EQ(2, (*t3).GetC());

                t3 = t0;
                EXPECT_EQ(2, t0->GetC());
                EXPECT_EQ(2, (*t0).GetC());
                EXPECT_EQ(2, t1->GetC());
                EXPECT_EQ(2, (*t1).GetC());
                EXPECT_EQ(2, t2->GetC());
                EXPECT_EQ(2, (*t2).GetC());
                EXPECT_EQ(2, t3->GetC());
                EXPECT_EQ(2, (*t3).GetC());
            }

            EXPECT_EQ(2, t0->GetC());
            EXPECT_EQ(2, (*t0).GetC());
            EXPECT_EQ(2, t1->GetC());
            EXPECT_EQ(2, (*t1).GetC());
            EXPECT_EQ(2, t2->GetC());
            EXPECT_EQ(2, (*t2).GetC());
        }

        EXPECT_EQ(2, t0->GetC());
        EXPECT_EQ(2, (*t0).GetC());
        EXPECT_EQ(2, t1->GetC());
        EXPECT_EQ(2, (*t1).GetC());
    }
    EXPECT_EQ(1, t0->GetC());
    EXPECT_EQ(1, (*t0).GetC());
}
