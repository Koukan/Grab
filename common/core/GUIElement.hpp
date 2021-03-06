#pragma once

#include "DrawableObject.hpp"
#include "Input.hpp"
#include "GUICommand.hpp"

CORE_BEGIN_NAMESPACE

class GUILayout;

class CORE_DLLREQ GUIElement : public DrawableObject
{
public:
	GUIElement(int x, int y, int width, int height, GUILayout *layout, GUICommand::PlayerType playerType = GUICommand::ALL);
  GUIElement(int x, int y, int width, int height, GUICommand::PlayerType playerType = GUICommand::ALL);
  virtual ~GUIElement();

  bool catchGUICommand(GUICommand const &command);
  virtual bool handleGUICommand(GUICommand const &command) = 0;
  virtual void draw(double elapseTime) = 0;
  virtual void draw(int /*x*/, int /*y*/, double /*elapseTime*/) {}
  virtual void focus();
  virtual void unfocus();

  int getWidth() const;
  int getHeight() const;
  bool getEnable() const;
  bool getHide() const;

  void setWidth(int width);
  void setHeight(int height);
  void setEnable(bool enable);
  void setHide(bool hide);

protected:

  int _width;
  int _height;
  bool _isFocused;
  bool _enable;
  bool _hide;
  GUICommand::PlayerType _playerType;
};

CORE_END_NAMESPACE
