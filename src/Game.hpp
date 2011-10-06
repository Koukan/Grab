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
  Game(const std::string &name = "Grab : The Power of the Lost Grapple");
  virtual ~Game();
  void		exec();
  void		quit();

private:
  void		initGraphics(const std::string &);
  void		handleInput(const CL_InputEvent &event, const CL_InputState &state);
  void		update(int elapsedTime);

  bool			_quit;
  CL_DisplayWindow	*_window;
  CL_GraphicContext	_gc;
  CL_InputContext	_ic;
  int			_mainLoopRate;

  CL_SoundOutput	_sound_output;
  CL_SetupSound		_setup_sound;
  CL_SetupMikMod	_setup_mikmod;
  CL_SetupVorbis	_setup_vorbis;
  CL_SetupCore		_setupCore;
  CL_SetupNetwork	_setupNetwork;
  CL_ConsoleLogger	_logger;
  CL_SetupDisplay 	_setup_display;
  CL_SetupGL		_setup_gl;
};

#endif		/* _GAME_ */
