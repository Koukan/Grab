#include "Server.hpp"
#if defined (WIN32)
#include <direct.h>
#define chdir _chdir
#endif

int		main(int ac, char **av)
{
  std::string		path = av[0];

  chdir(path.substr(0, path.rfind('/')).c_str());
  try
  {
	bool		ret;
	if (ac > 1)
		ret = Server::get().init(av[1]);
	else
		ret = Server::get().init();
    return (ret) ? 0 : 1;
  }
  catch (...)
  {
	std::cerr << "Unhandled Exception" << std::endl;
    return 1;
  }
  return 0;
}
