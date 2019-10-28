#ifndef tinyxml_ATTRIBUTE_H
#define tinyxml_ATTRIBUTE_H

#include <xstring>

namespace tinyxml
{

    class Attribute
    {
    public:
        Attribute();
        Attribute(const std::string& name, const std::string& value);
        Attribute(const Attribute& attri);
        Attribute& operator=(const Attribute& attri);

        void SetName(const std::string& name);
        void SetValue(const std::string& value);
        const std::string& GetName() const;
        const std::string& GetValue() const;

        bool IsNull() const;

    private:
        std::string name_;
        std::string value_;
    };

}

#endif
