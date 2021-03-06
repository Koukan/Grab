/// BulletML を実行する
/**
 * 使い方：
 * BulletMLRunner を継承していくつかの純粋仮想関数を実装する。
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

/// BulletMLRunner が状態伝達に使用するクラス
class DECLSPEC BulletMLState {
public:
	BulletMLState(BulletMLParser* bulletml,
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

	BulletMLParser* getBulletML() { return bulletml_; }
	const std::vector<BulletMLNode*>& getNode() const { return node_; }
	bullet_shared_ptr<BulletMLParameter> getParameter() { return para_; }

	// setter
	void setLabel(std::string const &label) { this->label_ = label; }
	void setGroup(std::string const &group) { this->group_ = group; }
	void setSprite(std::string const &sprite) { this->sprite_ = sprite; }
	void setBulletGroup(std::string const &group) { this->bulletGroup_ = group; }
	void setBulletSprite(std::string const &sprite) { this->bulletSprite_ = sprite; }
	void setShape(std::string const &shape) { this->shape_ = shape; }
	void setWidth(uint32_t val) { this->width_ = (val) ? val : 1; }
	void setHeight(uint32_t val) { this->height_ = (val) ? val : 1; }
	void setSimpleShape(std::string const &shape) { this->simpleShape_ = shape; }
	void setSimpleWidth(uint32_t val) { this->simpleWidth_ = val; }
	void setSimpleHeight(uint32_t val) { this->simpleHeight_ = val; }
	void setHX(int x) { this->_hx = x; }
	void setHY(int y) { this->_hy = y; }
	void setSimpleX(int x) { this->_shx = x; }
	void setSimpleY(int y) { this->_shy = y; }
	void setDamage(uint32_t val) { this->damage_ = val; }
	void setLife(uint32_t val) { this->life_ = val; }
	void setSimpleDamage(uint32_t val) { this->simpleDamage_ = val; }
	void setLifeRank(double val) { this->lifeRank_ = val; }
	void setSimpleLife(uint32_t val) { this->simpleLife_ = val; }
	void setGenericStr(std::map<std::string, std::string> const &map) { this->strMap_ = map; }
	void setGenericInt(std::map<std::string, int> const &map) { this->intMap_ = map; }

	// getter
	std::string const	&getLabel() const { return this->label_; }
	std::string const	&getGroup() const { return this->group_; }
	std::string const	&getSprite() const { return this->sprite_; }
	std::string const	&getBulletGroup() const { return this->bulletGroup_; }
	std::string const	&getBulletSprite() const { return this->bulletSprite_; }
	std::string const	&getShape() const { return this->shape_; }
	uint32_t			getRadius() const { return this->width_; }
	uint32_t			getWidth() const { return this->width_; }
	uint32_t			getHeight() const { return this->height_; }
	std::string const	&getSimpleShape() const { return this->simpleShape_; }
	uint32_t			getSimpleRadius() const { return this->simpleWidth_; }
	uint32_t			getSimpleWidth() const { return this->simpleWidth_; }
	uint32_t			getSimpleHeight() const { return this->simpleHeight_; }
	int				getHitboxX() const { return this->_hx; }
	int				getHitboxY() const { return this->_hy; }
	int				getSimpleHitboxX() const { return this->_shx; }
	int				getSimpleHitboxY() const { return this->_shy; }
	uint32_t			getDamage() const { return this->damage_; }
	uint32_t			getLife() const { return this->life_; }
	uint32_t			getSimpleDamage() const { return this->simpleDamage_; }
	double				getLifeRank() const { return this->lifeRank_; }
	uint32_t			getSimpleLife() const { return this->simpleLife_; }
	std::string		getGenericStr(std::string const &name) const
	{
		std::map<std::string, std::string>::const_iterator it = this->strMap_.find(name);

		if (it != this->strMap_.end())
			return it->second;
		return "";
	}
	int				getGenericInt(std::string const &name) const
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

/// BulletML を実行するクラス
/**
 * <pre>
 * 使い方。
 *  1. これを継承して、Bullet を実際に動かせるクラスを作る。
 *  2. 純粋仮想関数を全て実装する。
 *  3. 必要なら、changeDirection などのために必要な仮想関数を実装する。
 *  4. このクラスのオブジェクトに対して、com_->run(); などとする。
 * </pre>
 */

