#pragma once

#include <vector>
#include "PhysicObject.hpp"
#include "Sprite.hpp"
#include "PlayerBullet.hpp"
#include "Grab.hpp"

class	Cannon;
class	Player;

class Ship : public Core::PhysicObject
{
public:
  struct ShipInfo
  {
    std::string shipName;
    std::string spriteName;
    std::string bulletFileName;
    float speed;
    int fireFrequency;
    Grab::Position grab1;
    Grab::Position grab2;
    Grab::Position grab3;
  };
  static ShipInfo const	shipsList[];
  static unsigned int const shipsListSize;

public:
  Ship(Player &player, ShipInfo const &info, int r, int g, int b,
	   unsigned int nbMaxGrabs = 3);
  ~Ship();

  void			setGrabLaunched(bool grabLaunched);
  bool			getGrabLaunched() const;
  float			getSpeed() const;
  void			addCannon(Cannon *cannon, unsigned int nGrab);
  void			copyColor(Core::Sprite& sprite);
  virtual void	move(double time);

  void			defineGrabPosition(Grab::Position position, unsigned int nGrab);
  void			setDead(bool dead);
  bool			isDead() const;
  void			updateCannonsTrajectory();
  void			updateBulletTrajectory();

private:
  void			launchGrab(std::string const &group, unsigned int nGrab);
  void			manageGrab(std::string const &group, unsigned int nGrab);

  Player		&_player;
  float			_speed;
  int			_fireFrequency;
  bool			_dead;
  Cannon*		_cannons[4];
  unsigned int	_nbMaxGrabs; // can be up to 4 by choosing a special power
  bool			_grabLaunched;
  std::pair<double, double> _grabsPositions[3];
  int			_colors[3];

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
