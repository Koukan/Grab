#pragma once

#include "GUIElement.hpp"
#include "ButtonSprite.hpp"
#include "Font.hpp"
#include "GameStateManager.hpp"
#include <string>

class GUILabel : public GUIElement
{
public:
  GUILabel(std::string const &name, std::string const &font, std::string const &sprite, int x, int y);
  GUILabel(std::string const &name, std::string const &font, std::string const &sprite, GUILayout *layout);
  ~GUILabel();

  virtual bool handleGUICommand(InputCommand const &command);
  virtual void	draw(double elapseTime);
  virtual void	draw(int x, int y, double elapseTime);
  virtual void	setText(std::string const &str);

private:
  Sprite *_sprite;
  Font *_font;
};
