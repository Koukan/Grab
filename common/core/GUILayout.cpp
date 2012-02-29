#include "GUILayout.hpp"

CORE_USE_NAMESPACE

GUILayout::GUILayout(int x, int y, int width, int height, int padding, GUILayout *layout, int nbElements, GUICommand::PlayerType playerType)
  : GUIElement(x, y, width, height, layout, playerType), _padding(padding), _nbElements(nbElements), _dispatch(false)
{
  this->_begin = this->_elements.begin();
  this->_focusElement = this->_elements.begin();
  if (this->_isFocused)
    this->focus();
  else
    this->unfocus();
}

GUILayout::GUILayout(int x, int y, int width, int height, int padding, int nbElements, GUICommand::PlayerType playerType)
  : GUIElement(x, y, width, height, playerType), _padding(padding), _nbElements(nbElements), _dispatch(false)
{
  this->_begin = this->_elements.begin();
  this->_focusElement = this->_elements.begin();
  if (this->_isFocused)
	this->focus();
  else
    this->unfocus();
}

GUILayout::~GUILayout()
{
  this->clear();
}

void GUILayout::focus()
{
  if (!this->_elements.empty())
	  {
		  if (this->_focusElement == this->_elements.end())
			this->nextElement();
		  else
			(*this->_focusElement)->focus();
  }
  this->GUIElement::focus();
}

void GUILayout::unfocus()
{
  if (this->_focusElement != this->_elements.end())
    (*this->_focusElement)->unfocus();
  this->GUIElement::unfocus();
}

void GUILayout::clear()
{	
  for (std::list<GUIElement *>::iterator it = this->_elements.begin(); it != this->_elements.end(); ++it)
    {
      delete *it;
   	}
	_focusElement = _elements.begin();
	_begin = _elements.begin();	
}

void GUILayout::insertElementAtBegin(GUIElement &elem)
{
  elem.unfocus();
  this->_elements.push_front(&elem);
  this->_begin = this->_elements.begin();
  if (this->_focusElement == this->_elements.end() || !(*this->_focusElement)->getEnable() || (*this->_focusElement)->getHide())
    {
      std::list<GUIElement *>::iterator it = this->_elements.begin();
      for (; it != this->_elements.end() && (!(*it)->getEnable() || (*it)->getHide()); ++it);
      this->_focusElement = it;
	  if (it != this->_elements.end())
      	(*it)->focus();
    }
}

void GUILayout::insertElementAtEnd(GUIElement &elem)
{
	elem.unfocus();
  this->_elements.push_back(&elem);
  this->_begin = this->_elements.begin();
  if (this->_focusElement == this->_elements.end() || !(*this->_focusElement)->getEnable() || (*this->_focusElement)->getHide())
    {
      std::list<GUIElement *>::iterator it = this->_elements.begin();
      for (; it != this->_elements.end() && (!(*it)->getEnable() || (*it)->getHide()); ++it);
	  if (it != this->_elements.end())
	  {
	      this->_focusElement = it;
		  (*it)->focus();
	  }
    }
}

void GUILayout::prevElement()
{
  if (this->_focusElement == this->_begin)
    {
      if (this->_begin != this->_elements.begin())
	--this->_begin;
      else
	{
	  std::list<GUIElement *>::iterator it = this->_elements.end();
	  for (int i = 0; i < this->_nbElements && it != this->_elements.begin(); ++i)
	    --it;
	  this->_begin = it;
	}
    }
  if (this->_focusElement != this->_elements.end() && !this->_dispatch)
    (*this->_focusElement)->unfocus();
  if (this->_focusElement == this->_elements.begin())
    this->_focusElement = --this->_elements.end();
  else
    --this->_focusElement;
  if (this->_focusElement != this->_elements.end())
    {
      if ((*this->_focusElement)->getEnable() == false || (*this->_focusElement)->getHide())
	this->prevElement();
      else
	  {
		if (!this->_dispatch)
			(*this->_focusElement)->focus();
	  }
    }
}

void GUILayout::nextElement()
{
  int nb = 0;

  std::list<GUIElement *>::iterator it2 = this->_focusElement;

  ++it2;
  for (std::list<GUIElement *>::iterator it = this->_begin; it != it2 && nb < this->_nbElements; ++it)
    ++nb;
  if (nb == this->_nbElements)
    {
      if (it2 == this->_elements.end())
	this->_begin = this->_elements.begin();
      else
	++this->_begin;
    }
  if (this->_focusElement == this->_elements.end())
    this->_focusElement = this->_elements.begin();
  else if (this->_focusElement == --this->_elements.end())
    {
		if (!this->_dispatch)
			(*this->_focusElement)->unfocus();
		this->_focusElement = this->_elements.begin();
    }
  else
    {
		if (!this->_dispatch)
		    (*this->_focusElement)->unfocus();
      ++this->_focusElement;
    }
  if (this->_focusElement != this->_elements.end())
    {
      if ((*this->_focusElement)->getEnable() == false || (*this->_focusElement)->getHide())
	  this->nextElement();
      else
	  {
		if (!this->_dispatch)
			(*this->_focusElement)->focus();
	  }
    }
}

bool GUILayout::handleGUICommand(GUICommand const &command)
{
	if (!_dispatch)
	{
		if (this->_focusElement != this->_elements.end())
			return ((*(this->_focusElement))->catchGUICommand(command));
		return (false);
    }
	for (std::list<GUIElement *>::iterator it = _elements.begin(); it != _elements.end(); ++it)
	{
		if ((*it)->catchGUICommand(command))
			return (true);
	}
	return (false);
}

void		GUILayout::draw(double elapseTime)
{
  for (std::list<GUIElement *>::iterator it = this->_elements.begin(); it != this->_elements.end(); ++it)
    {
		if (!(*it)->getHide())
			(*it)->draw(elapseTime);
    }
}

void GUILayout::draw(int x, int y, double elapseTime)
{
  for (std::list<GUIElement *>::iterator it = this->_elements.begin(); it != this->_elements.end(); ++it)
    {
		if (!(*it)->getHide())
			(*it)->draw(x, y, elapseTime);
    }
}

void GUILayout::setDispatch(bool dispatch)
{
  _dispatch = dispatch;
}

bool GUILayout::isEmpty() const
{
  return !(this->_nbElements);
}
