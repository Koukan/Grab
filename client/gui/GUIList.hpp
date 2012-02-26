#pragma once

#include <list>
#include <string>
#include "Command.hpp"
#include "ButtonSprite.hpp"
#include "GUIElement.hpp"

template <typename T>
class GUIList : public Core::GUIElement {
public:
  GUIList(Core::ButtonSprite &left_arrow, Core::ButtonSprite &right_arrow, int x, int y, Core::GUICommand::PlayerType playerType = Core::GUICommand::ALL)
    : Core::GUIElement(x, y, left_arrow.getWidth() + right_arrow.getWidth() + 10, left_arrow.getHeight(), playerType),
      _leftArrow(left_arrow), _rightArrow(right_arrow),
      _instance(0), _func(0), _focusElement(_elements.begin())
  {
    if (this->_isFocused)
      this->focus();
    else
      this->unfocus();
  }

  GUIList(Core::ButtonSprite &left_arrow, Core::ButtonSprite &right_arrow, int x, int y, T &instance, void (T::*func)(Core::GUIElement &), Core::GUICommand::PlayerType playerType = Core::GUICommand::ALL)
    : Core::GUIElement(x, y, left_arrow.getWidth() + right_arrow.getWidth() + 10, left_arrow.getHeight(), playerType),
      _leftArrow(left_arrow), _rightArrow(right_arrow),
      _instance(&instance), _func(func), _focusElement(_elements.begin())
  {
    if (this->_isFocused)
      this->focus();
    else
      this->unfocus();
      }

  GUIList(T &instance, void (T::*func)(Core::GUIElement &), Core::ButtonSprite &left_arrow, Core::ButtonSprite &right_arrow, Core::GUILayout *layout, Core::GUICommand::PlayerType playerType = Core::GUICommand::ALL)
    : Core::GUIElement(0, 0, left_arrow.getWidth() + right_arrow.getWidth() + 10, left_arrow.getHeight(), layout, playerType),
      _leftArrow(left_arrow), _rightArrow(right_arrow), _instance(&instance), _func(func), _focusElement(_elements.begin())
  {
    if (this->_isFocused)
      this->focus();
    else
      this->unfocus();
  }

  ~GUIList()
  {}

  virtual void addElement(Core::GUIElement &elem)
  {
    this->_elements.push_back(&elem);
    if (this->_focusElement == this->_elements.end())
      {
	this->_focusElement = this->_elements.begin();
	if (this->_isFocused)
		(*this->_focusElement)->focus();
	(this->_instance->*(this->_func))(*(*_focusElement));
	this->_width = this->_leftArrow.getWidth() + this->_rightArrow.getWidth() + 10 + (*this->_focusElement)->getWidth();
	this->_height = (*this->_focusElement)->getHeight();
      }
  }

  virtual bool handleGUICommand(Core::GUICommand const &command)
  {
    if (command.type == Core::GUICommand::DIRECTION && command.buttonAction == Core::GUICommand::PRESSED && command.direction == Core::GUICommand::LEFT /*command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Left*/)
      {
	this->_leftArrow.updateState(Core::ButtonSprite::CLICKED);
	this->EventLeft();
	if (this->_instance)
	  (this->_instance->*(this->_func))(**(_focusElement));
	return (true);
      }
    else if (command.type == Core::GUICommand::DIRECTION && command.buttonAction == Core::GUICommand::PRESSED && command.direction == Core::GUICommand::RIGHT /*command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Right*/)
      {
	this->_rightArrow.updateState(Core::ButtonSprite::CLICKED);
	this->EventRight();
	if (this->_instance)
	  (this->_instance->*(this->_func))(**(_focusElement));
	return (true);
      }
	else if (command.type == Core::GUICommand::DIRECTION && command.buttonAction == Core::GUICommand::RELEASED && command.direction == Core::GUICommand::LEFT /*command.Type == InputCommand::KeyReleased && command.Key.Code == Keyboard::Left*/)
      {
	if (this->_isFocused)
	  this->_leftArrow.updateState(Core::ButtonSprite::SELECTED);
	else
	  this->_leftArrow.updateState(Core::ButtonSprite::DEFAULT);
	return (true);
      }
    else if (command.type == Core::GUICommand::DIRECTION && command.buttonAction == Core::GUICommand::RELEASED && command.direction == Core::GUICommand::RIGHT /*command.Type == InputCommand::KeyReleased && command.Key.Code == Keyboard::Right*/)
      {
	if (this->_isFocused)
	  this->_rightArrow.updateState(Core::ButtonSprite::SELECTED);
	else
	  this->_rightArrow.updateState(Core::ButtonSprite::DEFAULT);
	return (true);
      }
    if (this->_focusElement != this->_elements.end())
      return ((*this->_focusElement)->handleGUICommand(command));
    return false;
  }

