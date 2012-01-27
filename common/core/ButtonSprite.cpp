#include "ButtonSprite.hpp"
#include "GameStateManager.hpp"

ButtonSprite::ButtonSprite(std::string const &buttonSprite,
			   std::string const &buttonSelectedSprite,
			   std::string const &buttonClickedSprite)
  : _defaultName(buttonSprite), _selected(buttonSelectedSprite), _clicked(buttonClickedSprite), _state(ButtonSprite::DEFAULT)
{
  GameState *gameState = &(GameStateManager::get().getCurrentState());

  this->_defaultSprite = gameState->getSprite(buttonSprite);
  this->_selectedSprite = gameState->getSprite(buttonSelectedSprite);
  this->_clickedSprite = gameState->getSprite(buttonClickedSprite);

  gameState->getGUI().registerButtonSprite(*this);
}

ButtonSprite::~ButtonSprite()
{
  delete this->_defaultSprite;
  delete this->_selectedSprite;
  delete this->_clickedSprite;
}

ButtonSprite::ButtonSprite(ButtonSprite const &buttonSprite) :
 _defaultName(buttonSprite._defaultName), _selected(buttonSprite._selected), _clicked(buttonSprite._clicked), _state(ButtonSprite::DEFAULT)
{
  GameState *gameState = &(GameStateManager::get().getCurrentState());
  
  this->_defaultSprite = gameState->getSprite(_defaultName);
  this->_selectedSprite = gameState->getSprite(_selected);
  this->_clickedSprite = gameState->getSprite(_clicked);
  gameState->getGUI().registerButtonSprite(*this);
}

void ButtonSprite::updateState(enum ButtonSprite::eState state)
{
  this->_state = state;
}

void ButtonSprite::draw(int x, int y, double elapseTime)
{
  if (_state == DEFAULT && this->_defaultSprite)
    this->_defaultSprite->draw(x, y, elapseTime);
  else if (_state == SELECTED && this->_selectedSprite)
    this->_selectedSprite->draw(x, y, elapseTime);
  else if (_state == CLICKED && this->_clickedSprite)
    this->_clickedSprite->draw(x, y, elapseTime);
}

int ButtonSprite::getWidth() const
{
  if (this->_defaultSprite && this->_selectedSprite && this->_clickedSprite)
  {
	if (this->_defaultSprite->getWidth() > this->_selectedSprite->getWidth() &&
		  this->_defaultSprite->getWidth() > this->_clickedSprite->getWidth())
		return (this->_defaultSprite->getWidth());
	else if (this->_clickedSprite->getWidth() > this->_defaultSprite->getWidth() &&
		  this->_clickedSprite->getWidth() > this->_selectedSprite->getWidth())
		 return (this->_clickedSprite->getWidth());
	return (this->_selectedSprite->getWidth());
  }
  return (0);
}

int ButtonSprite::getHeight() const
{
  if (this->_defaultSprite && this->_selectedSprite && this->_clickedSprite)
  {
	 if (this->_defaultSprite->getHeight() > this->_selectedSprite->getHeight() &&
		this->_defaultSprite->getHeight() > this->_clickedSprite->getHeight())
    return (this->_defaultSprite->getHeight());
	else if (this->_clickedSprite->getHeight() > this->_defaultSprite->getHeight() &&
      this->_clickedSprite->getHeight() > this->_selectedSprite->getHeight())
    return (this->_clickedSprite->getHeight());
	return (this->_selectedSprite->getHeight());
  }
  return (0);
}
