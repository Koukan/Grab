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

  GUICommand *createGUICommand(InputCommand const &cmd);
};
