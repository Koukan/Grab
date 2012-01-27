/// BulletMLツリー。
/**
 * BulletML に特化していて非常にいんちきくさいのが特徴。
 */

#ifndef BULLETMLTREE_H_
#define BULLETMLTREE_H_

#include <string>
#include <algorithm>
#include <memory>

#include <stdint.h>

#include <vector>

#include "tree.h"
#include "formula.h"
#include "bulletmlcommon.h"

class BulletMLNode : public TreeNode<BulletMLNode> {
public:
	typedef Formula<double> Number;
	typedef enum { none, aim, absolute, relative, sequence, typeSize } Type;
	typedef enum { bullet, action, fire, changeDirection, changeSpeed, accel,
				   wait, repeat, bulletRef, actionRef, fireRef, vanish,
				   horizontal, vertical, term, times, direction, speed, param,
				   bulletml, hitbox, simpleHitbox, nameSize} Name;

private:
	static Type string2type(const std::string& str);
	static Name string2name(const std::string& str);
	static std::string name2string[nameSize];

public:
    typedef TreeNode<BulletMLNode>::Children Children;
    typedef TreeNode<BulletMLNode>::ChildIterator ChildIterator;

public:
	DECLSPEC explicit BulletMLNode(const std::string& name);
    DECLSPEC virtual ~BulletMLNode();

    DECLSPEC Name getName() const { return name_; }

    DECLSPEC void setValue(const std::string& val);
    DECLSPEC double getValue() const { return val_->value(); }

	DECLSPEC void setType(const std::string& type) { type_ = string2type(type); }
	DECLSPEC Type getType() const { return type_; }

	DECLSPEC void setRefID(int id) { refID_ = id; }
	DECLSPEC int getRefID() const { return refID_; }

    DECLSPEC BulletMLNode* getChild(Name name);
/*

    template <class OutIte_>
    void getAllChildren(Name name, OutIte_ outIte);
*/
    DECLSPEC void getAllChildrenVec(Name name, std::vector<BulletMLNode*>& outvec);



    /// 子孫の中に指定した名前に一致するものがあるかどうか
    DECLSPEC bool findNode(Name name) const;

    DECLSPEC BulletMLNode* next();

    virtual void dump();

	// setter
	void setLabel(std::string const &label) { this->label_ = label; }
	void setGroup(std::string const &group) { this->group_ = group; }
	void setSprite(std::string const &sprite) { this->sprite_ = sprite; }
	void setBulletGroup(std::string const &group) { this->bulletGroup_ = group; }
	void setBulletSprite(std::string const &sprite) { this->bulletSprite_ = sprite; }
	void setShape(std::string const &shape) { this->shape_ = shape; }
	void setWidth(std::string const &width) { this->width_ = strtol(width.c_str(), 0, 10); }
	void setHeight(std::string const &height) { this->height_ = strtol(height.c_str(), 0, 10); }
	void setSimpleShape(std::string const &shape) { this->simpleShape_ = shape; }
	void setSimpleWidth(std::string const &width) { this->simpleWidth_ = strtol(width.c_str(), 0, 10); }
	void setSimpleHeight(std::string const &height) { this->simpleHeight_ = strtol(height.c_str(), 0, 10); }

	// getter
	std::string const &getLabel() const { return this->label_; }
	std::string const &getGroup() const { return this->group_; }
	std::string const &getSprite() const { return this->sprite_; }
	std::string const &getBulletGroup() const { return this->bulletGroup_; }
	std::string const &getBulletSprite() const { return this->bulletSprite_; }
	std::string const &getShape() const { return this->shape_; }
	uint32_t getWidth() const { return this->width_; }
	uint32_t getHeight() const { return this->height_; }
	std::string const &getSimpleShape() const { return this->simpleShape_; }
	uint32_t getSimpleWidth() const { return this->simpleWidth_; }
	uint32_t getSimpleHeight() const { return this->simpleHeight_; }

protected:
    Name					name_;
    Type					type_;
    int						refID_;
    std::auto_ptr<Number>	val_;
    std::string				label_;
	std::string				group_;
	std::string				sprite_;
	std::string				bulletGroup_;
	std::string				bulletSprite_;
	std::string				shape_;
	uint32_t				width_;
	uint32_t				height_;
	std::string				simpleShape_;
	uint32_t				simpleWidth_;
	uint32_t				simpleHeight_;
};


/*
template <class OutIte_>
void BulletMLNode::getAllChildren(Name name, OutIte_ outIte) {
    ChildIterator ite;
    for (ite = childBegin(); ite != childEnd(); ite++) {
		if ((*ite)->getName() == name) *outIte = *ite;
		outIte++;
    }
}

*/

#endif // ! BULLETMLTREE_H_
