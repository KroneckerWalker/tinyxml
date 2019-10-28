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
