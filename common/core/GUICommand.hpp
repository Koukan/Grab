#pragma once

#include "Input.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ GUICommand
{
public:

	enum PlayerType
	{
      KEYBOARD = 0,
      JOYSTICK1,
      JOYSTICK2,
      JOYSTICK3,
      JOYSTICK4
	};

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

  GUICommand(GUICommand::PlayerType playerType, GUICommand::DirectionState dir, ButtonAction buttonAction)
	  : playerType(playerType), type(GUICommand::DIRECTION), buttonAction(buttonAction), direction(dir)
  {
  }

  GUICommand(GUICommand::PlayerType playerType, GUICommand::ActionState action, ButtonAction buttonAction)
	  : playerType(playerType), type(GUICommand::ACTION), buttonAction(buttonAction), action(action)
  {
  }

  GUICommand(GUICommand::PlayerType playerType, Keyboard::Key key, ButtonAction buttonAction)
	  : playerType(playerType), type(GUICommand::KEY), buttonAction(buttonAction), key(key)
  {
  }

  ~GUICommand() {}

  GUICommand::PlayerType playerType;
  GUICommand::Type type;
  GUICommand::ButtonAction buttonAction;

  union
  {
    DirectionState direction;
    ActionState action;
	Keyboard::Key key;
  };
};

CORE_END_NAMESPACE