  virtual void focus()
  {
    this->_leftArrow.updateState(Core::ButtonSprite::SELECTED);
    this->_rightArrow.updateState(Core::ButtonSprite::SELECTED);
    if (this->_focusElement != this->_elements.end())
      (*this->_focusElement)->focus();
    this->GUIElement::focus();
  }

  virtual void unfocus()
  {
    this->_leftArrow.updateState(Core::ButtonSprite::DEFAULT);
    this->_rightArrow.updateState(Core::ButtonSprite::DEFAULT);
    if (this->_focusElement != this->_elements.end())
      (*this->_focusElement)->unfocus();
    this->GUIElement::unfocus();
  }

  virtual void draw(double elapseTime)
  {
    unsigned int height = 0;
    unsigned int width = 0;

    if (this->_focusElement != this->_elements.end())
      {
	(*this->_focusElement)->draw(static_cast<int>(this->_x + this->_leftArrow.getWidth() + 5), static_cast<int>(this->_y), elapseTime);
	height = (*this->_focusElement)->getHeight();
	width = (*this->_focusElement)->getWidth();
      }
    this->_leftArrow.draw(static_cast<int>(this->_x), static_cast<int>(this->_y + (height - this->_leftArrow.getHeight()) / 2), elapseTime);
    this->_rightArrow.draw(static_cast<int>(this->_x + width + this->_leftArrow.getWidth() + 10), static_cast<int>(this->_y
			   + (height - this->_rightArrow.getHeight()) / 2), elapseTime);
  }

  virtual void draw(int x, int y, double elapseTime)
  {
    unsigned int height = 0;
    unsigned int width = 0;

    if (this->_focusElement != _elements.end())
      {
	(*this->_focusElement)->draw(x + this->_leftArrow.getWidth() + 5, y, elapseTime);
	height = (*this->_focusElement)->getHeight();
	width = (*this->_focusElement)->getWidth();
      }
    this->_leftArrow.draw(x, y + (height - this->_leftArrow.getHeight()) / 2, elapseTime);
    this->_rightArrow.draw(x + width + this->_leftArrow.getWidth() + 10, y
			   + (height - this->_rightArrow.getHeight()) / 2, elapseTime);
  }

private:
  void EventLeft()
  {
    if (!this->_elements.size())
      return ;
    (*this->_focusElement)->unfocus();
    if (this->_focusElement == this->_elements.begin())
      this->_focusElement = this->_elements.end();
    --this->_focusElement;
    if (this->_focusElement != this->_elements.end())
      {
	this->_width = this->_leftArrow.getWidth() + this->_rightArrow.getWidth() + 10 + (*this->_focusElement)->getWidth();
	(*this->_focusElement)->focus();
      }
  }

  void EventRight()
  {
    if (!this->_elements.size())
      return ;
    (*this->_focusElement)->unfocus();
    ++this->_focusElement;
    if (this->_focusElement == this->_elements.end())
      this->_focusElement = this->_elements.begin();
    if (this->_focusElement != this->_elements.end())
      {
	this->_width = this->_leftArrow.getWidth() + this->_rightArrow.getWidth() + 10 + (*this->_focusElement)->getWidth();
	(*this->_focusElement)->focus();
      }
  }

  Core::ButtonSprite				_leftArrow;
  Core::ButtonSprite				_rightArrow;
  T *					_instance;
  void					(T::*_func)(Core::GUIElement &);
  std::list<Core::GUIElement *>		_elements;
  std::list<Core::GUIElement *>::iterator	_focusElement;
};
