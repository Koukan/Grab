/// BulletML �����s����
/**
 * �g�����F
 * BulletMLRunner ���p�����Ă������̏������z�֐�����������B
 */

#ifndef BULLETRUNNER_H_
#define BULLETRUNNER_H_

#include "bulletmltree.h"
#include "bulletmlcommon.h"

#include <stack>
#include <vector>
#include <memory>
#include <iostream>

class BulletMLParser;
class BulletMLNode;
class BulletMLRunnerImpl;

typedef std::vector<double> BulletMLParameter;

/// BulletMLRunner ����ԓ`�B�Ɏg�p����N���X
class BulletMLState {
public:
	DECLSPEC BulletMLState(BulletMLParser* bulletml,
						   const std::vector<BulletMLNode*>& node,
						   bullet_shared_ptr<BulletMLParameter> para)
		: bulletml_(bulletml), node_(node.begin(), node.end()), para_(para), width_(1), height_(1)
	{
		simpleWidth_ = 1;
		simpleHeight_ = 1;
		_hx = 0;
		_hy = 0;
		_shx = 0;
		_shy = 0;
		damage_ = 1;
		life_ = 1;
		lifeRank_ = false;
		simpleDamage_ = 1;
		simpleLife_ = 1;
	}

	DECLSPEC BulletMLParser* getBulletML() { return bulletml_; }
	DECLSPEC const std::vector<BulletMLNode*>& getNode() const { return node_; }
	DECLSPEC bullet_shared_ptr<BulletMLParameter> getParameter() { return para_; }

	// setter
	DECLSPEC void setLabel(std::string const &label) { this->label_ = label; }
	DECLSPEC void setGroup(std::string const &group) { this->group_ = group; }
	DECLSPEC void setSprite(std::string const &sprite) { this->sprite_ = sprite; }
	DECLSPEC void setBulletGroup(std::string const &group) { this->bulletGroup_ = group; }
	DECLSPEC void setBulletSprite(std::string const &sprite) { this->bulletSprite_ = sprite; }
	DECLSPEC void setShape(std::string const &shape) { this->shape_ = shape; }
	DECLSPEC void setWidth(uint32_t val) { this->width_ = (val) ? val : 1; }
	DECLSPEC void setHeight(uint32_t val) { this->height_ = (val) ? val : 1; }
	DECLSPEC void setSimpleShape(std::string const &shape) { this->simpleShape_ = shape; }
	DECLSPEC void setSimpleWidth(uint32_t val) { this->simpleWidth_ = val; }
	DECLSPEC void setSimpleHeight(uint32_t val) { this->simpleHeight_ = val; }
	DECLSPEC void setHX(int x) { this->_hx = x; }
	DECLSPEC void setHY(int y) { this->_hy = y; }
	DECLSPEC void setSimpleX(int x) { this->_shx = x; }
	DECLSPEC void setSimpleY(int y) { this->_shy = y; }
	DECLSPEC void setDamage(uint32_t val) { this->damage_ = val; }
	DECLSPEC void setLife(uint32_t val) { this->life_ = val; }
	DECLSPEC void setSimpleDamage(uint32_t val) { this->simpleDamage_ = val; }
	DECLSPEC void setLifeRank(double val) { this->lifeRank_ = val; }
	DECLSPEC void setSimpleLife(uint32_t val) { this->simpleLife_ = val; }
	DECLSPEC void setGenericStr(std::map<std::string, std::string> const &map) { this->strMap_ = map; }
	DECLSPEC void setGenericInt(std::map<std::string, int> const &map) { this->intMap_ = map; }

