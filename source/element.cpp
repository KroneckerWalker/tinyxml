#include "../include/element.h"


namespace tinyxml
{

Element::Element() : name_("null")
{
    parent_ = NULL;
    previous_ = NULL;
    next_ = NULL;
}

Element::Element(const std::string& name) : name_(name)
{
    parent_ = NULL;
    previous_ = NULL;
    next_ = NULL;
}

Element::Element(const Element& element) : name_(element.name_)
{
    parent_ = element.parent_;
    previous_ = element.previous_;
    next_ = element.next_;
}

Element& Element::operator=(const Element& element)
{
    name_ = element.name_;
    parent_ = element.parent_;
    previous_ = element.previous_;
    next_ = element.next_;
    return *this;
}

bool Element::operator==(const Element& element) const
{
    //这里只是简化判断，只判断指针
    //正确的做法是整个内容判断一致性，不过效率会很低
    //以后考虑使用UUID标记Element，就只需要判断UUID
    if (parent_ == element.parent_
        && previous_ == element.previous_
        && next_ == element.next_)
    {
        return true;
    }
    return false;
}

bool Element::HasAttribute(const std::string& name) const
{
    for (std::list<Attribute>::const_iterator it = attri_.begin(); it != attri_.end(); ++it)
    {
        if (0 == name.compare((*it).GetName()))
        {
            return true;
        }
    }
    return false;
}

void Element::RemoveAttribute(const std::string& name)
{
    //当前的这种做法并不高效，不过Remove指令不常用，所以暂时不考虑优化。
    //可以重载==运算符，只判断name是否一致，这样可以直接使用attri_.remove
    for (std::list<Attribute>::iterator it = attri_.begin(); it != attri_.end(); ++it)
    {
        if (0 == name.compare((*it).GetName()))
        {
            attri_.erase(it);
            return;
        }
    }
}

void Element::Clear()
{
    attri_.clear();
    child_.clear();
}

Attribute Element::SetAttributeNode(const Attribute& attribute)
{
    for (std::list<Attribute>::iterator it = attri_.begin(); it != attri_.end(); ++it)
    {
        if (0 == attribute.GetName().compare((*it).GetName()))
        {
            Attribute attri = *it;
            (*it).SetValue(attribute.GetValue());

            return attri;
        }
    }
    attri_.push_back(attribute);
    return Attribute();
}

Attribute Element::GetAttributeNode(const std::string& name)
{
    for (std::list<Attribute>::iterator it = attri_.begin(); it != attri_.end(); ++it)
    {
        if (0 == name.compare((*it).GetName()))
        {
            return (*it);
        }
    }
    return Attribute();
}

std::list<Attribute>& Element::GetAttributeList()
{
    return attri_;
}

void Element::SetAttribute(const std::string& name, const std::string& value)
{
    for (std::list<Attribute>::iterator it = attri_.begin(); it != attri_.end(); ++it)
    {
        if (0 == name.compare((*it).GetName()))
        {
            (*it).SetValue(value);
            return;
        }
    }
    attri_.push_back(Attribute(name, value));
}

std::string Element::GetAttribute(const std::string& name)
{
    for (std::list<Attribute>::iterator it = attri_.begin(); it != attri_.end(); ++it)
    {
        if (0 == name.compare((*it).GetName()))
        {
            return (*it).GetValue();
        }
    }
    return "";
}

void Element::SetTagName(const std::string& name)
{
    name_ = name;
}

std::string Element::GetTagName() const
{
    return name_;
}

bool Element::IsNull() const
{
    return (0 == name_.compare("null"));
}

Element nullElement;

Element& Element::GetFirstChildElement()
{
    if (child_.empty())
    {
        return nullElement;
    }
    return child_.front();
}

Element& Element::GetLastChildElement()
{
    if (child_.empty())
    {
        return nullElement;
    }
    return child_.back();
}

Element& Element::GetNextSiblingElement()
{
    if (next_ != NULL)
    {
        return *next_;
    }
    return nullElement;
}

Element& Element::GetPreviousSiblingElement()
{
    if (previous_ != NULL)
    {
        return *previous_;
    }
    return nullElement;
}

Element& Element::GetParentElement()
{
    if (parent_ != NULL)
    {
        return *parent_;
    }
    return nullElement;
}

std::list<Element>& Element::GetChildElementList()
{
    return child_;
}

void Element::AppendChildElement(const Element& element)
{
    if (child_.empty())
    {
        //插入队尾
        child_.push_back(element);
        //修复链表结点关系
        Element& ele = child_.back();
        ele.parent_ = this;
        ele.next_ = NULL;
        ele.previous_ = NULL;
    }
    else
    {
        //保存队尾元素
        Element& pre = child_.back();
        //插入队尾
        child_.push_back(element);
        //修复链表结点关系
        Element& ele = child_.back();
        ele.parent_ = this;
        ele.next_ = NULL;
        ele.previous_ = &pre;
        pre.next_ = &ele;
    }
}

void Element::RemoveChildElement(const Element& element)
{
    for (std::list<Element>::iterator it = child_.begin(); it != child_.end(); ++it)
    {
        if (element == *it)
        {
            //修复链表结点关系
            if (element.previous_ != NULL)
            {
                (element.previous_)->next_ = element.next_;
            }
            if (element.next_ != NULL)
            {
                (element.next_)->previous_ = element.previous_;
            }
            //移除当前结点
            child_.erase(it);
            break;
        }
    }
}

void Element::AppendNullElement()
{
    AppendChildElement(Element());
}

void Element::RemoveLastElement()
{
    if (!child_.empty())
    {
        child_.pop_back();
    }
    //修复链表结点关系
    if (!child_.empty())
    {
        Element& ele = child_.back();
        ele.next_ = NULL;
    }
}

}
