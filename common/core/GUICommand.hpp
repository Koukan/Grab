#pragma once

#include "Player.hpp"
#include "Input.hpp"

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

  GUICommand(Player::type type, GUICommand::DirectionState dir, GUICommand::ButtonAction buttonAction)
	  : playerType(type), type(GUICommand::DIRECTION), buttonAction(buttonAction), direction(dir)
  {
  }

  GUICommand(Player::type type, GUICommand::ActionState action, GUICommand::ButtonAction buttonAction)
	  : playerType(type), type(GUICommand::ACTION), buttonAction(buttonAction), action(action)
  {
  }

  GUICommand(Player::type type, Keyboard::Key key, GUICommand::ButtonAction buttonAction)
	  : playerType(type), type(GUICommand::KEY), buttonAction(buttonAction), key(key)
  {
  }

  ~GUICommand();

  Player::type				playerType;
  GUICommand::Type			type;
  GUICommand::ButtonAction	buttonAction;

  union
  {
    GUICommand::DirectionState direction;
    GUICommand::ActionState action;
	Keyboard::Key key;
  };
};
