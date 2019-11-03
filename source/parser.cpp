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

#include "parser.h"


namespace tinyxml
{

Parser::Parser(Element& elem, Declare& declare, std::ifstream& ifs) 
: rootElement_(elem), declare_(declare), ifs_(ifs)
{
    line_ = 0;
}

int Parser::Do()
{
    int ret = SUCCESS;

    if (SUCCESS == ret)
    {
        ret = ParseDeclare();
    }

    if (SUCCESS == ret)
    {
        ret = ParseElement(rootElement_, std::string(""));
    }

    return ret;
}


enum NameChar { NameBeginning, NameNotBeginning, NotName };

static const char Begi = (char)NameBeginning;
static const char NtBg = (char)NameNotBeginning;
static const char NotN = (char)NotName;

static const char nameCharTable[128] =
{
    NotN, NotN, NotN, NotN, NotN, NotN, NotN, NotN,
    NotN, NotN, NotN, NotN, NotN, NotN, NotN, NotN,
    NotN, NotN, NotN, NotN, NotN, NotN, NotN, NotN,
    NotN, NotN, NotN, NotN, NotN, NotN, NotN, NotN,
    //    !     "     #     $     %     &     '
    NotN, NotN, NotN, NotN, NotN, NotN, NotN, NotN,
    //(   )     *     +     ,     -     .     /
    NotN, NotN, NotN, NotN, NotN, NtBg, NtBg, NotN,
    //0   1     2     3     4     5     6     7
    NtBg, NtBg, NtBg, NtBg, NtBg, NtBg, NtBg, NtBg,
    //8   9     :     ;     <     =     >     ?
    NtBg, NtBg, Begi, NotN, NotN, NotN, NotN, NotN,
    //@   A     B     C     D     E     F     G
    NotN, Begi, Begi, Begi, Begi, Begi, Begi, Begi,
    //H   I     J     K     L     M     N     O
    Begi, Begi, Begi, Begi, Begi, Begi, Begi, Begi,
    //P   Q     R     S     T     U     V     W
    Begi, Begi, Begi, Begi, Begi, Begi, Begi, Begi,
    //X   Y     Z     [     \     ]     ^     _
    Begi, Begi, Begi, NotN, NotN, NotN, NotN, Begi,
    //`   a     b     c     d     e     f     g
    NotN, Begi, Begi, Begi, Begi, Begi, Begi, Begi,
    //h   i     j     k     l     m     n     o
    Begi, Begi, Begi, Begi, Begi, Begi, Begi, Begi,
    //p   q     r     s     t     u     v     w
    Begi, Begi, Begi, Begi, Begi, Begi, Begi, Begi,
    //x   y     z     {     |     }     ~     
    Begi, Begi, Begi, NotN, NotN, NotN, NotN, NotN
};

static inline NameChar DetermineNameChar(char ch)
{
    return (NameChar)nameCharTable[ch & 0x7f];
}

static inline bool IsSpaceChar(char ch)
{
    return (' ' == ch || '\t' == ch || '\r' == ch || '\n' == ch);
}

int Parser::ParseDeclare()
{
    const char Init        = 0;
    const char LessThan    = 1; // Read '<'
    const char ExcMark     = 2; // Read '!', Already "<!"
    const char Comment     = 3; // Read '-', Already "<!-"
    const char CommentR    = 4; // Read '-', Already "<!--"
    const char DeclareS    = 5; // Read '?', Already "<?"
    const char ReadTag     = 6; // Read NameBeginning
    const char TagEnd      = 7; // Read ' ' or '?'
    const char AttriEnd    = 8; // 
    const char DeclareE    = 9; // Read '?'
    const char Done        = 10;// Read '>', Already "?>"

    const char InputWs     = 0;
    const char InputLt     = 1;
    const char InputEm     = 2;
    const char InputQm     = 3;
    const char InputDash   = 4;
    const char InputName   = 5;
    const char InputEq     = 6;
    const char InputBt     = 7;
    const char InputOther  = 8;

    static const char table[Done][InputOther+1] = 
    {
    //   InputWs    InputLt    InputEm    InputQm    InputDash  InputName  InputEq    InputBt  InputOther
        {Init,      LessThan,  -1,        -1,        -1,        -1,        -1,        -1,      -1 }, // Init
        {-1,        -1,        ExcMark,   DeclareS,  -1,        -1,        -1,        -1,      -1 }, // LessThan
        {-1,        -1,        -1,        -1,        Comment,   -1,        -1,        -1,      -1 }, // ExcMark
        {-1,        -1,        -1,        -1,        CommentR,  -1,        -1,        -1,      -1 }, // Comment
        {-1,        -1,        -1,        -1,        -1,        -1,        -1,        -1,      -1 }, // CommentR
        {-1,        -1,        -1,        -1,        -1,        ReadTag,   -1,        -1,      -1 }, // DeclareS
        {TagEnd,    -1,        -1,        TagEnd,    -1,        ReadTag,   -1,        -1,      -1 }, // ReadName
        {TagEnd,    -1,        -1,        DeclareE,  -1,        -1,        -1,        -1,      -1 }, // TagEnd
        {AttriEnd,  -1,        -1,        DeclareE,  -1,        -1,        -1,        -1,      -1 }, // AttriEnd
        {-1,        -1,        -1,        -1,        -1,        -1,        -1,        Done,    -1 }  // DeclareE
    };

    static const int error[Done] = 
    {
        ERROR_StartCharactor,    // Init
        ERROR_NotFoundDeclear,   // LessThan
        ERROR_CommentStart,      // ExcMark
        ERROR_CommentStart,      // Comment
        SUCCESS,                 // CommentR
        ERROR_DeclearTagName,    // DeclareS
        ERROR_DeclearTagName,    // ReadTag
        SUCCESS,                 // TagEnd
        SUCCESS,                 // AttriEnd
        ERROR_DeclearEnd,        // DeclareE
    };

    char preState = Init;
    char state = Init;
    char input;
    char ch;

    std::string tag;

    for (;;)
    {
        ifs_ >> ch;
        CountLines(ch);

        if (IsSpaceChar(ch))
        {
            input = InputWs;
        }
        else if ('<' == ch)
        {
            input = InputLt;
        }
        else if ('!' == ch)
        {
            input = InputEm;
        }
        else if ('?' == ch)
        {
            input = InputQm;
        }
        else if ('-' == ch)
        {
            input = InputDash;
        }
        else if (NameBeginning == DetermineNameChar(ch))
        {
            input = InputName;
        }
        else if('=' == ch)
        {
            input = InputEq;
        }
        else if ('>' == ch)
        {
            input = InputBt;
        }
        else
        {
            input = InputOther;
        }

        preState = state;
        state = table[state][input];

        switch (state)
        {
        case CommentR:
            {
                int ret = ParseComment();
                if (ret != SUCCESS)
                {
                    return ret;
                }
                state = Init;
            }
            break;
        case ReadTag:
            tag += ch;

            ch = ifs_.peek();
            if ('?' == ch || IsSpaceChar(ch))
            {
                if (0 != tag.compare("xml"))
                {
                    return ERROR_DeclearTagName;
                }
                state = TagEnd;
            }
            break;
        case TagEnd:
            for (;;)
            {
                std::string name;
                std::string value;
                int ret;

                ret = ParseAttributeName(name);
                if (SUCCESS == ret)
                {
                    if (0 == name.compare("version"))
                    {
                        ret = ParseAttributeValue(value);
                        if (SUCCESS == ret)
                        {
                            declare_.SetVersion(value);
                        }
                    }
                    else if (0 == name.compare("encoding"))
                    {
                        ret = ParseAttributeValue(value);
                        if (SUCCESS == ret)
                        {
                            declare_.SetEncoding(value);
                        }
                    }
                    else if (0 == name.compare("standalone"))
                    {
                        ret = ParseAttributeValue(value);
                        if (SUCCESS == ret)
                        {
                            declare_.SetStandalone(value);
                        }
                    }
                    else if (name.empty())
                    {
                        break;
                    }
                    else
                    {
                        return ERROR_AttributeName;
                    }
                }

                if (SUCCESS != ret)
                {
                    return ret;
                }
            }
            state = AttriEnd;
            break;
        case -1:
            return error[preState];
        case Done:
            return SUCCESS;
        default:
            break;
        }
    }

    return SUCCESS;
}

int Parser::ParseElement(Element& element, const std::string& parentTag)
{
    const char Init        = 0;
    const char LessThan    = 1; // Read '<'
    const char ExcMark     = 2; // Read '!', Already "<!"
    const char Comment     = 3; // Read '-', Already "<!-"
    const char CommentR    = 4; // Read '-', Already "<!--"
    const char ReadTag     = 5; // Read NameBeginning
    const char TagEnd      = 6; // Read ' ' or '>'(ElemEmbed) or '/'(ElemEnd)
    const char ElemEmbed   = 7; // Read '>'
    const char ElemEnd     = 8; // Read '/', Wait for "/>" to Done
    const char ElemPair    = 9; // Read '/', Already "</"
    const char ReadEndTag  = 10;// Read NameBeginning
    const char EndTagEnd   = 11;// Read '>', Already "</Name>"
    const char Done        = 12;

    const char InputWs     = 0;
    const char InputLt     = 1;
    const char InputEm     = 2;
    const char InputDash   = 3;
    const char InputNb     = 4;     // Name Beginning
    const char InputNc     = 5;     // Name not beginning (Name charactor)
    const char InputBt     = 6;
    const char InputSplash = 7;
    const char InputOther  = 8;

    static const char table[Done][InputOther+1] = 
    {
    //   InputWs    InputLt    InputEm    InputDash  InputNb     InputNc     InputBt     InputSplash InputOther
        {Init,      LessThan,  -1,        -1,        -1,         -1,         -1,         -1,         -1 }, // Init
        {-1,        -1,        ExcMark,   -1,        ReadTag,    -1,         -1,         ElemPair,   -1 }, // LessThan
        {-1,        -1,        -1,        Comment,   -1,         -1,         -1,         -1,         -1 }, // ExcMark
        {-1,        -1,        -1,        CommentR,  -1,         -1,         -1,         -1,         -1 }, // Comment
        {-1,        -1,        -1,        -1,        -1,         -1,         -1,         -1,         -1 }, // CommentR
        {TagEnd,    -1,        -1,        -1,        ReadTag,    ReadTag,    TagEnd,     TagEnd,     -1 }, // ReadTag
        {TagEnd,    -1,        -1,        -1,        -1,         -1,         ElemEmbed,  ElemEnd,    -1 }, // TagEnd
        {-1,        -1,        -1,        -1,        -1,         -1,         -1,         -1,         -1 }, // ElemEmbed
        {-1,        -1,        -1,        -1,        -1,         -1,         Done,       -1,         -1 }, // ElemEnd
        {-1,        -1,        -1,        -1,        ReadEndTag, -1,         -1,         -1,         -1 }, // ElemPair
        {EndTagEnd, -1,        -1,        -1,        ReadEndTag, ReadEndTag, EndTagEnd,  -1,         -1 }, // ReadEndTag
        {-1,        -1,        -1,        -1,        -1,         -1,         Done,       -1,         -1 }  // EndTagEnd
    };

    static const int error[Done] = 
    {
        ERROR_StartCharactor,    // Init
        ERROR_NotFoundDeclear,   // LessThan
        ERROR_CommentStart,      // ExcMark
        ERROR_CommentStart,      // Comment
        SUCCESS,                 // CommentR
        ERROR_ElementTagName,    // ReadTag
        SUCCESS,                 // TagEnd
        SUCCESS,                 // ElemEmbed
        ERROR_ElementEnd,        // ElemEnd
        ERROR_ElementEnd,        // ElemPair
        ERROR_ElementEnd,        // ReadEndTag
        ERROR_ElementEnd,        // EndTagEnd
    };

    char preState = Init;
    char state = Init;
    char input;
    char ch;

    std::string tag;
    std::string endtag;

    for (;;)
    {
        ifs_ >> ch;
        CountLines(ch);

        if (IsSpaceChar(ch))
        {
            input = InputWs;
        }
        else if ('<' == ch)
        {
            input = InputLt;
        }
        else if ('!' == ch)
        {
            input = InputEm;
        }
        else if ('-' == ch)
        {
            input = InputDash;
        }
        else if (NameBeginning == DetermineNameChar(ch))
        {
            input = InputNb;
        }
        else if (NameNotBeginning == DetermineNameChar(ch))
        {
            input = InputNc;
        }
        else if ('>' == ch)
        {
            input = InputBt;
        }
        else if('/' == ch)
        {
            input = InputSplash;
        }
        else
        {
            input = InputOther;
        }

        preState = state;
        state = table[state][input];

        switch (state)
        {
        case CommentR:
            {
                int ret = ParseComment();
                if (ret != SUCCESS)
                {
                    return ret;
                }
                state = Init;
            }
            break;
        case ReadTag:
            tag += ch;

            ch = ifs_.peek();
            if ('/' == ch || '>' == ch || IsSpaceChar(ch))
            {
                element.SetTagName(tag);
                state = TagEnd;
            }
            break;
        case TagEnd:
            for (;;)
            {
                Attribute attri;
                int ret = ParseAttribute(attri);
                if (SUCCESS == ret)
                {
                    if (!attri.IsNull())
                    {
                        element.SetAttributeNode(attri);
                        break;
                    }
                }
                else
                {
                    return ret;
                }
            }
            break;
        case ElemEmbed:
            for (;;)
            {
                Element elem;
                int ret = ParseElement(elem, element.GetTagName());
                if (SUCCESS == ret)
                {
                    // 没有解析到子Element
                    if (elem.IsNull())
                    {
                        return SUCCESS;
                    }
                    else
                    {
                        element.AppendChildElement(elem);
                    }
                }
                else
                {
                    return ret;
                }
            }
            break;
        case ReadEndTag:
            endtag += ch;

            ch = ifs_.peek();
            if ('>' == ch || IsSpaceChar(ch))
            {
                if (0 != endtag.compare(parentTag))
                {
                    return ERROR_ElementEnd;
                }
                state = EndTagEnd;
            }
            break;
        case -1:
            return error[preState];
        case Done:
            return SUCCESS;
        default:
            break;
        }
    }

    return SUCCESS;
}

int Parser::ParseAttribute(Attribute& attribute)
{
    int ret = SUCCESS;
    std::string name;
    std::string value;

    ret = ParseAttributeName(name);
    if (SUCCESS == ret && !name.empty())
    {
        ret = ParseAttributeValue(value);
        if (SUCCESS == ret)
        {
            attribute.SetName(name);
            attribute.SetValue(value);
        }
    }
    return ret;
}

int Parser::ParseComment()
{
    const char Init        = 0;
    const char Comment     = 1; // Read '-', Already "<!-"
    const char CommentR    = 2; // Read '-', Already "--"
    const char Done        = 3; // Read '>', Already "-->"

    const char InputDash   = 0;
    const char InputBt     = 1;
    const char InputOther  = 2;

    static const char table[Done][InputOther+1] = 
    {
    //   InputDash  InputBt    InputOther
        {Comment,   -1,        Init      }, // Init
        {CommentR,  -1,        -1        }, // Comment
        {-1,        Done,      -1        }  // CommentR
    };

    char state = Init;
    char input;
    char ch;

    for (;;)
    {
        ifs_ >> ch;
        CountLines(ch);

        if ('-' == ch)
        {
            input = InputDash;
        }
        else if ('>' == ch)
        {
            input = InputBt;
        }
        else
        {
            input = InputOther;
        }

        state = table[state][input];

        if (-1 == state)
        {
            return ERROR_CommentEnd;
        }
        // 注释里的所有字符全都抛弃掉
        if (Done == state)
        {
            break;
        }
    }

    return SUCCESS;
}

int Parser::ParseAttributeName(std::string& name)
{
    const char Init       = 0;
    const char ReadName   = 1;    // Read Name
    const char Done       = 2;

    const char InputWs    = 0;     // White space
    const char InputNb    = 1;     // Name Beginning
    const char InputNc    = 2;     // Name not beginning
    const char InputOther = 3;

    static const char table[Done][InputOther+1] = 
    {
    //   InputWs    InputNb    InputNc    InputOther
        {Init,      ReadName,  -1,        -1    }, // Init
        {Done,      ReadName,  ReadName,  -1    }  // ReadName
    };

    char state = Init;
    char input;
    char ch;

    for (;;)
    {
        // 循环读取Attribute时，可能因为是结束而需要退出
        ch = ifs_.peek();
        if ('?' == ch || '>' == ch || '/' == ch)
        {
            return SUCCESS;
        }

        ifs_ >> ch;
        CountLines(ch);

        if (NameBeginning == DetermineNameChar(ch))
        {
            input = InputNb;
        }
        else if (NameNotBeginning == DetermineNameChar(ch))
        {
            input = InputNc;
        }
        else if (IsSpaceChar(ch))
        {
            input = InputWs;
        }
        else
        {
            input = InputOther;
        }

        state = table[state][input];

        switch (state)
        {
        case -1:
            return ERROR_AttributeName;
        case ReadName:
            name += ch;

            ch = ifs_.peek();
            if ('=' == ch)
            {
                return SUCCESS;
            }
            break;
        case Done:
            return SUCCESS;
        default:
            break;
        }
    }

    return SUCCESS;
}

int Parser::ParseAttributeValue(std::string& value)
{
    const char Init       = 0;
    const char ReadEq     = 1;    // Read '='
    const char ReadDq     = 2;    // Read '"' start
    const char DqCh       = 3;    // Read value in double quotes
    const char ReadSq     = 4;    // Read ''' start
    const char SqCh       = 5;    // Read value in single quotes
    const char Done       = 6;

    const char InputWs    = 0;     // White space
    const char InputEq    = 1;     // '='
    const char InputDq    = 2;
    const char InputSq    = 3;
    const char InputOther = 4;

    static const char table[Done][InputOther+1] = 
    {
    //   InputWs    InputEq    InputDq    InputSq    InputOther
        {Init,      ReadEq,    -1,        -1,        -1     }, // Init
        {ReadEq,    -1,        ReadDq,    ReadSq,    -1     }, // ReadEq
        {DqCh,      DqCh,      Done,      DqCh,      DqCh   }, // ReadDq
        {DqCh,      DqCh,      Done,      DqCh,      DqCh   }, // DqCh
        {ReadSq,    ReadSq,    ReadSq,    -1,        ReadSq }, // ReadSq
        {-1,        -1,        -1,        Done,      -1     }  // SqCh
    };

    char state = Init;
    char input;
    char ch;

    for (;;)
    {
        ifs_ >> ch;
        CountLines(ch);

        if (IsSpaceChar(ch))
        {
            input = InputWs;
        }
        else if ('=' == ch)
        {
            input = InputEq;
        }
        else if ('"' == ch)
        {
            input = InputDq;
        }
        else if ('\'' == ch)
        {
            input = InputSq;
        }
        else
        {
            input = InputOther;
        }

        state = table[state][input];

        switch (state)
        {
        case -1:
            return ERROR_AttributeValue;
        case DqCh:
            value += ch;
            break;
        case SqCh:
            value = ch;
            break;
        case Done:
            return SUCCESS;
        default:
            break;
        }

        if (Done == state)
        {
            break;
        }
    }

    return SUCCESS;
}

void Parser::CountLines(char ch)
{
    if ('\n' == ch)
    {
        line_++;
    }
}

}
