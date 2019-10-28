#include "../include/error.h"
#include "../include/document.h"

#include <fstream>

#include "parser.h"
#include "dumper.h"


namespace tinyxml
{

int Document::LoadContent(std::string &file)
{
    if (file.empty())
    {
        return ERROR_FileNameEmpty;
    }

    std::ifstream ifs(file.c_str());
    if (!ifs)
    {
        return ERROR_FileNotOpen;
    }
    ifs >> std::noskipws;

    ClearContent();

    Parser parser(element_, declare_, ifs);
    parser.Do();

    return SUCCESS;
}

int Document::DumpContent(std::string &file)
{
    if (file.empty())
    {
        return ERROR_FileNameEmpty;
    }

    std::ofstream ofs(file.c_str());
    if (!ofs)
    {
        return ERROR_FileNotOpen;
    }

    Dumper dumper(element_, declare_, ofs);
    dumper.Do();

    return SUCCESS;
}

int Document::ClearContent()
{
    declare_.Clear();
    element_.Clear();
    return SUCCESS;
}

Declare& Document::GetDeclear()
{
    return declare_;
}

Element& Document::GetElement()
{
    return element_;
}

}
