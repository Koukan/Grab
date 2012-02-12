#pragma once

#include "GUIButton.hpp"
#include <list>
#include <string>

class GUIBindButton : public GUIButton<GUIBindButton>
{
public:
  GUIBindButton(int playerNb, std::string const &font, ButtonSprite const &sprite, int x, int y);
  GUIBindButton(int playerNb, std::string const &font, ButtonSprite const &sprite, GUILayout *layout);
  ~GUIBindButton();

  virtual bool handleGUICommand(InputCommand const &command);
  void pushButton();

private:
  int						_playerNb;
  std::list<std::string>			_bindingList;
  std::list<std::string>::const_iterator	_iterator;
};
