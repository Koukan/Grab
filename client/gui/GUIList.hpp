#pragma once

#include <list>
#include <string>
#include "Command.hpp"
#include "ButtonSprite.hpp"
#include "GUIElement.hpp"

template <typename T>
class GUIList : public GUIElement {
public:
  GUIList(std::string const & /*font */, ButtonSprite &left_arrow, ButtonSprite &right_arrow, int x, int y)
    : GUIElement(x, y, left_arrow.getWidth() + right_arrow.getWidth() + 10, left_arrow.getHeight()),
      _leftArrow(left_arrow), _rightArrow(right_arrow),
      _instance(0), _func(0), _focusElement(_elements.begin())
  {
    if (this->_isFocused)
      this->focus();
    else
      this->unfocus();
  }

  GUIList(ButtonSprite &left_arrow, ButtonSprite &right_arrow, int x, int y, T &instance, void (T::*func)(GUIElement const &))
    : GUIElement(x, y, left_arrow.getWidth() + right_arrow.getWidth() + 10, left_arrow.getHeight()),
      _leftArrow(left_arrow), _rightArrow(right_arrow),
      _instance(&instance), _func(func), _focusElement(_elements.begin())
  {
    if (this->_isFocused)
      this->focus();
    else
      this->unfocus();
      }

  GUIList(T &instance, void (T::*func)(GUIElement const &), ButtonSprite &left_arrow, ButtonSprite &right_arrow, GUILayout *layout)
    : GUIElement(0, 0, left_arrow.getWidth() + right_arrow.getWidth() + 10, left_arrow.getHeight(), layout),
      _leftArrow(left_arrow), _rightArrow(right_arrow), _instance(&instance), _func(func), _focusElement(_elements.begin())
  {
    if (this->_isFocused)
      this->focus();
    else
      this->unfocus();
  }

  ~GUIList()
  {}

  virtual void addElement(GUIElement &elem)
  {
    this->_elements.push_back(&elem);
    if (this->_focusElement == this->_elements.end())
      {
	this->_focusElement = this->_elements.begin();
	(this->_instance->*(this->_func))(*(*_focusElement));
	this->_width = this->_leftArrow.getWidth() + this->_rightArrow.getWidth() + 10 + (*this->_focusElement)->getWidth();
      }
  }

  virtual bool handleGUICommand(InputCommand const &command)
  {
    if (command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Left)
      {
	this->_leftArrow.updateState(ButtonSprite::CLICKED);
	this->EventLeft();
	if (this->_instance)
	  (this->_instance->*(this->_func))(**(_focusElement));
	return (true);
      }
    else if (command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Right)
      {
	this->_rightArrow.updateState(ButtonSprite::CLICKED);
	this->EventRight();
	if (this->_instance)
	  (this->_instance->*(this->_func))(**(_focusElement));
	return (true);
      }
    else if (command.Type == InputCommand::KeyReleased && command.Key.Code == Keyboard::Left)
      {
	if (this->_isFocused)
	  this->_leftArrow.updateState(ButtonSprite::SELECTED);
	else
	  this->_leftArrow.updateState(ButtonSprite::DEFAULT);
	return (true);
      }
    else if (command.Type == InputCommand::KeyReleased && command.Key.Code == Keyboard::Right)
      {
	if (this->_isFocused)
	  this->_rightArrow.updateState(ButtonSprite::SELECTED);
	else
	  this->_rightArrow.updateState(ButtonSprite::DEFAULT);
	return (true);
      }
    if (this->_focusElement != this->_elements.end())
      return ((*this->_focusElement)->handleGUICommand(command));
    return false;
  }

  virtual void focus()
  {
    this->_leftArrow.updateState(ButtonSprite::SELECTED);
    this->_rightArrow.updateState(ButtonSprite::SELECTED);
    if (this->_focusElement != this->_elements.end())
      (*this->_focusElement)->focus();
    this->GUIElement::focus();
  }

  virtual void unfocus()
  {
    this->_leftArrow.updateState(ButtonSprite::DEFAULT);
    this->_rightArrow.updateState(ButtonSprite::DEFAULT);
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

  ButtonSprite				_leftArrow;
  ButtonSprite				_rightArrow;
  T *					_instance;
  void					(T::*_func)(GUIElement const &);
  std::list<GUIElement *>		_elements;
  std::list<GUIElement *>::iterator	_focusElement;
};
