#pragma once

#include <vector>
#include "ConcreteObject.hpp"
#include "Sprite.hpp"
#include "Font.hpp"
#include "Input.hpp"
#include "PlayerBullet.hpp"
#include "Grab.hpp"
#include "ShipInfo.hpp"
#include "Color.hpp"

namespace Core
{
  class GameState;
}

struct	Color;
class	Cannon;
class	Player;

class Ship : public ConcreteObject
{
public:
  Ship(Player &player, ShipInfo::ShipInfo const &info, Core::GameState &state, Color const &color,
	   unsigned int nbMaxGrabs = 3);
  ~Ship();

  void			setSpecialPowerActive(bool isActive);
  virtual void	setPosition(double x, double y, double z = 0);
  void			setGrabLaunched(bool grabLaunched);
  bool			getGrabLaunched() const;
  Player		&getPlayer() const;
  double		getSpeed() const;
  void			addCannon(Cannon *cannon, unsigned int nGrab);
  void			releaseCannon(unsigned int nb);
  void			copyColor(Core::Sprite& sprite);
  virtual void	move(double time);

  void			manageFire();
  void			fire();
  void			releaseFire();
  void			specialFire();
  void			releaseSpecialFire();
  bool			isGood(uint32_t id);

  void			inputUp(Core::InputCommand const &cmd);
  void			inputDown(Core::InputCommand const &cmd);
  void			inputLeft(Core::InputCommand const &cmd);
  void			inputRight(Core::InputCommand const &cmd);
  void			inputReleasedUp(Core::InputCommand const &cmd);
  void			inputReleasedDown(Core::InputCommand const &cmd);
  void			inputReleasedLeft(Core::InputCommand const &cmd);
  void			inputReleasedRight(Core::InputCommand const &cmd);
  void			inputJoystickMoved(Core::InputCommand const &cmd);
  void			inputFire(Core::InputCommand const &cmd);
  void			inputReleasedFire(Core::InputCommand const &cmd);
  void			inputSpecialFire(Core::InputCommand const &cmd);
  void			inputReleasedSpecialFire(Core::InputCommand const &cmd);
  void			inputGrab1(Core::InputCommand const &cmd);
  void			inputGrab2(Core::InputCommand const &cmd);
  void			inputGrab3(Core::InputCommand const &cmd);
  void			defineGrabPosition(GrabPosition::Position position, unsigned int nGrab, int angle);
  void			setDead(bool dead, bool command = true);
  bool			isDead() const;
  virtual void	draw(double elapsedTime);
  void			updateCannonsTrajectory();
  void			updateBulletTrajectory();
  void			launchGrab(std::string const &group, unsigned int nGrab, double x, double y);
  void			specialPower(Core::InputCommand const& cmd);
  void			specialPower();
  void			bomb();
  void			shield();
  void			blackHole();
  void			disableShield();
  void			grab4();

  void			setNbSecRespawn(int nbSec);
  unsigned int		getScore() const;
  void			setScore(unsigned int score);
  unsigned int		getPowerGauge() const;
  void			increasePowerGauge(unsigned int score);
  void			resetState();

private:
  void			manageGrab(std::string const &group, unsigned int nGrab);

 // ship control
  enum Actions
  {
	  UP,
	  DOWN,
	  LEFT,
	  RIGHT,
	  FIRE,
	  SPECIAL_FIRE,
	  NBACTIONS
  };

  ShipInfo::ShipInfo const &			_caracs;
  Player					&_player;
  double					_speed;
  double					_tmpSpeed;
  bool						_dead;
  Cannon*					_cannons[4];
  unsigned int				_nbMaxGrabs; // can be up to 4 by choosing a special power
  bool						_grabLaunched;
  std::pair<double, double>	_grabsPositions[3];
  int						_angles[3];
  Color						_color;
  Core::Sound				*_fireSound;

  float			_joyPosX;
  float			_joyPosY;
  bool			_actions[Ship::NBACTIONS];

  PlayerBullet	*_playerBullet;
  PlayerBullet	*_concentratedPlayerBullet;
  unsigned int	_score;
  int			_nbSecRespawn;
  double		_elapsedTime;
  Core::CoreFont	*_timer;
  double		_targetx;
  double		_targety;
  bool			_target;
  uint32_t		_lastId;
  unsigned int		_powerGauge;
  void (Ship::*_specialPower)();
  bool			_specialPowerActive;
  ConcreteObject*	_electricAura;
  Core::GameState&	_state;
  
  union
  {
    ConcreteObject*	_shield;
    ConcreteObject*	_bomb;
  };	
  void handleActions();
  void resetPowerGauge();
};
