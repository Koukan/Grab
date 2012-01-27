/// BulletML のパーサ・ツリー by tinyxml
/**
 * tinyxmlによるBulletMLのパーサ
 */

#ifndef BULLETMLPARSER_TINYXML_H_
#define BULLETMLPARSER_TINYXML_H_

#include <string>

#include "bulletmlcommon.h"

#include "../tinyxml/tinyxml.h"

class BulletMLNode;

class BulletMLParserTinyXML : public BulletMLParser {
public:
    DECLSPEC BulletMLParserTinyXML(const std::string& filename);
    DECLSPEC BulletMLParserTinyXML(TiXmlNode* root,
								   const std::string& filename = "");
    DECLSPEC BulletMLParserTinyXML(FILE* fp,
								   const std::string& filename = "");
    DECLSPEC virtual ~BulletMLParserTinyXML();

    DECLSPEC virtual void parse();

private:
	void parseImpl(TiXmlDocument& doc);

protected:
    void getTree(TiXmlNode* node);
    void translateNode(TiXmlNode* node);

private:
	void init(std::string filename);
	enum { LOAD_FILE, LOAD_FP, LOAD_NODE } loadFrom_;
    std::string xmlFile_;
	FILE* fp_;
	TiXmlNode* root_;
    BulletMLNode* curNode_;
};

#endif // ! BULLETMLPARSER_TINYXML_H_
