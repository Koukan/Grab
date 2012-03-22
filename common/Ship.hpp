#pragma once

#include <vector>
#include "ConcreteObject.hpp"
#include "Sprite.hpp"
#include "Font.hpp"
#include "Input.hpp"
#include "PlayerBullet.hpp"
#include "Grab.hpp"
#include "ShipInfo.hpp"

class	Cannon;
class	Player;

class Ship : public ConcreteObject
{
public:
  Ship(Player &player, std::string const &spriteName, std::string const &bulletFileName,
       float speed, int fireFrequency, int r, int g, int b,
       GrabPosition::Position grab1, GrabPosition::Position grab2,
	   GrabPosition::Position grab3, unsigned int nbMaxGrabs = 3);
  Ship(Player &player, ShipInfo::ShipInfo const &info, int r, int g, int b,
	   unsigned int nbMaxGrabs = 3);
  ~Ship();

  virtual void	setPosition(double x, double y, double z = 0);
  void			setGrabLaunched(bool grabLaunched);
  bool			getGrabLaunched() const;
  Player		&getPlayer() const;
  double		getSpeed() const;
  void			addCannon(Cannon *cannon, unsigned int nGrab);
  void			releaseCannon(unsigned int nb);
  void			copyColor(Core::Sprite& sprite);
  virtual void	move(double time);

  void			fire(Core::GameState &);
  void			releaseFire();
  void			specialFire(Core::GameState &);
  void			releaseSpecialFire();

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
  void			inputGrab4(Core::InputCommand const &cmd);
  void			defineGrabPosition(GrabPosition::Position position, unsigned int nGrab);
  void			setDead(bool dead, bool command = true);
  bool			isDead() const;
  virtual void	draw(double elapsedTime);
  void			updateCannonsTrajectory();
  void			updateBulletTrajectory();
  void			launchGrab(std::string const &group, unsigned int nGrab, double x, double y);
  void			setNbSecRespawn(int nbSec);
  unsigned int	getScore() const;
  void			setScore(unsigned int score);

private:
  void			manageGrab(std::string const &group, unsigned int nGrab);

  Player					&_player;
  double					_speed;
  double					_tmpSpeed;
  int						_fireFrequency;
  bool						_dead;
  Cannon*					_cannons[4];
  unsigned int				_nbMaxGrabs; // can be up to 4 by choosing a special power
  bool						_grabLaunched;
  std::pair<double, double>	_grabsPositions[3];
  int						_colors[3];

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

  float			_joyPosX;
  float			_joyPosY;
  bool			_actions[Ship::NBACTIONS];

  std::string	_bulletFileName;
  PlayerBullet	*_playerBullet;
  unsigned int	_score;
  int			_nbSecRespawn;
  double		_elapsedTime;
  Core::CoreFont	*_timer;
  double		_targetx;
  double		_targety;
  bool			_target;

  void handleActions();
};
