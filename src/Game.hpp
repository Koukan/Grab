#ifndef		_GAME_
#define 	_GAME_

#include <string>
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/network.h>
#include "Singleton.hpp"
#include <ClanLib/sound.h>
#include <ClanLib/vorbis.h>
#include <ClanLib/mikmod.h>
#include "GameStateManager.hpp"
#include "ManagerManager.hpp"

class Game : public Singleton<Game>, public GameStateManager, public ManagerManager
{
public:
  Game();
  virtual ~Game();
  void		init(const std::string &name = "Grab : The Power of the Lost Grapple");
  void		exec();
  void		quit();

private:
  void		initInput(void);
  void		handleInput(const CL_InputEvent &event, const CL_InputState &state);
  void		update(double elapsedTime);

  bool			_quit;
  CL_InputContext	_ic;
  int			_mainLoopRate;

  CL_SoundOutput	_sound_output;
  CL_SetupSound		_setup_sound;
  CL_SetupMikMod	_setup_mikmod;
  CL_SetupVorbis	_setup_vorbis;
  CL_SetupCore		_setupCore;
  CL_SetupNetwork	_setupNetwork;
  CL_ConsoleLogger	_logger;
};

#endif		/* _GAME_ */
