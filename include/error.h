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
