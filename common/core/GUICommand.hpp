#pragma once

#include "Input.hpp"
#include "Player.hpp"

class GUICommand
{
public:

  enum Type
    {
      DIRECTION,
      ACTION,
	  KEY
    };
  
  enum ButtonAction
    {
      PRESSED,
      RELEASED
    };

  enum DirectionState
    {
      DEFAULT,
      LEFT,
      RIGHT,
      UP,
      DOWN
    };
  
   enum ActionState
     {
       SELECT,
       BACK
     };

  GUICommand(Player::type type, GUICommand::DirectionState dir, ButtonAction buttonAction)
	  : playerType(type), type(GUICommand::DIRECTION), buttonAction(buttonAction), direction(dir)
  {
  }

  GUICommand(Player::type type, GUICommand::ActionState action, ButtonAction buttonAction)
	  : playerType(type), type(GUICommand::ACTION), buttonAction(buttonAction), action(action)
  {
  }

  GUICommand(Player::type type, Keyboard::Key key, ButtonAction buttonAction)
	  : playerType(type), type(GUICommand::KEY), buttonAction(buttonAction), key(key)
  {
  }

  ~GUICommand() {}

  Player::type playerType;
  GUICommand::Type type;
  GUICommand::ButtonAction buttonAction;

  union
  {
    DirectionState direction;
    ActionState action;
	Keyboard::Key key;
  };
};
