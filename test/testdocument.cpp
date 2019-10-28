#include "gtest/gtest.h"
#include "../include/tinyxml.h"

//#define DUMP

TEST(DocumentTest, ElementFunctions)
{
    tinyxml::Document doc;
    int ret = doc.LoadContent(std::string(""));
    EXPECT_EQ(ret, tinyxml::ERROR_FileNameEmpty);
#ifdef DUMP
    tinyxml::Declare& dec = doc.GetDeclear();
    dec.SetVersion("1.0");
    dec.SetEncoding("UTF-8");
    tinyxml::Element& ele = doc.GetElement();
    ele.SetTagName("GameProfile");
    ele.AppendChildElement(tinyxml::Element("Player"));
    tinyxml::Element& child1 = ele.GetLastChildElement();
    child1.SetAttribute(std::string("Name"), std::string("Nancy"));
    child1.SetAttribute(std::string("Gender"), std::string("Female"));
    child1.SetAttribute(std::string("Age"), std::string("23"));

    ele.AppendChildElement(tinyxml::Element("Player"));
    tinyxml::Element& child2 = ele.GetLastChildElement();
    child2.SetAttribute(std::string("Name"), std::string("Maria"));
    child2.SetAttribute(std::string("Gender"), std::string("Female"));
    child2.SetAttribute(std::string("Age"), std::string("12"));

    child2.AppendChildElement(tinyxml::Element("Hobby"));
    tinyxml::Element& child3 = child2.GetLastChildElement();
    child3.SetAttribute(std::string("Name"), std::string("Draw"));
    child3.SetAttribute(std::string("Period"), std::string("Weekly"));

    doc.DumpContent(std::string("game.xml"));
#else
    ret = doc.LoadContent(std::string("game.xml"));
    EXPECT_EQ(tinyxml::SUCCESS, ret);
    ret = doc.DumpContent(std::string("gamedump.xml"));
    EXPECT_EQ(tinyxml::SUCCESS, ret);
#endif
}
