#include "../include/attribute.h"


namespace tinyxml
{

Attribute::Attribute() : name_("null"), value_("null")
{
}

Attribute::Attribute(const std::string& name, const std::string& value) : name_(name), value_(value)
{
}

Attribute::Attribute(const Attribute& attri) : name_(attri.name_), value_(attri.value_)
{
}

Attribute& Attribute::operator=(const Attribute& attri)
{
    name_ = attri.name_;
    value_ = attri.value_;
    return *this;
}

void Attribute::SetName(const std::string& name)
{
    name_ = name;
}

void Attribute::SetValue(const std::string& value)
{
    value_ = value;
}

const std::string& Attribute::GetName() const
{
    return name_;
}

const std::string& Attribute::GetValue() const
{
    return value_;
}

bool Attribute::IsNull() const
{
    return (0 == name_.compare("null"));
}

}
