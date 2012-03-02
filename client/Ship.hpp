#pragma once

#include <vector>
#include "ConcreteObject.hpp"
#include "Sprite.hpp"
#include "Input.hpp"
#include "PlayerBullet.hpp"
#include "Grab.hpp"

class Cannon;

class Ship : public ConcreteObject
{
public:
  Ship(std::string const &spriteName, std::string const &bulletFileName,
       float speed, int fireFrequency, int r, int g, int b,
       Grab::Position grab1, Grab::Position grab2, Grab::Position grab3,
       std::string const &group = "players", unsigned int nbMaxGrabs = 3);

  ~Ship();

  void launchGrab(std::string const &group = "grabs");

  void setGrabLaunched(bool grabLaunched);
  bool getGrabLaunched() const;
  float getSpeed() const;
  void addCannon(Cannon *cannon);

  void inputUp(Core::InputCommand const &cmd);
  void inputDown(Core::InputCommand const &cmd);
  void inputLeft(Core::InputCommand const &cmd);
  void inputRight(Core::InputCommand const &cmd);
  void inputReleasedUp(Core::InputCommand const &cmd);
  void inputReleasedDown(Core::InputCommand const &cmd);
  void inputReleasedLeft(Core::InputCommand const &cmd);
  void inputReleasedRight(Core::InputCommand const &cmd);
  void inputJoystickMoved(Core::InputCommand const &cmd);
  void inputFire(Core::InputCommand const &cmd);
  void inputReleasedFire(Core::InputCommand const &cmd);
  void defineGrabPosition(Grab::Position position, unsigned int nGrab);

private:
  typedef std::vector<Cannon *> cannonContainer;

  float			_speed;
  int			_fireFrequency;
  cannonContainer	_cannons;
  unsigned int		_nbMaxGrabs; // can be up to 4 by choosing a special power
  bool			_grabLaunched;
  std::pair<double, double> _grabsPositions[3];

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
  void updateCannonsTrajectory();
  void updateBulletTrajectory();

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
};
