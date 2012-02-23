#include "GSLoading.hpp"
#include "GSInGame.hpp"
#include "Game.hpp"
#include "Bullet.hpp"
#include "Wall.hpp"
#include "SFMLSpriteProvider.hpp"
#include "SFMLFontProvider.hpp"
#include "GUIButton.hpp"
#include "GUIList.hpp"
#include "GUIVLayout.hpp"
#include "GUIHLayout.hpp"
#include "ScrollingSprite.hpp"
#include "GameStateManager.hpp"
#include "GSInGame.hpp"
#include "ResourceCommand.hpp"

GSLoading::GSLoading(int nbPlayers) : Core::GameState("Loading", true), _nbPlayers(nbPlayers)
{
  //AudioManager::get().load("intro", "resource/sound/06-multiplayer-mouse-mania.ogg");
  //AudioManager::get().play("intro", "test", "intro");
  //AudioManager::get().setVolume("intro", "test", 1.0f);
}

GSLoading::~GSLoading()
{}

void	GSLoading::escape(const Core::InputCommand &)
{
  Core::GameStateManager::get().popState();
  	Game::get().quit();
}

//void	GSLoading::click(const CL_InputEvent &event)
//{
//}

void	GSLoading::update(double )
{
}

void	GSLoading::buttonClick()
{
		//this->setComponentVisibility(false);

}

void	GSLoading::listChoice(std::string const &)
{
		//this->setComponentVisibility(false);
}

bool		GSLoading::handleCommand(Core::Command const &command)
{
  static Method const	methods[] = {
    {"GameBegin", &GSLoading::gameBeginCommand},
    {"ErrorFullGame", &GSLoading::errorFullGameCommand},
	{"ResourceId", &GSLoading::resourceId}
  };

	for (size_t i = 0; i < sizeof(methods) / sizeof(*methods); ++i)
	{
		if (command.name == methods[i].name)
		{
			(this->*methods[i].method)(static_cast<GameCommand const &>(command));
			return true;
		}
	}
	return (_ingame->handleCommand(command));
	return false;
}

void	GSLoading::errorFullGameCommand(Core::Command const &)
{
	delete _ingame;
	Core::GameStateManager::get().popState();
}

void	GSLoading::onStart()
{
	this->load("resources/intro.xml");
	this->load("resources/player.xml");

	Core::Sprite *test = this->getSprite("player1");
	test->setX(550);
	test->setY(360);
	this->addGameObject(test, "gui", 20);

	Core::CoreFont *font = this->getFont("buttonFont");
	font->setX(400);
	font->setY(350);
	font->setText("Loading");
	this->addGameObject(font, "gui", 20);
//	_ingame = new GSInGame(this->_nbPlayers);
	_ingame->preload();

  /*this->addBulletParser("resources/BulletBossMetroid.xml", "Test");
  BulletCommand *bullet = new BulletCommand("Test", *this, 1100, 300);
  this->addGameObject(bullet, "ship");*/
}

void	GSLoading::gameBeginCommand(Core::Command const &)
{
	Core::GameStateManager::get().changeState(*_ingame);
}

void	GSLoading::resourceId(Core::Command const &command)
{
	ResourceCommand const &cmd = static_cast<ResourceCommand const &>(command);

	_ingame->changeId(cmd.name, cmd.id, cmd.type);
}