	// getter
	DECLSPEC std::string const	&getLabel() const { return this->label_; }
	DECLSPEC std::string const	&getGroup() const { return this->group_; }
	DECLSPEC std::string const	&getSprite() const { return this->sprite_; }
	DECLSPEC std::string const	&getBulletGroup() const { return this->bulletGroup_; }
	DECLSPEC std::string const	&getBulletSprite() const { return this->bulletSprite_; }
	DECLSPEC std::string const	&getShape() const { return this->shape_; }
	DECLSPEC uint32_t			getRadius() const { return this->width_; }
	DECLSPEC uint32_t			getWidth() const { return this->width_; }
	DECLSPEC uint32_t			getHeight() const { return this->height_; }
	DECLSPEC std::string const	&getSimpleShape() const { return this->simpleShape_; }
	DECLSPEC uint32_t			getSimpleRadius() const { return this->simpleWidth_; }
	DECLSPEC uint32_t			getSimpleWidth() const { return this->simpleWidth_; }
	DECLSPEC uint32_t			getSimpleHeight() const { return this->simpleHeight_; }
	DECLSPEC int				getHitboxX() const { return this->_hx; }
	DECLSPEC int				getHitboxY() const { return this->_hy; }
	DECLSPEC int				getSimpleHitboxX() const { return this->_shx; }
	DECLSPEC int				getSimpleHitboxY() const { return this->_shy; }
	DECLSPEC uint32_t			getDamage() const { return this->damage_; }
	DECLSPEC uint32_t			getLife() const { return this->life_; }
	DECLSPEC uint32_t			getSimpleDamage() const { return this->simpleDamage_; }
	DECLSPEC double				getLifeRank() const { return this->lifeRank_; }
	DECLSPEC uint32_t			getSimpleLife() const { return this->simpleLife_; }
	DECLSPEC std::string		getGenericStr(std::string const &name) const
	{
		std::map<std::string, std::string>::const_iterator it = this->strMap_.find(name);

		if (it != this->strMap_.end())
			return it->second;
		return "";
	}
	DECLSPEC int				getGenericInt(std::string const &name) const
	{
		std::map<std::string, int>::const_iterator it = this->intMap_.find(name);

		if (it != this->intMap_.end())
			return it->second;
		return 0;
	}

private:
	BulletMLParser*							bulletml_;
	std::vector<BulletMLNode*>				node_;
	bullet_shared_ptr<BulletMLParameter>	para_;
	uint32_t								width_;
	uint32_t								height_;
    std::string								label_;
	std::string								group_;
	std::string								sprite_;
	std::string								bulletGroup_;
	std::string								bulletSprite_;
	//hitbox
	std::string								shape_;
	std::string								simpleShape_;
	uint32_t								simpleWidth_;
	uint32_t								simpleHeight_;
	int										_hx;
	int										_hy;
	int										_shx;
	int										_shy;
	//end hitbox
	uint32_t								damage_;
	uint32_t								life_;
	double									lifeRank_;
	uint32_t								simpleDamage_;
	uint32_t								simpleLife_;
	std::map<std::string, std::string>		strMap_;
	std::map<std::string, int>				intMap_;
};

/// BulletML �����s����N���X
/**
 * <pre>
 * �g�����B
 *  1. ������p�����āABullet �����ۂɓ�������N���X�����B
 *  2. �������z�֐���S�Ď�������B
 *  3. �K�v�Ȃ�AchangeDirection �Ȃǂ̂��߂ɕK�v�ȉ��z�֐�����������B
 *  4. ���̃N���X�̃I�u�W�F�N�g�ɑ΂��āAcom_->run(); �ȂǂƂ���B
 * </pre>
 */

class BulletMLRunner {
public:
	DECLSPEC explicit BulletMLRunner(BulletMLParser* bulletml);
    DECLSPEC explicit BulletMLRunner(BulletMLState* state);
    DECLSPEC virtual ~BulletMLRunner();

