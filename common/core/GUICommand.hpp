#pragma once

#include "Command.hpp"

class GUICommand : public Command
{
public:

  enum type
    {
      DIRECTION,
      ACTION
    };
  
  enum buttonAction
    {
      PRESSED,
      RELEASED
    };

  enum directionState
    {
      DEFAULT,
      LEFT,
      RIGHT,
      UP,
      DOWN
    };
  
   enum actionState
     {
       SELECT,
       BACK
     };

  GUICommand(directionState);
  ~GUICommand();

  GUICommand::type type;
  GUICommand::buttonAction buttonAction;

  union
  {
    directionState direction;
    actionState action;
  };
};
