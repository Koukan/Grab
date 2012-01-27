#include "GUIHLayout.hpp"

GUIHLayout::GUIHLayout(int x, int y, int width, int height, int padding, GUILayout *layout, int nbElements)
  : GUILayout(x, y, width, height, padding, layout, nbElements)
{
}

GUIHLayout::GUIHLayout(int x, int y, int width, int height, int padding, int nbElements)
  : GUILayout(x, y, width, height, padding, nbElements)
{
}

GUIHLayout::~GUIHLayout()
{
}

bool GUIHLayout::handleGUICommand(InputCommand const &command)
{
  if (command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Left)
    {
      this->prevElement();
      return (true);
    }
  else if (command.Type == InputCommand::KeyPressed && command.Key.Code == Keyboard::Right)
    {
      this->nextElement();
      return (true);
    }
  return (this->GUILayout::handleGUICommand(command));
}

void GUIHLayout::draw(double elapseTime)
{
  int x = this->_x;
  int y = this->_y;
  int nb = 0;

  for (std::list<GUIElement *>::iterator it = this->_begin; it != this->_elements.end() && nb < this->_nbElements; ++it)
    {
      (*it)->draw(x, y - (*it)->getHeight() / 2, elapseTime);
      x += (*it)->getWidth() + this->_padding;
      ++nb;
    }
}

void GUIHLayout::draw(int x, int y, double elapseTime)
{
  int nb = 0;

  for (std::list<GUIElement *>::iterator it = this->_begin; it != this->_elements.end() && nb < this->_nbElements; ++it)
    {
      (*it)->draw(x, y - (*it)->getHeight() / 2, elapseTime);
      x += (*it)->getWidth() + this->_padding;
      ++nb;
    }
}
