#pragma once

#include "GUIElement.hpp"
#include "ButtonSprite.hpp"
#include "Font.hpp"
#include "GameStateManager.hpp"
#include <string>

class GUILabel : public Core::GUIElement
{
public:
  GUILabel(std::string const &name, std::string const &font, std::string const &sprite, int x, int y);
  GUILabel(std::string const &name, std::string const &font, std::string const &sprite, Core::GUILayout *layout);
  ~GUILabel();

  virtual bool handleGUICommand(Core::GUICommand const &command);
  virtual void	draw(double elapseTime);
  virtual void	draw(int x, int y, double elapseTime);
  virtual void	setText(std::string const &str);

private:
  Core::Sprite *_sprite;
  Core::CoreFont *_font;
};
