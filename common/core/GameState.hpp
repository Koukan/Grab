#ifndef		_GAMESTATE_
#define 	_GAMESTATE_

#include <list>
#include <string>
#include "GameObjectManager.hpp"
#include "CommandHandler.hpp"
#include "ResourceManager.hpp"
#include "Command.hpp"
#include "InputManager.hpp"
#include "GUIManager.hpp"
#include "Sound.hpp"

CORE_BEGIN_NAMESPACE

class Game;

class CORE_DLLREQ GameState : public GameObjectManager, public ResourceManager,
		  public CommandHandler
{
public:
  enum Pause
  {
    NONE = 0,
    DRAW = 1,
    PHYSIC = 2,
    ALL = 3
  };

  GameState(const std::string &name, bool GUIautoBack = false);
  virtual ~GameState();
  virtual void	onStart();
  virtual void	onEnd();
  virtual void	onChange();
  virtual void	onResume();
  virtual void	onPause();
  virtual void	onPlay();
  virtual void	update(double elapseTime = 0);
  void			pause(Pause paused = ALL);
  void			play();
  void			addSound(Core::Sound &sound);
  Pause			getPaused() const;
  InputManager		&getInput();
  GUIManager		&getGUI();

  const std::string	name;

private:
  Pause						_paused;
  GUIManager				_GUIManager;
  InputManager				_inputManager;
  std::list<Core::Sound*>	_sounds;
};

CORE_END_NAMESPACE

#endif		/* _GAMESTATE_ */
