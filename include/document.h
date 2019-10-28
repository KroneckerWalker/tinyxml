#ifndef tinyxml_DOCUMENT_H
#define tinyxml_DOCUMENT_H

#include <xstring>
#include "declare.h"
#include "element.h"

namespace tinyxml
{

    class Document
    {
    public:
        int LoadContent(std::string &file);
        int DumpContent(std::string &file);
        int ClearContent();

        Declare& GetDeclear();
        Element& GetElement();

    private:
        Element element_;
        Declare declare_;
    };

}

#endif
