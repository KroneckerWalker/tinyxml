#ifndef tinyxml_ELEMENT_H
#define tinyxml_ELEMENT_H

#include <xstring>
#include <list>
#include "attribute.h"

namespace tinyxml
{

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
        bool HasAttribute(const std::string& name) const;
        void RemoveAttribute(const std::string& name);
        void Clear();

        //�����Զ���attribute���ӵ���ǰԪ�أ�
        //�����ǰԪ���Ѿ������Զ�����attributeͬ����ʹ��attribute�滻�������ر��滻�����Զ���
        //���򷵻ؿ����Զ���
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
        Element& GetFirstChildElement();
        Element& GetLastChildElement();
        Element& GetNextSiblingElement();
        Element& GetPreviousSiblingElement();
        Element& GetParentElement();
        std::list<Element>& GetChildElementList();

        void AppendChildElement(const Element& element);
        void RemoveChildElement(const Element& element);

        void AppendNullElement();
        void RemoveLastElement();

    private:
        std::string name_;
        std::list<Attribute> attri_;
        std::list<Element> child_;

        Element* parent_;
        Element* previous_;
        Element* next_;
    };

}

#endif

