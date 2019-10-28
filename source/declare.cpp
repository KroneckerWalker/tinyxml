#include "../include/declare.h"


namespace tinyxml
{

Declare::Declare() 
: version_(std::string("version"), std::string("null")),
  encoding_(std::string("encoding"), std::string("null")),
  standalone_(std::string("standalone"), std::string("null"))
{
}

void Declare::SetVersion(const std::string& version)
{
    version_.SetValue(version);
}

void Declare::SetEncoding(const std::string& encoding)
{
    encoding_.SetValue(encoding);
}

void Declare::SetStandalone(const std::string& standalone)
{
    standalone_.SetValue(standalone);
}

std::string Declare::GetVersion() const
{
    return version_.GetValue();
}

std::string Declare::GetEncoding() const
{
    return encoding_.GetValue();
}

std::string Declare::GetStandalone() const
{
    return standalone_.GetValue();
}

void Declare::Clear()
{
    version_.SetValue(std::string("null"));
    encoding_.SetValue(std::string("null"));
    standalone_.SetValue(std::string("null"));
}

}
