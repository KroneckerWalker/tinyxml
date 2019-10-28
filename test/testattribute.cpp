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
