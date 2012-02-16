#pragma once

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

  GUICommand(int playerType, GUICommand::DirectionState dir, ButtonAction buttonAction)
	  : playerType(playerType), type(GUICommand::DIRECTION), buttonAction(buttonAction), direction(dir)
  {
  }

  GUICommand(int playerType, GUICommand::ActionState action, ButtonAction buttonAction)
	  : playerType(playerType), type(GUICommand::ACTION), buttonAction(buttonAction), action(action)
  {
  }

  GUICommand(int playerType, Keyboard::Key key, ButtonAction buttonAction)
	  : playerType(type), type(GUICommand::KEY), buttonAction(buttonAction), key(key)
  {
  }

  ~GUICommand() {}

  int playerType;
  GUICommand::Type type;
  GUICommand::ButtonAction buttonAction;

  union
  {
    DirectionState direction;
    ActionState action;
	Keyboard::Key key;
  };
};
