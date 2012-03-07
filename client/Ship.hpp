#pragma once

#include <vector>
#include "ConcreteObject.hpp"
#include "Sprite.hpp"
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

  void			setGrabLaunched(bool grabLaunched);
  bool			getGrabLaunched() const;
  float			getSpeed() const;
  void			addCannon(Cannon *cannon, unsigned int nGrab);
  void			copyColor(Core::Sprite& sprite);
  virtual void	move(double time);

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
  void			inputGrab1(Core::InputCommand const &cmd);
  void			inputGrab2(Core::InputCommand const &cmd);
  void			inputGrab3(Core::InputCommand const &cmd);
  void			inputGrab4(Core::InputCommand const &cmd);
  void			defineGrabPosition(GrabPosition::Position position, unsigned int nGrab);
  void			setDead(bool dead);
  bool			isDead() const;
  virtual void	draw(double elapsedTime);
  void			updateCannonsTrajectory();
  void			updateBulletTrajectory();

private:
  void			launchGrab(std::string const &group, unsigned int nGrab);
  void			manageGrab(std::string const &group, unsigned int nGrab);

  Player					&_player;
  float						_speed;
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
	  NBACTIONS
  };

  float			_joyPosX;
  float			_joyPosY;
  bool			_actions[Ship::NBACTIONS];

  std::string	_bulletFileName;
  PlayerBullet	*_playerBullet;

  void handleActions();
};
