#pragma once

#include "GUILayout.hpp"
#include "CommandHandler.hpp"
#include "Singleton.hpp"
#include "ButtonSprite.hpp"
#include "Module.hpp"
#include "Input.hpp"
#include "GUICommand.hpp"
#include <list>

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ GUIManager : public CommandHandler, public GUILayout
{
public:
  GUIManager(bool autoBack = false);
  ~GUIManager();

  virtual bool		handleCommand(Command const &command);
  virtual bool		handleGUICommand(GUICommand const &command);
  void				registerButtonSprite(ButtonSprite &sprite);

  virtual	void	init();
  void				update(double elapsedTime = 0);
  virtual void		destroy();

private:
  std::list<ButtonSprite *> _spriteButtons;
  GUICommand::DirectionState _direction[4];
  double _elapsedTime[4];

  GUICommand *createGUICommand(InputCommand const &cmd);

  bool _autoBack;
};

CORE_END_NAMESPACE
