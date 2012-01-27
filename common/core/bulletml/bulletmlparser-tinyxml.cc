#include "bulletmlparser.h"
#include "bulletmlparser-tinyxml.h"
#include "bulletmlerror.h"
#include "bulletmltree.h"
#include <iostream>
#include <string>

BulletMLParserTinyXML::BulletMLParserTinyXML(const std::string& filename)
	: loadFrom_(LOAD_FILE)
{
	init(filename);
}

BulletMLParserTinyXML::BulletMLParserTinyXML(TiXmlNode* root,
											 const std::string& filename)
	: loadFrom_(LOAD_NODE), root_(root)
{
	init(filename);
}

BulletMLParserTinyXML::BulletMLParserTinyXML(FILE* fp,
											 const std::string& filename)
	: loadFrom_(LOAD_FP), fp_(fp)
{
	init(filename);
}

void BulletMLParserTinyXML::init(std::string filename) {
	xmlFile_ = filename;
	setName(filename);
	curNode_ = 0;
}

BulletMLParserTinyXML::~BulletMLParserTinyXML() {}

void BulletMLParserTinyXML::getTree(TiXmlNode* node) {
	if (node->ToComment() != 0) return;
    translateNode(node);

    TiXmlNode* child;
    for (child = node->FirstChild(); child; child = child->NextSibling()) {
		TiXmlText* text;
		if ((text = child->ToText()) != 0) {
			curNode_->setValue(text->Value());
			break;
		}

		getTree(child);
    }

    curNode_ = curNode_->getParent();
}

void BulletMLParserTinyXML::translateNode(TiXmlNode* node) {
    TiXmlElement* elem = node->ToElement();
    assert(elem != 0);

    BulletMLNode* xmlNode = addContent(elem->Value());

	if (xmlNode->getName() == BulletMLNode::bulletml) {
		TiXmlAttribute* attr;
		for (attr = elem->FirstAttribute(); attr; attr = attr->Next()) {
			if (attr->Value() == "horizontal") setHorizontal();
		}
	}
	else {
		MyAttributes mattr;
		TiXmlAttribute* attr;
		for (attr = elem->FirstAttribute(); attr; attr = attr->Next()) {
			mattr.push_back(attr->Name());
			mattr.push_back(attr->Value());
		}
		addAttribute(mattr, xmlNode);
		if (curNode_ != 0) curNode_->addChild(xmlNode);
	}
	curNode_ = xmlNode;
}

void BulletMLParserTinyXML::parseImpl(TiXmlDocument& doc) {
	if (doc.Error()) {
		throw BulletMLError(doc.Value() + ": " + doc.ErrorDesc());
	}

    TiXmlNode* node;
    for (node = doc.FirstChild(); node; node = node->NextSibling()) {
		if (node->ToElement() != 0) {
			getTree(node);
			break;
		}
    }
}

void BulletMLParserTinyXML::parse() {
	if (loadFrom_ == LOAD_FILE) {
		TiXmlDocument doc(xmlFile_.c_str());
		doc.LoadFile();
		parseImpl(doc);
	}
	else if (loadFrom_ == LOAD_FP) {
		TiXmlDocument doc(xmlFile_.c_str());
		doc.LoadFile(fp_);
		parseImpl(doc);
	}
	else {
		getTree(root_);
	}
}


