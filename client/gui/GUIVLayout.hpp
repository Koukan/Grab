#pragma once

#include "GUILayout.hpp"
#include "Sprite.hpp"
#include <string>

class GUIVLayout : public GUILayout
{
public:
  GUIVLayout(int x, int y, int width, int height, int padding, GUILayout *layout, int nbElements = 100, std::string const &arrowUp = "", std::string const &arrowDown = "");
  GUIVLayout(int x, int y, int width, int height, int padding, int nbElements = 100, std::string const &arrowUp = "", std::string const &arrowDown = "");
  ~GUIVLayout();

  virtual void draw(double elapseTime);
  virtual void draw(int x, int y, double elapseTime);

  virtual bool handleGUICommand(InputCommand const &command);

private:
  Sprite *_upArrow;
  Sprite *_downArrow;
};
