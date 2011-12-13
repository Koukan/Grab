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
#include "ModuleManager.hpp"

class Game : public Singleton<Game>, public ModuleManager
{
public:
  Game();
  virtual ~Game();
  void		init();
  void		quit();

private:
  bool		_quit;

  CL_SoundOutput	_sound_output;
  CL_SetupSound		_setup_sound;
  CL_SetupMikMod	_setup_mikmod;
  CL_SetupVorbis	_setup_vorbis;
  CL_SetupCore		_setupCore;
  CL_ConsoleLogger	_logger;
};

#endif		/* _GAME_ */
