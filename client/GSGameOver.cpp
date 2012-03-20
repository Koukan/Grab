#include "GSGameOver.hpp"
#include "GUIVLayout.hpp"
#include "ButtonSprite.hpp"
#include "RendererManager.hpp"
#include "GUIButton.hpp"
#include "SFMLFont.hpp"
#include "GSInGame.hpp"

GSGameOver::GSGameOver(bool victory, std::list<Player *> const& players,
		       Modes::Mode mode, std::string const& map, 
		       unsigned int nbPlayers, bool online) :
  Core::GameState("gameOver"),
  _victory(victory), _players(players), _mode(mode), _map(map),
  _nbPlayers(nbPlayers), _online(online)
{}

GSGameOver::~GSGameOver()
{}

void GSGameOver::onStart()
{
  Core::GUILayout *layout = new GUIVLayout(RendererManager::get().getWidth() / 2,
					   RendererManager::get().getHeight() / 3 * 2,
					   300, 300, 10, 100, "up arrow", "down arrow");
  layout->setY((RendererManager::get().getHeight() - layout->getHeight()) / 2);
  Core::ButtonSprite *sprite = new Core::ButtonSprite("default button", "selected button", "pressed button");
  new GUIButton<GSGameOver>(*this, &GSGameOver::retry, "Retry", "buttonFont", *sprite, layout);
  new GUIButton<GSGameOver>(*this, &GSGameOver::returnToMainMenu, "Go to Main Menu", "buttonFont", *sprite, layout);
}

void GSGameOver::onEnd()
{}

bool	GSGameOver::handleCommand(Core::Command const &)
{
  return false;
}

void	GSGameOver::retry()
{
	Core::GameStateManager::get().popState();
	Core::GameStateManager::get().popState();

	GSInGame *gs = new GSInGame(this->_players, this->_mode, this->_map, this->_players.size(), this->_online);
	Core::GameStateManager::get().pushState(*gs);
	gs->preload();
	
}

void	GSGameOver::returnToMainMenu()
{
	Core::GameStateManager::get().popState();
	Core::GameStateManager::get().popState();
	Core::GameStateManager::get().popState();
	Core::GameStateManager::get().popState();
	Core::GameStateManager::get().popState();
}
