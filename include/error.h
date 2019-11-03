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


#ifndef tinyxml_ERROR_H
#define tinyxml_ERROR_H

namespace tinyxml
{
    static const int SUCCESS = 0;
    static const int ERROR_FileNameEmpty     = 10000;
    static const int ERROR_FileNotOpen       = 10001;
    static const int ERROR_CommentStart      = 10002;
    static const int ERROR_CommentEnd        = 10003;
    static const int ERROR_StartCharactor    = 10004;
    static const int ERROR_NotFoundDeclear   = 10005;
    static const int ERROR_DeclearTagName    = 10006;
    static const int ERROR_DeclearEnd        = 10007;
    static const int ERROR_AttributeName     = 10008;
    static const int ERROR_AttributeValue    = 10009;
    static const int ERROR_ElementTagName    = 10010;
    static const int ERROR_ElementEnd        = 10011;
}

#endif
