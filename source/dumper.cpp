#include "../include/error.h"

#include "dumper.h"


namespace tinyxml
{

    Dumper::Dumper(Element& elem, Declare& declare, std::ofstream& ofs) 
        : rootElement_(elem), declare_(declare), ofs_(ofs)
    {
    }

    int Dumper::Do()
    {
        int ret = SUCCESS;

        if (SUCCESS == ret)
        {
            ret = DumpDeclare();
        }

        if (SUCCESS == ret)
        {
            ret = DumpElement();
        }

        return ret;
    }

    int Dumper::DumpDeclare()
    {
        ofs_<<"<?xml";
        if (0 != declare_.GetVersion().compare("null"))
        {
            ofs_<<" version=\""<<declare_.GetVersion().c_str()<<"\"";
        }
        if (0 != declare_.GetEncoding().compare("null"))
        {
            ofs_<<" encoding=\""<<declare_.GetEncoding().c_str()<<"\"";
        }
        if (0 != declare_.GetStandalone().compare("null"))
        {
            ofs_<<" standalone=\""<<declare_.GetStandalone().c_str()<<"\"";
        }
        ofs_<<"?>"<<std::endl;
        return SUCCESS;
    }

    int Dumper::DumpElement()
    {
        return DumpChildElement(rootElement_, 0);
    }

    int Dumper::DumpChildElement(Element& elem, int rank)
    {
        std::list<Attribute>& attri = elem.GetAttributeList();
        std::list<Element>& child = elem.GetChildElementList();
        //This type element has a special dump style.
        bool hasAttriNoChild = (!attri.empty()) && (child.empty());

        //Dump Element Start
        for (int i = 0; i < rank; i++)
        {
            ofs_<<"\t";
        }
        ofs_<<"<"<<elem.GetTagName().c_str();

        //Dump Attributes
        if (!attri.empty())
        {
            for(std::list<Attribute>::iterator it = attri.begin(); it != attri.end(); ++it)
            {
                ofs_<<" "<<(*it).GetName().c_str()<<"=\""<<(*it).GetValue().c_str()<<"\"";
            }
        }
        if (hasAttriNoChild)
        {
            //This type of element end at here.
            ofs_<<"/";
        }
        ofs_<<">\n";

        //Dump Sub-elements
        if (!child.empty())
        {
            for(std::list<Element>::iterator it = child.begin(); it != child.end(); ++it)
            {
                DumpChildElement(*it, rank+1);
            }
        }

        //Dump Element End
        if (!hasAttriNoChild)
        {
            for (int i = 0; i < rank; i++)
            {
                ofs_<<"\t";
            }
            ofs_<<"</"<<elem.GetTagName().c_str()<<">"<<std::endl;
        }

        return SUCCESS;
    }

}
