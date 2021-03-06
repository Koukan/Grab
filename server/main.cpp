#include "Server.hpp"
#if defined (WIN32)
#include <direct.h>
#define chdir _chdir
#endif
#include <exception>

int		main(int ac, char **av)
{
  std::string		path = av[0];
  Net::SetupNetwork       setup;

  chdir(path.substr(0, path.rfind('/')).c_str());
  try
  {
	bool		ret;
	if (ac > 1)
		ret = Server::get().initServer(av[1]);
	else
		ret = Server::get().initServer();
    return (ret) ? 0 : 1;
  }
  catch (std::exception const &e)
    {
      std::cerr << "Unhandled Exception" << e.what() << std::endl;
      return 1;
    }
  return 0;
}
