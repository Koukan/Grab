#pragma once

#include <list>
#include "GUIElement.hpp"

class GUILayout : public GUIElement
{
public:
  void insertElementAtBegin(GUIElement &elem);
  void insertElementAtEnd(GUIElement &elem);

  virtual bool handleGUICommand(InputCommand const &command);
  virtual void draw(double elapseTime);
  virtual void draw(int x, int y, double elapseTime);
  void prevElement();
  void nextElement();

  virtual void focus();
  virtual void unfocus();

protected:
  GUILayout(int x, int y, int width, int height, int padding, GUILayout *layout, int nbElements);
  GUILayout(int x, int y, int width, int height, int padding, int nbElements);
  virtual ~GUILayout();

protected:
  std::list<GUIElement *> _elements;
  std::list<GUIElement *>::iterator _focusElement;
  std::list<GUIElement *>::iterator _begin;
  int _padding;
  int _nbElements;
};
