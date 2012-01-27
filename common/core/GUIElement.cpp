#include "GUIElement.hpp"
#include "GUILayout.hpp"
#include "GameStateManager.hpp"

GUIElement::GUIElement(int x, int y, int width, int height, GUILayout *layout)
  : DrawableObject(x, y), _width(width), _height(height), _isFocused(false), _enable(true)
{
  if (layout)
    layout->insertElementAtEnd(*this);
}

GUIElement::GUIElement(int x, int y, int width, int height)
  : DrawableObject(x, y), _width(width), _height(height), _isFocused(false), _enable(true)
{
  Singleton<GameStateManager>::get().getCurrentState().getGUI().insertElementAtEnd(*this);
}

GUIElement::~GUIElement()
{
}

void GUIElement::focus()
{
  this->_isFocused = true;
}

void GUIElement::unfocus()
{
  this->_isFocused = false;
}

int GUIElement::getWidth() const
{
  return (this->_width);
}

int GUIElement::getHeight() const
{
  return (this->_height);
}

void GUIElement::setWidth(int width)
{
  this->_width = width;
}

void GUIElement::setHeight(int height)
{
  this->_height = height;
}

void GUIElement::setEnable(bool enable)
{
  this->_enable = enable;
}

bool GUIElement::getEnable() const
{
  return this->_enable;
}
