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


#ifndef tinyxml_ELEMENT_H
#define tinyxml_ELEMENT_H

#include <string>
#include <list>
#include "attribute.h"

namespace tinyxml
{
    // Define a reference count smart pointer, to make this operation copy memory lightly:
    // Element ele = element.GetFirstChildElement();
    template<typename T>
    class ContentPtr
    {
    public:
        ContentPtr() : ptr_(new T()), count_(new int) { *count_ = 1; }
        ContentPtr(const ContentPtr& obj) : ptr_(obj.ptr_), count_(obj.count_) { *count_ += 1; }
        ContentPtr& operator=(const ContentPtr& obj)
        {
            Derefrence();
            ptr_ = obj.ptr_;
            count_ = obj.count_;
            *count_ += 1;
            return *this;
        }
        ~ContentPtr() { Derefrence(); }
        T* operator->() { return ptr_; }
        T& operator*() {return *ptr_; }
    private:
        void Derefrence()
        {
            *count_ -= 1;
            if (0 == *count_)
            {
                delete ptr_;
                delete count_;
            }        
        }
    private:
        T* ptr_;
        int* count_;
    };


    class Element
    {
    public:
        Element();
        Element(const std::string& name);
        Element(const Element& element);
        Element& operator=(const Element& element);
        bool operator==(const Element& element) const;

    public:
        //----Attribute----
        bool HasAttribute(const std::string& name);
        void RemoveAttribute(const std::string& name);
        void Clear();

        //把属性对象attribute增加到当前元素；
        //如果当前元素已经有属性对象与attribute同名，使用attribute替换，并返回被替换的属性对象；
        //否则返回空属性对象。
        Attribute SetAttributeNode(const Attribute& attribute);
        Attribute GetAttributeNode(const std::string& name);
        std::list<Attribute>& GetAttributeList();

        void SetAttribute(const std::string& name, const std::string& value);
        std::string GetAttribute(const std::string& name);

        //----TagName----
        void SetTagName(const std::string& name);
        std::string GetTagName() const;
        bool IsNull() const;

        //----Element----
        Element GetFirstChildElement();
        Element GetLastChildElement();
        Element GetNextSiblingElement();
        Element GetPreviousSiblingElement();
        Element GetParentElement();
        std::list<Element>& GetChildElementList();

        void AppendChildElement(const Element& element);
        void RemoveChildElement(const Element& element);

    private:
        std::string name_;
        ContentPtr< std::list<Attribute> > attri_;
        ContentPtr< std::list<Element> > child_;

        Element* parent_;
        Element* previous_;
        Element* next_;
    };

}

#endif

