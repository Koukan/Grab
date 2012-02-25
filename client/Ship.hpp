#pragma once

#include <vector>
#include "ConcreteObject.hpp"
#include "Sprite.hpp"
#include "Input.hpp"

class Grab;

class Ship : public ConcreteObject
{
public:
  Ship(std::string const &spriteName, std::string const &bulletFileName, float speed, int fireFrequency, int r, int g, int b, unsigned int nbMaxGrabs = 3);

  Ship(std::string const &spriteName, std::string const &bulletFileName, float speed, int fireFrequency, int r, int g, int b, std::pair<int, int> grabs[4], unsigned int nbMaxGrabs = 3);

  ~Ship();

  
  void registerInGameObjectManager(std::string const &shipGroup,
				   std::string const &grabsGroup);
  void launchGrab(std::string const &group = "grabs");

  void setGrabLaunched(bool grabLaunched);
  bool getGrabLaunched() const;
  void addGrab(Grab* grab);
  
  void inputUp(Core::InputCommand const &cmd);
  void inputDown(Core::InputCommand const &cmd);
  void inputLeft(Core::InputCommand const &cmd);
  void inputRight(Core::InputCommand const &cmd);
  void inputReleasedUp(Core::InputCommand const &cmd);
  void inputReleasedDown(Core::InputCommand const &cmd);
  void inputReleasedLeft(Core::InputCommand const &cmd);
  void inputReleasedRight(Core::InputCommand const &cmd);
  void inputJoystickMoved(Core::InputCommand const &cmd);

private:
  float			_speed;
  int				_fireFrequency;
  std::vector<Grab *> _grabs;
  unsigned int _nbMaxGrabs; // can be up to 4 by choosing a special power
  bool _grabLaunched;

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

  void handleActions();

public:
  struct ShipInfo
  {
    std::string shipName;
    std::string spriteName;
    std::string bulletFileName;
    float speed;
    int fireFrequency;
  };
  static ShipInfo const	shipsList[];
  static unsigned int const shipsListSize;
};
