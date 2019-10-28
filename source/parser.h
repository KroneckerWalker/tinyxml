#ifndef tinyxml_PARSER_H
#define tinyxml_PARSER_H

#include "../include/element.h"
#include "../include/declare.h"

#include <xstring>
#include <fstream>


namespace tinyxml
{

    class Parser
    {
    public:
        Parser(Element& elem, Declare& declare, std::ifstream& ifs);

    public:
        int Do();

    private:
        int ParseDeclare();
        int ParseElement(Element& element);
        int ParseAttribute(Attribute& attribute);
        int ParseComment();

        int ParseAttributeName(std::string& name);
        int ParseAttributeValue(std::string& value);

        void CountLines(char ch);

    private:
        Element& rootElement_;
        Declare& declare_;
        std::ifstream& ifs_;
        int line_;
    };

}

#endif
