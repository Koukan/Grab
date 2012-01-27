#include "GUIManager.hpp"

GUIManager::GUIManager()
  : GUILayout(0, 0, 0, 0, 0, 0, 0)
{
}

GUIManager::~GUIManager()
{
  for (std::list<ButtonSprite *>::iterator it = this->_spriteButtons.begin(); it != this->_spriteButtons.end(); ++it)
    {
      delete *it;
    }
}

bool		GUIManager::handleCommand(Command const &command)
{
  if (command.name == "Input")
    return (this->handleGUICommand(static_cast<InputCommand const &>(command)));
  return (false);
}

void		GUIManager::registerButtonSprite(ButtonSprite &sprite)
{
  this->_spriteButtons.push_front(&sprite);
}
