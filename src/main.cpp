#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/network.h>
#include <ClanLib/sound.h>
#include <ClanLib/vorbis.h>
#include <ClanLib/mikmod.h>
#include "Game.hpp"
#include "AudioManager.hpp"

int	main(int ac, char**av)
{
  std::string		path = av[0];

  chdir(path.substr(0, path.rfind('/')).c_str());
  try
  {
    Game::get().exec();
    return 0;
  }
  catch (CL_Exception &e)
  {
    CL_Console::write_line("Unhandled Exception: %1", e.get_message_and_stack_trace());
    return 1;
  }
}
