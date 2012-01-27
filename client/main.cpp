#include "Game.hpp"
#if defined (WIN32)
#include <direct.h>
#define chdir _chdir
#endif

int	main(int /*ac*/, char**av)
{
  std::string		path = av[0];

  chdir(path.substr(0, path.rfind('/')).c_str());
  try
  {
	Game::get().init();
    Game::get().update(0);
    return 0;
  }
  catch (std::exception &e)
  {
    std::cerr << "Unhandled Exception : " << e.what() << std::endl;
	while (1);
    return 1;
  }
}
