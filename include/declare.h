#ifndef tinyxml_DECLARE_H
#define tinyxml_DECLARE_H

#include "attribute.h"

namespace tinyxml
{

    class Declare
    {
    public:
        Declare();

    public:
        void SetVersion(const std::string& version);
        void SetEncoding(const std::string& encoding);
        void SetStandalone(const std::string& standalone);
        std::string GetVersion() const;
        std::string GetEncoding() const;
        std::string GetStandalone() const;

        void Clear();

    private:
        Attribute version_;
        Attribute encoding_;
        Attribute standalone_;
    };

}

#endif
