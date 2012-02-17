#pragma once

#include <list>
#include "GUIElement.hpp"

CORE_BEGIN_NAMESPACE

class GUILayout : public GUIElement
{
public:
  void insertElementAtBegin(GUIElement &elem);
  void insertElementAtEnd(GUIElement &elem);

  virtual bool handleGUICommand(GUICommand const &command);
  virtual void draw(double elapseTime);
  virtual void draw(int x, int y, double elapseTime);
  void prevElement();
  void nextElement();

  virtual void focus();
  virtual void unfocus();

  void setDispatch(bool dispatch);

protected:
  GUILayout(int x, int y, int width, int height, int padding, GUILayout *layout, int nbElements, GUICommand::PlayerType playerType = GUICommand::ALL);
  GUILayout(int x, int y, int width, int height, int padding, int nbElements, GUICommand::PlayerType playerType = GUICommand::ALL);
  virtual ~GUILayout();

protected:
  std::list<GUIElement *> _elements;
  std::list<GUIElement *>::iterator _focusElement;
  std::list<GUIElement *>::iterator _begin;
  int _padding;
  int _nbElements;
  bool _dispatch;
};

CORE_END_NAMESPACE
