#pragma once

#include "GUILayout.hpp"
#include "CommandHandler.hpp"
#include "Singleton.hpp"
#include "ButtonSprite.hpp"

#include <list>

class GUIManager : public CommandHandler, public GUILayout
{
public:
  GUIManager();
  ~GUIManager();

  virtual bool		handleCommand(Command const &command);
  void			registerButtonSprite(ButtonSprite &sprite);

private:
  std::list<ButtonSprite *> _spriteButtons;
};
