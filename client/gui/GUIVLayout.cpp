#include "GUIVLayout.hpp"
#include "GameStateManager.hpp"
#include "Player.hpp"

GUIVLayout::GUIVLayout(int x, int y, int width, int height, int padding, Core::GUILayout *layout, int nbElements, std::string const &arrowUp, std::string const &arrowDown,
	  Core::GUICommand::PlayerType playerType)
  : Core::GUILayout(x, y, width, height, padding, layout, nbElements, playerType), _upArrow(Core::GameStateManager::get().getCurrentState().getSprite(arrowUp)), _downArrow(Core::GameStateManager::get().getCurrentState().getSprite(arrowDown))
{
}

GUIVLayout::GUIVLayout(int x, int y, int width, int height, int padding, int nbElements, std::string const &arrowUp, std::string const &arrowDown,
	  Core::GUICommand::PlayerType playerType)
  : Core::GUILayout(x, y, width, height, padding, nbElements, playerType), _upArrow(Core::GameStateManager::get().getCurrentState().getSprite(arrowUp)), _downArrow(Core::GameStateManager::get().getCurrentState().getSprite(arrowDown))
{
}

GUIVLayout::~GUIVLayout()
{
	delete this->_upArrow;
	delete this->_downArrow;
}

bool GUIVLayout::handleGUICommand(Core::GUICommand const &command)
{
	if (command.type == Core::GUICommand::DIRECTION && command.buttonAction == Core::GUICommand::PRESSED && command.direction == Core::GUICommand::UP)
    {
      this->prevElement();
      return (true);
    }
  else if (command.type == Core::GUICommand::DIRECTION && command.buttonAction == Core::GUICommand::PRESSED && command.direction == Core::GUICommand::DOWN)
    {
      this->nextElement();
      return (true);
    }
  return (this->GUILayout::handleGUICommand(command));
}

void GUIVLayout::draw(double elapseTime)
{
  int x = static_cast<int>(this->_x);
  int y = static_cast<int>(this->_y);
  int nb = 0;

  if (this->_upArrow && this->_begin != this->_elements.begin())
    this->_upArrow->draw(x - this->_upArrow->getWidth() / 2, y - this->_upArrow->getHeight() - 5);
  std::list<Core::GUIElement *>::iterator it = this->_begin;
  for (; it != this->_elements.end() && nb < this->_nbElements; ++it)
    {
		if (!(*it)->getHide())
		{
			(*it)->draw(x - (*it)->getWidth() / 2, y, elapseTime);
			y += (*it)->getHeight() + this->_padding;
			++nb;
		}
    }
  if (this->_downArrow && it != this->_elements.end())
    this->_downArrow->draw(x - this->_downArrow->getWidth() / 2, y + 5 - this->_padding);
}

void GUIVLayout::draw(int x, int y, double elapseTime)
{
  int nb = 0;

  if (this->_upArrow && this->_begin != this->_elements.begin())
    this->_upArrow->draw(x - this->_upArrow->getWidth() / 2, y - this->_upArrow->getHeight() - 5);
  std::list<Core::GUIElement *>::iterator it = this->_begin;
  for (; it != this->_elements.end() && nb < this->_nbElements; ++it)
    {
		if (!(*it)->getHide())
		{
			(*it)->draw(x - (*it)->getWidth() / 2, y, elapseTime);
			y += (*it)->getHeight() + this->_padding;
			++nb;
		}
    }
  if (this->_downArrow && it != this->_elements.end())
    this->_downArrow->draw(x - this->_downArrow->getWidth() / 2, y + 5 - this->_padding);
}
