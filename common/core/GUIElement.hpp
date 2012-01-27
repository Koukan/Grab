#pragma once

#include "DrawableObject.hpp"
#include "Input.hpp"

class GUILayout;

class GUIElement : public DrawableObject
{
public:
  GUIElement(int x, int y, int width, int height, GUILayout *layout);
  GUIElement(int x, int y, int width, int height);
  virtual ~GUIElement();

  virtual bool handleGUICommand(InputCommand const &command) = 0;
  virtual void draw(double elapseTime) = 0;
  virtual void draw(int /*x*/, int /*y*/, double /*elapseTime*/) {}
  virtual void focus();
  virtual void unfocus();

  int getWidth() const;
  int getHeight() const;
  bool getEnable() const;

  void setWidth(int width);
  void setHeight(int height);
  void setEnable(bool enable);

protected:

  int _width;
  int _height;
  bool _isFocused;
  bool _enable;
};