	/// ���s����
    DECLSPEC void run();

public:
	/// ���s���I�����Ă��邩�ǂ���
	DECLSPEC bool isEnd() const;

public:
	// ----- ��Ύ������Ȃ���΂Ȃ�Ȃ��֐��Q�̎n�܂� -----
	//@{
	/// ���̒e�̊p�x�����߂�
	/**
	 * @return �p�x��x�P�ʂŁA����� 0 �Ŏ��v����ŕԂ�
	 */
	DECLSPEC virtual double getBulletDirection() =0;
	/// ���̒e���玩�@��_���p�x�����߂�
	/**
	 * @return �p�x��x�P�ʂŁA����� 0 �Ŏ��v����ŕԂ�
	 */
	DECLSPEC virtual double getAimDirection() =0;
	/// ���̒e�̑��x�����߂�
	DECLSPEC virtual double getBulletSpeed() =0;
	/// �f�t�H���g�̑��x�����߂�
	DECLSPEC virtual double getDefaultSpeed() =0;
	/// �����N�����߂�
	/**
	 * @return 0 ���� 1 �܂ł̎���
	 */
	DECLSPEC virtual double getRank() =0;
	/// action �������Ȃ��e�����
	DECLSPEC virtual void createSimpleBullet(double direction, double speed) =0;
	/// action �����e�����
	/**
	 * @param state
	 * �V�����e�� BulletMLRunner �̃R���X�g���N�^�ɓn�����ƁB
	 * �����n���Ȃ��̂ł���΁Adelete �ŉ�����Ȃ���΂Ȃ�Ȃ��B
	 */
	DECLSPEC virtual void createBullet(BulletMLState* state,
									   double direction, double speed) =0;
	/// �e�̊�ƂȂ�^�[���̒l��Ԃ��A�ʏ�̓t���[����
	/**
	 * @return
	 * �Q�[�����Ƃ̊�ŃI�[�_�[�͕ύX���č\���܂��񂪁A
	 * �����͋�����܂���B
	 * xml �f�[�^��ŁAwait �� term �̃I�[�_�[�������Ă���Ζ�肠��܂���B
	 */
	DECLSPEC virtual int getTurn() =0;
	/// ����
	DECLSPEC virtual void doVanish() =0;
	//@}
	// ----- ��Ύ������Ȃ���΂Ȃ�Ȃ��֐��Q�̏I��� -----

	// ----- �K�v������Ύ�������֐��Q�̎n�܂� -----
   	//@{
	/// �e�̕������w�肵�������ɕύX����
	DECLSPEC virtual void doChangeDirection(double) {}
	/// �e�̑��x���w�肵���l�ɕύX����
	DECLSPEC virtual void doChangeSpeed(double) {}
	/// accel �ɑ΂���C���^�[�t�F�C�X
	/**
	 * @todo
	 * horizontal, vertical �� type �͖������ł��B
	 * �ǂ�� absolute �ɂȂ��Ă��܂��܂��B
	 */
	DECLSPEC virtual void doAccelX(double) {}
	/// accel �ɑ΂���C���^�[�t�F�C�X
	/**
	 * @todo
	 * horizontal, vertical �� type �͖������ł��B
	 * �ǂ�� absolute �ɂȂ��Ă��܂��܂��B
	 */
	DECLSPEC virtual void doAccelY(double) {}
	/// �e�̑����� X ����������Ԃ��܂�
	/**
	 * accel ���g���ꍇ�̓I�[�o�[���C�h���ĉ�����
 	 */
	DECLSPEC virtual double getBulletSpeedX() { return 0; }
	/// �e�̑����� Y ����������Ԃ��܂�
	/**
	 * accel ���g���ꍇ�̓I�[�o�[���C�h���ĉ�����
 	 */
	DECLSPEC virtual double getBulletSpeedY() { return 0; }
    //@}
	// ----- �K�v������Ύ�������֐��Q�̏I��� -----

	/// ������Ԃ�
	/**
	 * ���Ă̂Ƃ���A�f�t�H���g�ł� std::rand ���p�����܂��B
	 */
	DECLSPEC virtual double getRand() { return (double)rand() / RAND_MAX; }

private:
	/// BulletMLRunnerImpl ���I�[�o�[���C�h����ꍇ�A������I�[�o�[���C�h����
	virtual BulletMLRunnerImpl* makeImpl(BulletMLState* state);

protected:
	std::vector<BulletMLRunnerImpl*>	impl_;
	std::stack<BulletMLState*>		state_;
};

#endif // ! BULLETRUNNER_H_

