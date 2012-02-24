#include "GUIElement.hpp"
#include "GUILayout.hpp"
#include "GameStateManager.hpp"

CORE_USE_NAMESPACE

GUIElement::GUIElement(int x, int y, int width, int height, GUILayout *layout, GUICommand::PlayerType playerType)
  : DrawableObject(x, y), _width(width), _height(height), _isFocused(false), _enable(true), _hide(false), _playerType(playerType)
{
  if (layout)
    layout->insertElementAtEnd(*this);
}

GUIElement::GUIElement(int x, int y, int width, int height, GUICommand::PlayerType playerType)
  : DrawableObject(x, y), _width(width), _height(height), _isFocused(false), _enable(true), _hide(false), _playerType(playerType)
{
	GameStateManager::get().getCurrentState().getGUI().insertElementAtEnd(*this);
}

GUIElement::~GUIElement()
{
}

bool GUIElement::catchGUICommand(GUICommand const &command)
{
	if (this->_playerType == GUICommand::ALL || command.playerType == this->_playerType)
		return (this->handleGUICommand(command));
	return (false);
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

bool GUIElement::getHide() const
{
	return (this->_hide);
}

void GUIElement::setHide(bool hide)
{
	this->_hide = hide;
}