class DECLSPEC BulletMLRunner {
public:
	explicit BulletMLRunner(BulletMLParser* bulletml);
    explicit BulletMLRunner(BulletMLState* state);
    virtual ~BulletMLRunner();

	/// 実行する
    void run();

public:
	/// 実行が終了しているかどうか
	bool isEnd() const;

public:
	// ----- 絶対実装しなければならない関数群の始まり -----
	//@{
	/// この弾の角度を求める
	/**
	 * @return 角度を度単位で、上方向 0 で時計周りで返す
	 */
	virtual double getBulletDirection() =0;
	/// この弾から自機を狙う角度を求める
	/**
	 * @return 角度を度単位で、上方向 0 で時計周りで返す
	 */
	virtual double getAimDirection() =0;
	/// この弾の速度を求める
	virtual double getBulletSpeed() =0;
	/// デフォルトの速度を求める
	virtual double getDefaultSpeed() =0;
	/// ランクを求める
	/**
	 * @return 0 から 1 までの実数
	 */
	virtual double getRank() =0;
	/// action を持たない弾を作る
	virtual void createSimpleBullet(double direction, double speed) =0;
	/// action を持つ弾を作る
	/**
	 * @param state
	 * 新しい弾の BulletMLRunner のコンストラクタに渡すこと。
	 * もし渡さないのであれば、delete で解放しなければならない。
	 */
	virtual void createBullet(BulletMLState* state,
									   double direction, double speed) =0;
	/// 弾の基準となるターンの値を返す、通常はフレーム数
	/**
	 * @return
	 * ゲームごとの基準でオーダーは変更して構いませんが、
	 * 負数は許されません。
	 * xml データ上で、wait と term のオーダーが揃っていれば問題ありません。
	 */
	virtual int getTurn() =0;
	/// 死ぬ
	virtual void doVanish() =0;
	//@}
	// ----- 絶対実装しなければならない関数群の終わり -----

	// ----- 必要があれば実装する関数群の始まり -----
   	//@{
	/// 弾の方向を指定した方向に変更する
	virtual void doChangeDirection(double) {}
	/// 弾の速度を指定した値に変更する
	virtual void doChangeSpeed(double) {}
	/// accel に対するインターフェイス
	/**
	 * @todo
	 * horizontal, vertical の type は未実装です。
	 * どれも absolute になってしまいます。
	 */
	virtual void doAccelX(double) {}
	/// accel に対するインターフェイス
	/**
	 * @todo
	 * horizontal, vertical の type は未実装です。
	 * どれも absolute になってしまいます。
	 */
	virtual void doAccelY(double) {}
	/// 弾の速さの X 方向成分を返します
	/**
	 * accel を使う場合はオーバーライドして下さい
 	 */
	virtual double getBulletSpeedX() { return 0; }
	/// 弾の速さの Y 方向成分を返します
	/**
	 * accel を使う場合はオーバーライドして下さい
 	 */
	virtual double getBulletSpeedY() { return 0; }
    //@}
	// ----- 必要があれば実装する関数群の終わり -----

	/// 乱数を返す
	/**
	 * 見てのとおり、デフォルトでは std::rand が用いられます。
	 */
	virtual double getRand() { return (double)rand() / RAND_MAX; }

private:
	/// BulletMLRunnerImpl をオーバーライドする場合、これもオーバーライドする
	virtual BulletMLRunnerImpl* makeImpl(BulletMLState* state);

protected:
	std::vector<BulletMLRunnerImpl*>	impl_;
	std::stack<BulletMLState*>		state_;
};

#endif // ! BULLETRUNNER_H_

