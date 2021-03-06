#pragma once

#include <set>
#include <random>
#include "Net.hpp"
#include "bulletmlrunner.h"
#include "Sprite.hpp"
#include "PhysicObject.hpp"
#include "Bullet.hpp"
#include "GameState.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ BulletCommand : public Bullet, public BulletMLRunner
{
  public:
    BulletCommand(std::string const &parser, GameState &gstate,
		  double x = 0, double y = 0, double vx = 0, double vy = 0, bool paused = false);
    BulletCommand(BulletMLParser &parser, GameState &gstate,
		  double x = 0, double y = 0, double vx = 0, double vy = 0, bool paused = false);
    BulletCommand(BulletMLState &state, GameState &gstate, bool paused,
		  double x = 0, double y = 0, double vx = 0, double vy = 0);
    BulletCommand(BulletMLState &state, GameState &gstate, HitBox &box, bool paused,
		  double vx = 0, double vy = 0, double xHitboxOffset = 0, double yHitboxOffset = 0);
    virtual ~BulletCommand();

	// BulletMLRunner overloaded
	virtual double	getBulletDirection();
    virtual double	getAimDirection();
    virtual double	getBulletSpeed();
    virtual double	getDefaultSpeed();
    virtual double	getRank();
	virtual double	getRand();
    virtual void	createSimpleBullet(double direction, double speed);
    virtual void	createBullet(BulletMLState* state, double direction, double speed);
    virtual int		getTurn();
    virtual void	doVanish();
    virtual void	doChangeDirection(double direction);
    virtual void	doChangeSpeed(double speed);
    virtual void	doAccelX(double speedx);
    virtual void	doAccelY(double speedy);
    virtual double	getBulletSpeedX();
    virtual double	getBulletSpeedY();
	void			removeChild(uint32_t id);

	double			getAimDirection(double defaultValue);
	void			isCommanded(bool commanded);
	bool			isCommanded() const;
	void			addFocus(std::string const &name);
	void			removeFocus(std::string const &name);
	void			setRank(double rank);
    virtual void	move(double time);
	void			setSeed(uint32_t seed);
	uint32_t		getSeed() const;
	Bullet			*getChild(uint32_t id) const;
	std::string const	&getBulletScript() const;
	void			start();
	void			stop();
	bool			isStarted() const;

	virtual void	erase();

  protected:
	typedef std::map<uint32_t, Bullet*>	BulletMap;
	enum		Shape
	{
		Circle,
		Rectangle,
		UNKNOWN
	};

	void			setSpeedDirection();
	void			insertChild(Bullet &bullet);
	virtual	BulletCommand	*instantiateBullet(BulletMLState* state, double direction, double speed);

	double					_direction;
	double					_speed;
    double					_turn;
    bool					_end;
    GameState				&_state;
	Shape					_shape;
	uint32_t				_width;
	uint32_t				_height;
	double					_rank;
	uint32_t				_nextId;
	uint32_t				_simpleLife;
	double					_lifeRank;
	uint32_t				_simpleDamage;
	std::set<std::string>	_focus;
	BulletMap				_childs;
	std::string				_simpleSprite;
	std::string				_simpleGroup;
	double					_simpleXHitbox;
	double					_simpleYHitbox;
	std::string				_grabBullet;
	std::string				_deathBullet;
	std::mt19937			_rand;
	uint32_t				_seed;
	bool					_paused;
	bool					_isCommanded;
	bool					_stop;

 public:
	unsigned int const	score;

 private:
	void			managePaused(GameState &);
};

CORE_END_NAMESPACE
