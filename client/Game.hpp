#ifndef		_GAME_
#define 	_GAME_

#include <fstream>
#include <string>
#include <vector>
#include "Singleton.hpp"
#include "GameStateManager.hpp"
#include "ModuleManager.hpp"

class Game : public Net::Singleton<Game>, public Core::ModuleManager
{
public:
  static const std::string PREF_FILE;

  Game();
  virtual ~Game();
  void		init();
  void		quit();

  void		readPreferencesFile();
  void		savePreferencesFile(std::vector<std::string> const &tab);
  std::vector<std::string> const &getPreferences() const;
  bool		isMaster() const;
  void		setMaster(bool value);

private:
  bool						_quit;
  std::fstream				_preferencesFile;
  std::vector<std::string>	_preferences;
  bool						_master;
};

#endif		/* _GAME_ */
