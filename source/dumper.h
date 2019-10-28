#ifndef tinyxml_DUMPER_H
#define tinyxml_DUMPER_H

#include "../include/element.h"
#include "../include/declare.h"

#include <fstream>


namespace tinyxml
{

    class Dumper
    {
    public:
        Dumper(Element& elem, Declare& declare, std::ofstream& ofs);

    public:
        int Do();

    private:
        int DumpDeclare();
        int DumpElement();
        int DumpChildElement(Element& elem, int rank);

    private:
        Element& rootElement_;
        Declare& declare_;
        std::ofstream& ofs_;
    };

}

#endif
