#pragma once

#include "GUILayout.hpp"
#include "CommandHandler.hpp"
#include "Singleton.hpp"
#include "ButtonSprite.hpp"
#include "Module.hpp"
#include "Input.hpp"
#include "GUICommand.hpp"

#include <list>

class GUIManager : public CommandHandler, public GUILayout
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

  GUIManager();
  ~GUIManager();

  virtual bool		handleCommand(Command const &command);
  void				registerButtonSprite(ButtonSprite &sprite);

  virtual	void	init();
  void				update(double elapsedTime = 0);
  virtual void		destroy();

private:
  std::list<ButtonSprite *> _spriteButtons;
  GUICommand::DirectionState _direction[4];

  bool	updateDirection(InputCommand const &cmd);
  GUICommand *createGUICommand(InputCommand const &cmd);
};
