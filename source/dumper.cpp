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
            ofs_<<" version=\""<<declare_.GetVersion()<<"\"";
        }
        if (0 != declare_.GetEncoding().compare("null"))
        {
            ofs_<<" encoding=\""<<declare_.GetEncoding()<<"\"";
        }
        if (0 != declare_.GetStandalone().compare("null"))
        {
            ofs_<<" standalone=\""<<declare_.GetStandalone()<<"\"";
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
        ofs_<<"<"<<elem.GetTagName();

        //Dump Attributes
        if (!attri.empty())
        {
            for(std::list<Attribute>::iterator it = attri.begin(); it != attri.end(); ++it)
            {
                ofs_<<" "<<(*it).GetName()<<"=\""<<(*it).GetValue()<<"\"";
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
            ofs_<<"</"<<elem.GetTagName()<<">"<<std::endl;
        }

        return SUCCESS;
    }

}
