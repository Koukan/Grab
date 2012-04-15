#include "GSContinue.hpp"
#include "GameStateManager.hpp"
#include "Converter.hpp"
#include "GSInGame.hpp"
#include "RendererManager.hpp"
#include "Player.hpp"

GSContinue::GSContinue(GSInGame& ingame, std::list<Player *> const & players,
		       unsigned int nbContinues) :
  Core::GameState("continue"),
  _time(10),
  _continue(false),
  _timer(this->getFont("bigNumbersFont")),
  _info(this->getFont("bigNumbersFont")),
  _nbContinues(this->getFont("listGameFont")),
  _inGame(ingame), _players(players)
{
  if (_timer && _info)
    {
      _timer->setText(Net::Converter::toString<int>(_time));
      _timer->setX(VIEWX / 2 - _timer->getWidth() / 2);
      _timer->setY(VIEWY / 2 - _timer->getHeight() / 2);
      _info->setText("CONTINUE ?");
      _info->setX(VIEWX / 2 - _info->getWidth() / 2);
      _info->setY(VIEWY / 2 - _info->getHeight() / 2 - 100);
      this->addGameObject(_info);
      this->addGameObject(_timer);
    }
  if (_nbContinues)
    {
      _nbContinues->setText("Continues : " + Net::Converter::toString<unsigned int>(nbContinues));
      _nbContinues->setX(VIEWX / 2 - _nbContinues->getWidth() / 2 + 200);
      _nbContinues->setY(VIEWY / 2 - _nbContinues->getHeight() / 2 + 200);
      this->addGameObject(_nbContinues);
    }
}

GSContinue::~GSContinue()
{}

void GSContinue::onStart()
{
   for (std::list<Player *>::const_iterator it = this->_players.begin();
  it != this->_players.end();
    ++it)
    {
      if ((*it)->getType() == Player::KEYBOARD)
	{
	  this->getInput().registerInputCallback(Core::InputCommand::KeyReleased,
						 *this, &GSContinue::returnToGame,
						 static_cast<int>((*it)->getAction(Player::FIRE).Key.Code));
	  this->getInput().registerInputCallback(Core::InputCommand::KeyReleased,
						 *this, &GSContinue::returnToGame,
						 static_cast<int>((*it)->getAction(Player::PAUSE).Key.Code));	  
	}
      else
	{
	  this->getInput().registerInputCallback(Core::InputCommand::JoystickButtonReleased,
						 *this, &GSContinue::returnToGame,
						 static_cast<int>((*it)->getAction(Player::FIRE).JoystickButton.Button));
	  this->getInput().registerInputCallback(Core::InputCommand::JoystickButtonReleased,
						 *this, &GSContinue::returnToGame,
						 static_cast<int>((*it)->getAction(Player::PAUSE).JoystickButton.Button));
						 }
    }
}

void GSContinue::returnToGame(Core::InputCommand const &/*cmd*/)
{
	if (!this->_continue)
	{
		this->_continue = true;
		Core::GameStateManager::get().popState();
	}
}

void GSContinue::update(double elapsedTime)
{
  static int time = 0;

  time += elapsedTime;
  if (time >= 1000)
    {
      time -= 1000;
      _time -= 1;
      _timer->setText(Net::Converter::toString<int>(_time));
      if (_time == 0)
	{
	  _inGame.setGameOver(2);
	  Core::GameStateManager::get().popState();
	}
    }
}

bool	GSContinue::handleCommand(Core::Command const &cmd)
{
	return this->_inGame.handleCommand(cmd);
}