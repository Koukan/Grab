#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/network.h>
#include <ClanLib/sound.h>
#include <ClanLib/vorbis.h>
#include <ClanLib/mikmod.h>
#include "Game.hpp"
#include "AudioManager.hpp"
#if defined (WIN32)
#include <direct.h>
#endif

int	main(int /*ac*/, char**av)
{
  std::string		path = av[0];

  #if defined (WIN32)
  _chdir(path.substr(0, path.rfind('/')).c_str());
  #else
  chdir(path.substr(0, path.rfind('/')).c_str());
  #endif
  try
  {
    Game::get().init("Grab : The Power of the Lost Grapple");
    Game::get().exec();
    return 0;
  }
  catch (CL_Exception &e)
  {
    CL_Console::write_line("Unhandled Exception: %1", e.get_message_and_stack_trace());
    return 1;
  }
}
