#include "GSContinue.hpp"
#include "GameStateManager.hpp"
#include "Converter.hpp"
#include "GSInGame.hpp"

GSContinue::GSContinue() :
  Core::GameState("continue"),
  _time(10),
  _timer(Core::GameStateManager::get().getCurrentState().getFont("listGameFont"))
{
  _timer->setText(Net::Converter::toString<int>(_time));
  this->addGameObject(_timer);
}

GSContinue::~GSContinue()
{}

void GSContinue::onStart()
{
  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed,
					 *this, &GSContinue::returnToGame);
  this->getInput().registerInputCallback(Core::InputCommand::JoystickMoved,
					 *this, &GSContinue::returnToGame);
}

void GSContinue::returnToGame(Core::InputCommand const &/*cmd*/)
{
  Core::GameStateManager::get().popState();

  Core::GameState *state = Core::GameStateManager::get().getGameState("Game");
  if (state)
	state->play();
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
	  Core::GameStateManager::get().popState();
	  GSInGame *state = static_cast<GSInGame*>(Core::GameStateManager::get().getGameState("Game"));

	  if (state)
	    state->gameover(false);
	}	      
    }
}
